/*
 * Hardware_FFW.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Hardware_FFW".
 *
 * Model version              : 14.20
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Oct 21 10:39:02 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (32-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Hardware_FFW_h_
#define Hardware_FFW_h_
#ifndef Hardware_FFW_COMMON_INCLUDES_
#define Hardware_FFW_COMMON_INCLUDES_
#include <string.h>
#include <stdio.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* Hardware_FFW_COMMON_INCLUDES_ */

#include "Hardware_FFW_types.h"
#include <stddef.h>
#include "rt_nonfinite.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Startsetpoint;                /* '<S5>/Start setpoint' */
  real_T SFunction[3];                 /* '<S6>/S-Function' */
  real_T SFunction1;                   /* '<S8>/S-Function1' */
  real_T SFunction_o;                  /* '<S8>/S-Function' */
  real_T ec_Ebox_o1[2];                /* '<S7>/ec_Ebox' */
  real_T ec_Ebox_o2[2];                /* '<S7>/ec_Ebox' */
  real_T ec_Ebox_o3[8];                /* '<S7>/ec_Ebox' */
  real_T Gain[2];                      /* '<S7>/Gain' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T Dctleadlag2;                  /* '<S2>/Dctleadlag2' */
  real_T Dct1lowpass3;                 /* '<S2>/Dct1lowpass3' */
  real_T Gain4;                        /* '<Root>/Gain4' */
  real_T Noise;                        /* '<Root>/Noise' */
  real_T Saturation[2];                /* '<S7>/Saturation' */
  real_T Gain3;                        /* '<Root>/Gain3' */
  real_T Constant1[8];                 /* '<S1>/Constant1' */
  real_T Downsample[2];                /* '<S4>/Downsample' */
} B_Hardware_FFW_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<Root>/Noise' */
  real_T Downsample_Buffer[2];         /* '<S4>/Downsample' */
  real_T fileID;                       /* '<S3>/SPERTE_measurement_function' */
  real_T SFunction_RWORK[50];          /* '<S6>/S-Function' */
  real_T SFunction1_RWORK[2];          /* '<S8>/S-Function1' */
  real_T Dctleadlag2_RWORK[2];         /* '<S2>/Dctleadlag2' */
  real_T Dct1lowpass3_RWORK[2];        /* '<S2>/Dct1lowpass3' */
  void *SFunction1_PWORK;              /* '<S8>/S-Function1' */
  struct {
    void *FilePtr;
  } ToFile_PWORK;                      /* '<S8>/To File ' */

  struct {
    void *LoggedData;
  } Live_Scope_PWORK;                  /* '<S4>/Live_Scope' */

  FILE* eml_openfiles[20];             /* '<S3>/SPERTE_measurement_function' */
  int32_T sfEvent;                     /* '<S3>/SPERTE_measurement_function' */
  uint32_T RandSeed;                   /* '<Root>/Noise' */
  uint32_T NS;                         /* '<S3>/SPERTE_measurement_function' */
  int_T SFunction1_IWORK;              /* '<S8>/S-Function1' */
  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<S8>/To File ' */

  int16_T NF;                          /* '<S3>/SPERTE_measurement_function' */
  uint8_T busy;                        /* '<S3>/SPERTE_measurement_function' */
  boolean_T doneDoubleBufferReInit;    /* '<S3>/SPERTE_measurement_function' */
  boolean_T fileID_not_empty;          /* '<S3>/SPERTE_measurement_function' */
  boolean_T NF_not_empty;              /* '<S3>/SPERTE_measurement_function' */
  boolean_T busy_not_empty;            /* '<S3>/SPERTE_measurement_function' */
  boolean_T NS_not_empty;              /* '<S3>/SPERTE_measurement_function' */
  boolean_T eml_openfiles_not_empty;   /* '<S3>/SPERTE_measurement_function' */
  boolean_T eml_autoflush[20];         /* '<S3>/SPERTE_measurement_function' */
  boolean_T eml_autoflush_not_empty;   /* '<S3>/SPERTE_measurement_function' */
} DW_Hardware_FFW_T;

/* Parameters (default storage) */
struct P_Hardware_FFW_T_ {
  real_T SFunction_P1_Size[2];         /* Computed Parameter: SFunction_P1_Size
                                        * Referenced by: '<S6>/S-Function'
                                        */
  real_T ref_part[12];                 /* Variable: ref_part
                                        * Referenced by: '<S6>/S-Function'
                                        */
  real_T Refpower_stat;                /* Mask Parameter: Refpower_stat
                                        * Referenced by: '<S5>/Start setpoint'
                                        */
  uint32_T MeasurementBlock_N_samples;
                                   /* Mask Parameter: MeasurementBlock_N_samples
                                    * Referenced by: '<S3>/SPERTE_measurement_samples'
                                    */
  uint8_T MeasurementBlock_trigger_comman;
                              /* Mask Parameter: MeasurementBlock_trigger_comman
                               * Referenced by: '<S3>/SPERTE_measurement_trigger_command'
                               */
  uint8_T MeasurementBlock_triggertype;
                                 /* Mask Parameter: MeasurementBlock_triggertype
                                  * Referenced by: '<S3>/SPERTE_measurement_function'
                                  */
  real_T Gain7_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain7'
                                        */
  real_T Gain6_Gain;                   /* Expression: -1
                                        * Referenced by: '<Root>/Gain6'
                                        */
  real_T SFunction1_P1_Size[2];        /* Computed Parameter: SFunction1_P1_Size
                                        * Referenced by: '<S8>/S-Function1'
                                        */
  real_T SFunction1_P1;                /* Expression: 1
                                        * Referenced by: '<S8>/S-Function1'
                                        */
  real_T SFunction_P1_Size_f[2];      /* Computed Parameter: SFunction_P1_Size_f
                                       * Referenced by: '<S8>/S-Function'
                                       */
  real_T SFunction_P1;                 /* Expression: portid
                                        * Referenced by: '<S8>/S-Function'
                                        */
  real_T SFunction_P2_Size[2];         /* Computed Parameter: SFunction_P2_Size
                                        * Referenced by: '<S8>/S-Function'
                                        */
  real_T SFunction_P2;                 /* Expression: ectimeout
                                        * Referenced by: '<S8>/S-Function'
                                        */
  real_T ec_Ebox_P1_Size[2];           /* Computed Parameter: ec_Ebox_P1_Size
                                        * Referenced by: '<S7>/ec_Ebox'
                                        */
  real_T ec_Ebox_P1;                   /* Expression: link_id
                                        * Referenced by: '<S7>/ec_Ebox'
                                        */
  real_T count2rad_Gain;               /* Expression: (2*pi)/(4*500)
                                        * Referenced by: '<S1>/count2rad'
                                        */
  real_T Constant_Value[2];            /* Expression: [0,0]
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/100
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Quantizer2_Interval;          /* Expression: (2*pi)/(500*4)
                                        * Referenced by: '<Root>/Quantizer2'
                                        */
  real_T Gain_Gain_h;                  /* Expression: 0%0.007
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 0%0.000015
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Quantizer3_Interval;          /* Expression: (2*pi)/(500*4)
                                        * Referenced by: '<Root>/Quantizer3'
                                        */
  real_T Gain2_Gain;                   /* Expression: 0%0.0002705
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Gain5_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real_T Quantizer1_Interval;          /* Expression: (2*pi)/(500*4)
                                        * Referenced by: '<Root>/Quantizer1'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: 0.15
                                        * Referenced by: '<S2>/Gain1'
                                        */
  real_T Dctleadlag2_P1_Size[2];      /* Computed Parameter: Dctleadlag2_P1_Size
                                       * Referenced by: '<S2>/Dctleadlag2'
                                       */
  real_T Dctleadlag2_P1;               /* Expression: f_num
                                        * Referenced by: '<S2>/Dctleadlag2'
                                        */
  real_T Dctleadlag2_P2_Size[2];      /* Computed Parameter: Dctleadlag2_P2_Size
                                       * Referenced by: '<S2>/Dctleadlag2'
                                       */
  real_T Dctleadlag2_P2;               /* Expression: f_den
                                        * Referenced by: '<S2>/Dctleadlag2'
                                        */
  real_T Dctleadlag2_P3_Size[2];      /* Computed Parameter: Dctleadlag2_P3_Size
                                       * Referenced by: '<S2>/Dctleadlag2'
                                       */
  real_T Dctleadlag2_P3;               /* Expression: 0.001
                                        * Referenced by: '<S2>/Dctleadlag2'
                                        */
  real_T Dct1lowpass3_P1_Size[2];    /* Computed Parameter: Dct1lowpass3_P1_Size
                                      * Referenced by: '<S2>/Dct1lowpass3'
                                      */
  real_T Dct1lowpass3_P1;              /* Expression: f_den
                                        * Referenced by: '<S2>/Dct1lowpass3'
                                        */
  real_T Dct1lowpass3_P2_Size[2];    /* Computed Parameter: Dct1lowpass3_P2_Size
                                      * Referenced by: '<S2>/Dct1lowpass3'
                                      */
  real_T Dct1lowpass3_P2;              /* Expression: 0.001
                                        * Referenced by: '<S2>/Dct1lowpass3'
                                        */
  real_T Gain4_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain4'
                                        */
  real_T Noise_Mean;                   /* Expression: 0
                                        * Referenced by: '<Root>/Noise'
                                        */
  real_T Noise_StdDev;                 /* Computed Parameter: Noise_StdDev
                                        * Referenced by: '<Root>/Noise'
                                        */
  real_T Noise_Seed;                   /* Expression: 0
                                        * Referenced by: '<Root>/Noise'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 2.5
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -2.5
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Gain3_Gain;                   /* Expression: 0.0001
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real_T Constant1_Value[8];           /* Expression: [0,0,0,0,0,0,0,0]
                                        * Referenced by: '<S1>/Constant1'
                                        */
  uint8_T Selectencoder_CurrentSetting;
                             /* Computed Parameter: Selectencoder_CurrentSetting
                              * Referenced by: '<Root>/Select encoder'
                              */
};

/* Real-time Model Data Structure */
struct tag_RTM_Hardware_FFW_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[3];
    SimStruct childSFunctions[6];
    SimStruct *childSFunctionPtrs[6];
    struct _ssBlkInfo2 blkInfo2[6];
    struct _ssSFcnModelMethods2 methods2[6];
    struct _ssSFcnModelMethods3 methods3[6];
    struct _ssSFcnModelMethods4 methods4[6];
    struct _ssStatesInfo2 statesInfo2[6];
    ssPeriodicStatesInfo periodicStatesInfo[6];
    struct _ssPortInfo2 inputOutputPortInfo2[6];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      real_T const *UPtrs0[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[1];
      mxArray *params[1];
      struct _ssDWorkRecord dWork[3];
      struct _ssDWorkAuxRecord dWorkAux[3];
    } Sfcn1;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
    } Sfcn2;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[3];
      struct _ssInPortUnit inputPortUnits[3];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[3];
      real_T const *UPtrs0[2];
      real_T const *UPtrs1[2];
      real_T const *UPtrs2[8];
      struct _ssPortOutputs outputPortInfo[3];
      struct _ssOutPortUnit outputPortUnits[3];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[3];
      uint_T attribs[1];
      mxArray *params[1];
    } Sfcn3;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      real_T const *UPtrs0[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[3];
      mxArray *params[3];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn4;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssInPortUnit inputPortUnits[1];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[1];
      real_T const *UPtrs0[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[2];
      mxArray *params[2];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn5;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[3];
    time_T offsetTimesArray[3];
    int_T sampleTimeTaskIDArray[3];
    int_T sampleHitArray[3];
    int_T perTaskSampleHitsArray[9];
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Hardware_FFW_T Hardware_FFW_P;

/* Block signals (default storage) */
extern B_Hardware_FFW_T Hardware_FFW_B;

/* Block states (default storage) */
extern DW_Hardware_FFW_T Hardware_FFW_DW;

/* External function called from main */
extern void Hardware_FFW_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void Hardware_FFW_initialize(void);
extern void Hardware_FFW_step0(void);  /* Sample time: [0.0s, 0.0s] */
extern void Hardware_FFW_step2(void);  /* Sample time: [0.002s, 0.0s] */
extern void Hardware_FFW_step(int_T tid);
extern void Hardware_FFW_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Hardware_FFW_T *const Hardware_FFW_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Buffer' : Eliminate redundant signal conversion block
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Hardware_FFW'
 * '<S1>'   : 'Hardware_FFW/Fourth Order Motion System'
 * '<S2>'   : 'Hardware_FFW/Load_FFW_5Hz'
 * '<S3>'   : 'Hardware_FFW/Measurement Block'
 * '<S4>'   : 'Hardware_FFW/Real-time scope'
 * '<S5>'   : 'Hardware_FFW/Ref power'
 * '<S6>'   : 'Hardware_FFW/Subsystem'
 * '<S7>'   : 'Hardware_FFW/Fourth Order Motion System/Ethercat E-box'
 * '<S8>'   : 'Hardware_FFW/Fourth Order Motion System/Ethercat Supervisor'
 * '<S9>'   : 'Hardware_FFW/Measurement Block/SPERTE_measurement_function'
 */
#endif                                 /* Hardware_FFW_h_ */
