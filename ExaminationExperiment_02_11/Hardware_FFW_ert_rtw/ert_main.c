#include <stdio.h>
#include <stdlib.h>
#include "Hardware_FFW.h"
#include "Hardware_FFW_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "ext_mode.h"
#include "MW_raspi_init.h"
#include "linuxTimeLogger.h"
#include "MW_Pyserver_control.h"
#include "linuxinitialize.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
extmodeErrorCode_T errorCode;
sem_t stopSem;
sem_t baserateTaskSem;
sem_t subrateTaskSem[1];
int taskId[1];
pthread_t schedulerThread;
pthread_t baseRateThread;
pthread_t backgroundThread;
void *threadJoinStatus;
int terminatingmodel = 0;
pthread_t subRateThread[1];
pthread_mutex_t rateTaskFcnRunningMutex[2];
int subratePriority[1];
int testForRateOverrun(int rateID);
extmodeSimulationTime_T getCurrentTaskTime(int_T tid)
{
  extmodeSimulationTime_T extmodeTime = 0;
  switch (tid) {
   case 0:
    extmodeTime = (extmodeSimulationTime_T)(Hardware_FFW_M->Timing.t[0]);
    break;

   case 1:
    extmodeTime = (extmodeSimulationTime_T)(Hardware_FFW_M->Timing.t[1]);
    break;

   case 2:
    extmodeTime = (extmodeSimulationTime_T)((((Hardware_FFW_M->Timing.clockTick2
      +Hardware_FFW_M->Timing.clockTickH2* 4294967296.0)) * 0.002));
    break;
  }

  return extmodeTime;
}

void *subrateTask(void *arg)
{
  int_T tid = *((int_T *) arg);
  int_T subRateId;
  subRateId = tid + 2;
  while (runModel) {
    sem_wait(&subrateTaskSem[tid]);
    if (terminatingmodel)
      break;

#ifdef MW_RTOS_DEBUG

    printf(" -subrate task %d semaphore received\n", subRateId);

#endif

    pthread_mutex_lock(&rateTaskFcnRunningMutex[tid+1]);
    extmodeSimulationTime_T currentTime = getCurrentTaskTime(subRateId);
    Hardware_FFW_step(subRateId);

    /* Get model outputs here */

    /* Trigger External Mode event */
    extmodeEvent(subRateId, currentTime);
    pthread_mutex_unlock(&rateTaskFcnRunningMutex[tid+1]);
  }

  pthread_exit((void *)0);
  return NULL;
}

void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(Hardware_FFW_M) == (NULL)) &&
    !rtmGetStopRequested(Hardware_FFW_M);
  while (runModel) {
    sem_wait(&baserateTaskSem);
    pthread_mutex_lock(&rateTaskFcnRunningMutex[0]);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    if (rtmStepTask(Hardware_FFW_M, 2)
        ) {
      testForRateOverrun(1);
      sem_post(&subrateTaskSem[0]);
    }

    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      Hardware_FFW_M->Timing.t[1];
    Hardware_FFW_step(0);

    /* Get model outputs here */

    /* Trigger External Mode event */
    extmodeEvent(1, currentTime);
    pthread_mutex_unlock(&rateTaskFcnRunningMutex[0]);
    stopRequested = !((rtmGetErrorStatus(Hardware_FFW_M) == (NULL)) &&
                      !rtmGetStopRequested(Hardware_FFW_M));
    runModel = !stopRequested && !extmodeSimulationComplete() &&
      !extmodeStopRequested();
  }

  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(Hardware_FFW_M, "stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    int i;

    /* Signal all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(sem_post(&subrateTaskSem[i]), 0, "sem_post");
      CHECK_STATUS(sem_destroy(&subrateTaskSem[i]), 0, "sem_destroy");
    }

    /* Wait for all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(pthread_join(subRateThread[i], &threadJoinStatus), 0,
                   "pthread_join");
    }

    runModel = 0;

    /* Wait for background task to complete */
    CHECK_STATUS(pthread_join(backgroundThread, &threadJoinStatus), 0,
                 "pthread_join");
  }

  MW_killPyserver();
  mwRaspiTerminate();

  /* Terminate model */
  Hardware_FFW_terminate();
  extmodeReset();
  sem_post(&stopSem);
  return NULL;
}

int testForRateOverrun(int rateID)
{
  if (pthread_mutex_trylock(&rateTaskFcnRunningMutex[rateID]) == 0) {
    pthread_mutex_unlock(&rateTaskFcnRunningMutex[rateID]);
    return 0;                          /* Not overruning this rate */
  } else {
    reportOverrun(rateID);
    return 1;                          /* Overruning this rate */
  }
}

void *backgroundTask(void *arg)
{
  while (runModel) {
    /* Run External Mode background activities */
    errorCode = extmodeBackgroundRun();
    if (errorCode != EXTMODE_SUCCESS && errorCode != EXTMODE_EMPTY) {
      /* Code to handle External Mode background task errors
         may be added here */
    }
  }

  pthread_exit((void *)0);
  return NULL;
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  subratePriority[0] = 39;
  mwRaspiInit();
  MW_launchPyserver();
  rtmSetErrorStatus(Hardware_FFW_M, 0);

  /* Parse External Mode command line arguments */
  errorCode = extmodeParseArgs(argc, (const char_T **)argv);
  if (errorCode != EXTMODE_SUCCESS) {
    return (errorCode);
  }

  /* Initialize model */
  Hardware_FFW_initialize();

  /* External Mode initialization */
  errorCode = extmodeInit(Hardware_FFW_M->extModeInfo, &rtmGetTFinal
    (Hardware_FFW_M));
  if (errorCode != EXTMODE_SUCCESS) {
    /* Code to handle External Mode initialization errors
       may be added here */
  }

  if (errorCode == EXTMODE_SUCCESS) {
    /* Wait until a Start or Stop Request has been received from the Host */
    extmodeWaitForHostRequest(EXTMODE_WAIT_FOREVER);
    if (extmodeStopRequested()) {
      rtmSetStopRequested(Hardware_FFW_M, true);
    }
  }

  /* Call RTOS Initialization function */
  myRTOSInit(0.00025, 1);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(sem_destroy(&timerTaskSem[i]), 0, "sem_destroy");
    }
  }

#endif

  {
    int idxMutex;
    for (idxMutex=0; idxMutex<2; idxMutex++)
      pthread_mutex_destroy(&rateTaskFcnRunningMutex[idxMutex]);
  }

  return 0;
}
