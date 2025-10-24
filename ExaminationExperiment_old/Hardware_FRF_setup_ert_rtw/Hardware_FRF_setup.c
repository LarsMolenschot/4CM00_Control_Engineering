/*
 * Hardware_FRF_setup.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Hardware_FRF_setup".
 *
 * Model version              : 14.17
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Oct 21 09:41:56 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (32-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Hardware_FRF_setup.h"
#include "Hardware_FRF_setup_types.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "Hardware_FRF_setup_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Named constants for MATLAB Function: '<S3>/SPERTE_measurement_function' */
#define Hardware_FRF_setup_CALL_EVENT  (-1)

/* Block signals (default storage) */
B_Hardware_FRF_setup_T Hardware_FRF_setup_B;

/* Block states (default storage) */
DW_Hardware_FRF_setup_T Hardware_FRF_setup_DW;

/* Real-time model */
static RT_MODEL_Hardware_FRF_setup_T Hardware_FRF_setup_M_;
RT_MODEL_Hardware_FRF_setup_T *const Hardware_FRF_setup_M =
  &Hardware_FRF_setup_M_;

/* Forward declaration for local functions */
static void Hardware_FRF_set_emxInit_char_T(emxArray_char_T_Hardware_FRF__T
  **pEmxArray, int32_T numDimensions);
static void Hardwa_emxEnsureCapacity_char_T(emxArray_char_T_Hardware_FRF__T
  *emxArray, int32_T oldNumel);
static void Hardware_FRF_set_emxFree_char_T(emxArray_char_T_Hardware_FRF__T
  **pEmxArray);
static int8_T Hardware_FRF_setup_filedata(void);
static int8_T Hardware_FRF_setup_cfopen(const emxArray_char_T_Hardware_FRF__T
  *cfilename, const char_T *cpermission);
static int32_T Hardware_FRF_setup_cfclose(real_T fid);
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 * 0 - success
 * 1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void Hardware_FRF_setup_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(Hardware_FRF_setup_M, 2));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (Hardware_FRF_setup_M->Timing.TaskCounters.TID[1] == 0) {
    Hardware_FRF_setup_M->Timing.RateInteraction.TID1_2 =
      (Hardware_FRF_setup_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    Hardware_FRF_setup_M->Timing.perTaskSampleHits[5] =
      Hardware_FRF_setup_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Hardware_FRF_setup_M->Timing.TaskCounters.TID[2])++;
  if ((Hardware_FRF_setup_M->Timing.TaskCounters.TID[2]) > 7) {/* Sample time: [0.002s, 0.0s] */
    Hardware_FRF_setup_M->Timing.TaskCounters.TID[2] = 0;
  }
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void Hardware_FRF_set_emxInit_char_T(emxArray_char_T_Hardware_FRF__T
  **pEmxArray, int32_T numDimensions)
{
  emxArray_char_T_Hardware_FRF__T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_char_T_Hardware_FRF__T *)malloc(sizeof
    (emxArray_char_T_Hardware_FRF__T));
  emxArray = *pEmxArray;
  emxArray->data = (char_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)malloc(sizeof(int32_T) * (uint32_T)numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void Hardwa_emxEnsureCapacity_char_T(emxArray_char_T_Hardware_FRF__T
  *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = malloc((uint32_T)i * sizeof(char_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(char_T) * (uint32_T)oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = (char_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void Hardware_FRF_set_emxFree_char_T(emxArray_char_T_Hardware_FRF__T
  **pEmxArray)
{
  if (*pEmxArray != (emxArray_char_T_Hardware_FRF__T *)NULL) {
    if (((*pEmxArray)->data != (char_T *)NULL) && (*pEmxArray)->canFreeData) {
      free((*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_char_T_Hardware_FRF__T *)NULL;
  }
}

/* Function for MATLAB Function: '<S3>/SPERTE_measurement_function' */
static int8_T Hardware_FRF_setup_filedata(void)
{
  int32_T k;
  int8_T f;
  boolean_T exitg1;
  f = 0;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k - 1 < 20)) {
    if (Hardware_FRF_setup_DW.eml_openfiles[(int8_T)k - 1] == NULL) {
      f = (int8_T)k;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/* Function for MATLAB Function: '<S3>/SPERTE_measurement_function' */
static int8_T Hardware_FRF_setup_cfopen(const emxArray_char_T_Hardware_FRF__T
  *cfilename, const char_T *cpermission)
{
  FILE *filestar;
  emxArray_char_T_Hardware_FRF__T *ccfilename;
  int32_T loop_ub;
  int8_T fileid;
  int8_T j;
  fileid = -1;
  j = Hardware_FRF_setup_filedata();
  if (j >= 1) {
    Hardware_FRF_set_emxInit_char_T(&ccfilename, 2);
    loop_ub = ccfilename->size[0] * ccfilename->size[1];
    ccfilename->size[0] = 1;
    ccfilename->size[1] = cfilename->size[1] + 1;
    Hardwa_emxEnsureCapacity_char_T(ccfilename, loop_ub);
    loop_ub = cfilename->size[1];
    if (loop_ub - 1 >= 0) {
      memcpy(&ccfilename->data[0], &cfilename->data[0], (uint32_T)loop_ub *
             sizeof(char_T));
    }

    ccfilename->data[cfilename->size[1]] = '\x00';
    filestar = fopen(&ccfilename->data[0], cpermission);
    Hardware_FRF_set_emxFree_char_T(&ccfilename);
    if (filestar != NULL) {
      Hardware_FRF_setup_DW.eml_openfiles[j - 1] = filestar;
      Hardware_FRF_setup_DW.eml_autoflush[j - 1] = true;
      loop_ub = j + 2;
      if (j + 2 > 127) {
        loop_ub = 127;
      }

      fileid = (int8_T)loop_ub;
    }
  }

  return fileid;
}

/* Function for MATLAB Function: '<S3>/SPERTE_measurement_function' */
static int32_T Hardware_FRF_setup_cfclose(real_T fid)
{
  FILE *f;
  int32_T cst;
  int32_T st;
  int8_T b_fileid;
  int8_T fileid;
  st = -1;
  fileid = (int8_T)fid;
  if (((int8_T)fid < 0) || (fid != (int8_T)fid)) {
    fileid = -1;
  }

  b_fileid = fileid;
  if (fileid < 0) {
    b_fileid = -1;
  }

  if (b_fileid >= 3) {
    f = Hardware_FRF_setup_DW.eml_openfiles[b_fileid - 3];
  } else if (b_fileid == 0) {
    f = stdin;
  } else if (b_fileid == 1) {
    f = stdout;
  } else if (b_fileid == 2) {
    f = stderr;
  } else {
    f = NULL;
  }

  if ((f != NULL) && (fileid >= 3)) {
    cst = fclose(f);
    if (cst == 0) {
      st = 0;
      Hardware_FRF_setup_DW.eml_openfiles[fileid - 3] = NULL;
      Hardware_FRF_setup_DW.eml_autoflush[fileid - 3] = true;
    }
  }

  return st;
}

/* Model step function for TID0 */
void Hardware_FRF_setup_step0(void)    /* Sample time: [0.0s, 0.0s] */
{
  FILE *f;
  size_t bytesOutSizet;
  emxArray_char_T_Hardware_FRF__T *str;
  emxArray_char_T_Hardware_FRF__T *str_0;
  real_T rtb_Quantizer1;
  real_T rtb_Quantizer3;
  real_T rtb_Selectencoder;
  real_T y;
  int32_T nbytes;
  int32_T tmp;
  real32_T xout[5];
  int8_T b_fileid;
  boolean_T autoflush;

  {                                    /* Sample time: [0.0s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (getTiming): '<S8>/S-Function1' */

  /* Level2 S-Function Block: '<S8>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* ToFile: '<S8>/To File ' */
  if (1 ) {
    {
      if (!(++Hardware_FRF_setup_DW.ToFile_IWORK.Decimation % 1) &&
          (Hardware_FRF_setup_DW.ToFile_IWORK.Count * (1 + 1)) + 1 < 100000000 )
      {
        FILE *fp = (FILE *) Hardware_FRF_setup_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          Hardware_FRF_setup_DW.ToFile_IWORK.Decimation = 0;
          u[0] = Hardware_FRF_setup_M->Timing.t[1];
          u[1] = Hardware_FRF_setup_B.SFunction1;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(Hardware_FRF_setup_M,
                              "Error writing to MAT-file Ts_meas.mat");
            return;
          }

          if (((++Hardware_FRF_setup_DW.ToFile_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file Ts_meas.mat.\n");
          }
        }
      }
    }
  }

  /* S-Function (ec_Supervisor): '<S8>/S-Function' */

  /* Level2 S-Function Block: '<S8>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* S-Function (ec_Ebox): '<S7>/ec_Ebox' */

  /* Level2 S-Function Block: '<S7>/ec_Ebox' (ec_Ebox) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* Constant: '<S5>/Start setpoint' */
  Hardware_FRF_setup_B.Startsetpoint = Hardware_FRF_setup_P.Refpower_stat;

  /* S-Function (ref3b): '<S6>/S-Function' */

  /* Level2 S-Function Block: '<S6>/S-Function' (ref3b) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[3];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Constant: '<S1>/Constant'
   */
  Hardware_FRF_setup_B.Gain[0] = Hardware_FRF_setup_P.Gain_Gain *
    Hardware_FRF_setup_P.Constant_Value[0];
  Hardware_FRF_setup_B.Gain[1] = Hardware_FRF_setup_P.Gain_Gain *
    Hardware_FRF_setup_P.Constant_Value[1];

  /* RandomNumber: '<Root>/Noise' */
  Hardware_FRF_setup_B.Noise = Hardware_FRF_setup_DW.NextOutput;

  /* Quantizer: '<Root>/Quantizer2' */
  rtb_Quantizer3 = rt_roundd_snf(Hardware_FRF_setup_B.SFunction_c[1] /
    Hardware_FRF_setup_P.Quantizer2_Interval) *
    Hardware_FRF_setup_P.Quantizer2_Interval;

  /* ManualSwitch: '<Root>/Select encoder' incorporates:
   *  Gain: '<Root>/Gain6'
   *  Gain: '<Root>/Gain7'
   *  Gain: '<S1>/count2rad'
   */
  if (Hardware_FRF_setup_P.Selectencoder_CurrentSetting == 1) {
    rtb_Selectencoder = Hardware_FRF_setup_P.count2rad_Gain *
      Hardware_FRF_setup_B.ec_Ebox_o2[0] * Hardware_FRF_setup_P.Gain7_Gain;
  } else {
    rtb_Selectencoder = Hardware_FRF_setup_P.count2rad_Gain *
      Hardware_FRF_setup_B.ec_Ebox_o2[1] * Hardware_FRF_setup_P.Gain6_Gain;
  }

  /* End of ManualSwitch: '<Root>/Select encoder' */

  /* Quantizer: '<Root>/Quantizer1' */
  rtb_Quantizer1 = rt_roundd_snf(Hardware_FRF_setup_B.SFunction_c[2] /
    Hardware_FRF_setup_P.Quantizer1_Interval) *
    Hardware_FRF_setup_P.Quantizer1_Interval;

  /* Sum: '<Root>/Sum' */
  Hardware_FRF_setup_B.Sum = rtb_Quantizer1 - rtb_Selectencoder;

  /* Gain: '<S2>/Gain1' */
  Hardware_FRF_setup_B.Gain1 = Hardware_FRF_setup_P.Gain1_Gain_a *
    Hardware_FRF_setup_B.Sum;

  /* S-Function (dleadlag): '<S2>/Dctleadlag2' */

  /* Level2 S-Function Block: '<S2>/Dctleadlag2' (dleadlag) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[4];
    sfcnOutputs(rts,0);
  }

  /* S-Function (dlowpass1): '<S2>/Dct1lowpass3' */

  /* Level2 S-Function Block: '<S2>/Dct1lowpass3' (dlowpass1) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[5];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<Root>/Gain4' */
  Hardware_FRF_setup_B.Gain4 = Hardware_FRF_setup_P.Gain4_Gain *
    Hardware_FRF_setup_B.Dct1lowpass3;

  /* Signum: '<Root>/Sign' */
  if (rtIsNaN(rtb_Quantizer3)) {
    y = (rtNaN);
  } else if (rtb_Quantizer3 < 0.0) {
    y = -1.0;
  } else {
    y = (rtb_Quantizer3 > 0.0);
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain5'
   *  Quantizer: '<Root>/Quantizer3'
   *  Signum: '<Root>/Sign'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<Root>/Sum4'
   */
  rtb_Quantizer3 = (((rt_roundd_snf(Hardware_FRF_setup_B.SFunction_c[0] /
    Hardware_FRF_setup_P.Quantizer3_Interval) *
                      Hardware_FRF_setup_P.Quantizer3_Interval *
                      Hardware_FRF_setup_P.Gain2_Gain +
                      Hardware_FRF_setup_P.Gain1_Gain * rtb_Quantizer3) +
                     Hardware_FRF_setup_P.Gain_Gain_h * y) *
                    Hardware_FRF_setup_P.Gain5_Gain + Hardware_FRF_setup_B.Gain4)
    + Hardware_FRF_setup_B.Noise;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Quantizer3 > Hardware_FRF_setup_P.Saturation_UpperSat) {
    y = Hardware_FRF_setup_P.Saturation_UpperSat;
  } else if (rtb_Quantizer3 < Hardware_FRF_setup_P.Saturation_LowerSat) {
    y = Hardware_FRF_setup_P.Saturation_LowerSat;
  } else {
    y = rtb_Quantizer3;
  }

  /* Saturate: '<S7>/Saturation' */
  if (y > Hardware_FRF_setup_P.Saturation_UpperSat_d) {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[0] =
      Hardware_FRF_setup_P.Saturation_UpperSat_d;
  } else if (y < Hardware_FRF_setup_P.Saturation_LowerSat_e) {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[0] =
      Hardware_FRF_setup_P.Saturation_LowerSat_e;
  } else {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[0] = y;
  }

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  if (Hardware_FRF_setup_P.Constant2_Value >
      Hardware_FRF_setup_P.Saturation_UpperSat) {
    y = Hardware_FRF_setup_P.Saturation_UpperSat;
  } else if (Hardware_FRF_setup_P.Constant2_Value <
             Hardware_FRF_setup_P.Saturation_LowerSat) {
    y = Hardware_FRF_setup_P.Saturation_LowerSat;
  } else {
    y = Hardware_FRF_setup_P.Constant2_Value;
  }

  /* Saturate: '<S7>/Saturation' */
  if (y > Hardware_FRF_setup_P.Saturation_UpperSat_d) {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[1] =
      Hardware_FRF_setup_P.Saturation_UpperSat_d;
  } else if (y < Hardware_FRF_setup_P.Saturation_LowerSat_e) {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[1] =
      Hardware_FRF_setup_P.Saturation_LowerSat_e;
  } else {
    /* Saturate: '<S7>/Saturation' */
    Hardware_FRF_setup_B.Saturation[1] = y;
  }

  /* MATLAB Function: '<S3>/SPERTE_measurement_function' incorporates:
   *  Constant: '<S3>/SPERTE_measurement_samples'
   *  Constant: '<S3>/SPERTE_measurement_trigger_command'
   *  SignalConversion generated from: '<S9>/ SFunction '
   */
  Hardware_FRF_setup_DW.sfEvent = Hardware_FRF_setup_CALL_EVENT;
  if ((((Hardware_FRF_setup_P.MeasurementBlock_triggertype == 1) &&
        (Hardware_FRF_setup_P.MeasurementBlock_trigger_comman == 1)) ||
       ((Hardware_FRF_setup_P.MeasurementBlock_triggertype == 2) &&
        (Hardware_FRF_setup_P.MeasurementBlock_trigger_comman == 1))) &&
      (Hardware_FRF_setup_DW.busy != 1)) {
    nbytes = (int32_T)snprintf(NULL, 0, "measurement_%d.bin",
      Hardware_FRF_setup_DW.NF) + 1;
    Hardware_FRF_set_emxInit_char_T(&str, 2);
    tmp = str->size[0] * str->size[1];
    str->size[0] = 1;
    str->size[1] = nbytes;
    Hardwa_emxEnsureCapacity_char_T(str, tmp);
    snprintf(&str->data[0], (size_t)nbytes, "measurement_%d.bin",
             Hardware_FRF_setup_DW.NF);
    if (nbytes - 1 < 1) {
      nbytes = -1;
    } else {
      nbytes -= 2;
    }

    Hardware_FRF_set_emxInit_char_T(&str_0, 2);
    tmp = str_0->size[0] * str_0->size[1];
    str_0->size[0] = 1;
    str_0->size[1] = nbytes + 1;
    Hardwa_emxEnsureCapacity_char_T(str_0, tmp);
    if (nbytes >= 0) {
      memcpy(&str_0->data[0], &str->data[0], (uint32_T)(nbytes + 1) * sizeof
             (char_T));
    }

    Hardware_FRF_set_emxFree_char_T(&str);
    b_fileid = Hardware_FRF_setup_cfopen(str_0, "wb");
    Hardware_FRF_set_emxFree_char_T(&str_0);
    Hardware_FRF_setup_DW.fileID = b_fileid;
    nbytes = Hardware_FRF_setup_DW.NF + 1;
    if (Hardware_FRF_setup_DW.NF + 1 > 32767) {
      nbytes = 32767;
    }

    Hardware_FRF_setup_DW.NF = (int16_T)nbytes;
    Hardware_FRF_setup_DW.busy = 1U;
    Hardware_FRF_setup_DW.NS = 0U;
  }

  if (Hardware_FRF_setup_DW.busy == 1) {
    if (Hardware_FRF_setup_DW.NS <
        Hardware_FRF_setup_P.MeasurementBlock_N_samples) {
      b_fileid = (int8_T)Hardware_FRF_setup_DW.fileID;
      if (((int8_T)Hardware_FRF_setup_DW.fileID < 0) ||
          (Hardware_FRF_setup_DW.fileID != (int8_T)Hardware_FRF_setup_DW.fileID))
      {
        b_fileid = -1;
      }

      if (b_fileid >= 3) {
        autoflush = Hardware_FRF_setup_DW.eml_autoflush[b_fileid - 3];
        f = Hardware_FRF_setup_DW.eml_openfiles[b_fileid - 3];
      } else if (b_fileid == 0) {
        f = stdin;
        autoflush = true;
      } else if (b_fileid == 1) {
        f = stdout;
        autoflush = true;
      } else if (b_fileid == 2) {
        f = stderr;
        autoflush = true;
      } else {
        f = NULL;
        autoflush = true;
      }

      if (!(Hardware_FRF_setup_DW.fileID != 0.0)) {
        f = NULL;
      }

      if (!(f == NULL)) {
        xout[0] = (real32_T)Hardware_FRF_setup_B.Noise;
        xout[1] = (real32_T)rtb_Selectencoder;
        xout[2] = (real32_T)rtb_Quantizer3;
        xout[3] = (real32_T)Hardware_FRF_setup_B.Sum;
        xout[4] = (real32_T)rtb_Quantizer1;
        bytesOutSizet = fwrite(&xout[0], sizeof(real32_T), (size_t)5, f);
        if (((real_T)bytesOutSizet > 0.0) && autoflush) {
          fflush(f);
        }
      }

      Hardware_FRF_setup_DW.NS++;
    } else {
      Hardware_FRF_setup_cfclose(Hardware_FRF_setup_DW.fileID);
      Hardware_FRF_setup_DW.busy = 0U;
      Hardware_FRF_setup_DW.NS = 0U;
    }
  }

  /* End of MATLAB Function: '<S3>/SPERTE_measurement_function' */

  /* Gain: '<Root>/Gain3' */
  Hardware_FRF_setup_B.Gain3 = Hardware_FRF_setup_P.Gain3_Gain *
    Hardware_FRF_setup_B.SFunction_c[0];

  /* RateTransition: '<S4>/Downsample' */
  if (Hardware_FRF_setup_M->Timing.RateInteraction.TID1_2) {
    Hardware_FRF_setup_DW.Downsample_Buffer[0] = Hardware_FRF_setup_B.Gain3;
    Hardware_FRF_setup_DW.Downsample_Buffer[1] = Hardware_FRF_setup_B.Sum;
  }

  /* End of RateTransition: '<S4>/Downsample' */

  /* Constant: '<S1>/Constant1' */
  memcpy(&Hardware_FRF_setup_B.Constant1[0],
         &Hardware_FRF_setup_P.Constant1_Value[0], sizeof(real_T) << 3U);

  /* Update for RandomNumber: '<Root>/Noise' */
  Hardware_FRF_setup_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
    (&Hardware_FRF_setup_DW.RandSeed) * Hardware_FRF_setup_P.Noise_StdDev +
    Hardware_FRF_setup_P.Noise_Mean;

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Hardware_FRF_setup_M->Timing.clockTick0)) {
    ++Hardware_FRF_setup_M->Timing.clockTickH0;
  }

  Hardware_FRF_setup_M->Timing.t[0] = Hardware_FRF_setup_M->Timing.clockTick0 *
    Hardware_FRF_setup_M->Timing.stepSize0 +
    Hardware_FRF_setup_M->Timing.clockTickH0 *
    Hardware_FRF_setup_M->Timing.stepSize0 * 4294967296.0;

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Hardware_FRF_setup_M->Timing.clockTick1)) {
    ++Hardware_FRF_setup_M->Timing.clockTickH1;
  }

  Hardware_FRF_setup_M->Timing.t[1] = Hardware_FRF_setup_M->Timing.clockTick1 *
    Hardware_FRF_setup_M->Timing.stepSize1 +
    Hardware_FRF_setup_M->Timing.clockTickH1 *
    Hardware_FRF_setup_M->Timing.stepSize1 * 4294967296.0;
}

/* Model step function for TID2 */
void Hardware_FRF_setup_step2(void)    /* Sample time: [0.002s, 0.0s] */
{
  /* RateTransition: '<S4>/Downsample' */
  Hardware_FRF_setup_B.Downsample[0] = Hardware_FRF_setup_DW.Downsample_Buffer[0];
  Hardware_FRF_setup_B.Downsample[1] = Hardware_FRF_setup_DW.Downsample_Buffer[1];

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.002, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  Hardware_FRF_setup_M->Timing.clockTick2++;
  if (!Hardware_FRF_setup_M->Timing.clockTick2) {
    Hardware_FRF_setup_M->Timing.clockTickH2++;
  }
}

/* Use this function only if you need to maintain compatibility with an existing static main program. */
void Hardware_FRF_setup_step(int_T tid)
{
  switch (tid) {
   case 0 :
    Hardware_FRF_setup_step0();
    break;

   case 2 :
    Hardware_FRF_setup_step2();
    break;

   default :
    /* do nothing */
    break;
  }
}

/* Model initialize function */
void Hardware_FRF_setup_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Hardware_FRF_setup_M, 0,
                sizeof(RT_MODEL_Hardware_FRF_setup_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Hardware_FRF_setup_M->solverInfo,
                          &Hardware_FRF_setup_M->Timing.simTimeStep);
    rtsiSetTPtr(&Hardware_FRF_setup_M->solverInfo, &rtmGetTPtr
                (Hardware_FRF_setup_M));
    rtsiSetStepSizePtr(&Hardware_FRF_setup_M->solverInfo,
                       &Hardware_FRF_setup_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Hardware_FRF_setup_M->solverInfo, (&rtmGetErrorStatus
      (Hardware_FRF_setup_M)));
    rtsiSetRTModelPtr(&Hardware_FRF_setup_M->solverInfo, Hardware_FRF_setup_M);
  }

  rtsiSetSimTimeStep(&Hardware_FRF_setup_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Hardware_FRF_setup_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&Hardware_FRF_setup_M->solverInfo, false);
  rtsiSetSolverName(&Hardware_FRF_setup_M->solverInfo,"FixedStepDiscrete");
  Hardware_FRF_setup_M->solverInfoPtr = (&Hardware_FRF_setup_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Hardware_FRF_setup_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    Hardware_FRF_setup_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Hardware_FRF_setup_M->Timing.sampleTimes =
      (&Hardware_FRF_setup_M->Timing.sampleTimesArray[0]);
    Hardware_FRF_setup_M->Timing.offsetTimes =
      (&Hardware_FRF_setup_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Hardware_FRF_setup_M->Timing.sampleTimes[0] = (0.0);
    Hardware_FRF_setup_M->Timing.sampleTimes[1] = (0.00025);
    Hardware_FRF_setup_M->Timing.sampleTimes[2] = (0.002);

    /* task offsets */
    Hardware_FRF_setup_M->Timing.offsetTimes[0] = (0.0);
    Hardware_FRF_setup_M->Timing.offsetTimes[1] = (0.0);
    Hardware_FRF_setup_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Hardware_FRF_setup_M, &Hardware_FRF_setup_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Hardware_FRF_setup_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      Hardware_FRF_setup_M->Timing.perTaskSampleHitsArray;
    Hardware_FRF_setup_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Hardware_FRF_setup_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Hardware_FRF_setup_M, -1);
  Hardware_FRF_setup_M->Timing.stepSize0 = 0.00025;
  Hardware_FRF_setup_M->Timing.stepSize1 = 0.00025;

  /* External mode info */
  Hardware_FRF_setup_M->Sizes.checksums[0] = (1833252448U);
  Hardware_FRF_setup_M->Sizes.checksums[1] = (3715633772U);
  Hardware_FRF_setup_M->Sizes.checksums[2] = (4286213816U);
  Hardware_FRF_setup_M->Sizes.checksums[3] = (2562326530U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    Hardware_FRF_setup_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Hardware_FRF_setup_M->extModeInfo,
      &Hardware_FRF_setup_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Hardware_FRF_setup_M->extModeInfo,
                        Hardware_FRF_setup_M->Sizes.checksums);
    rteiSetTPtr(Hardware_FRF_setup_M->extModeInfo, rtmGetTPtr
                (Hardware_FRF_setup_M));
  }

  Hardware_FRF_setup_M->solverInfoPtr = (&Hardware_FRF_setup_M->solverInfo);
  Hardware_FRF_setup_M->Timing.stepSize = (0.00025);
  rtsiSetFixedStepSize(&Hardware_FRF_setup_M->solverInfo, 0.00025);
  rtsiSetSolverMode(&Hardware_FRF_setup_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  (void) memset(((void *) &Hardware_FRF_setup_B), 0,
                sizeof(B_Hardware_FRF_setup_T));

  /* states (dwork) */
  (void) memset((void *)&Hardware_FRF_setup_DW, 0,
                sizeof(DW_Hardware_FRF_setup_T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Hardware_FRF_setup_M->NonInlinedSFcns.sfcnInfo;
    Hardware_FRF_setup_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Hardware_FRF_setup_M)));
    Hardware_FRF_setup_M->Sizes.numSampTimes = (3);
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &Hardware_FRF_setup_M->Sizes.numSampTimes);
    Hardware_FRF_setup_M->NonInlinedSFcns.taskTimePtrs[0] = (&rtmGetTPtr
      (Hardware_FRF_setup_M)[0]);
    Hardware_FRF_setup_M->NonInlinedSFcns.taskTimePtrs[1] = (&rtmGetTPtr
      (Hardware_FRF_setup_M)[1]);
    Hardware_FRF_setup_M->NonInlinedSFcns.taskTimePtrs[2] = (&rtmGetTPtr
      (Hardware_FRF_setup_M)[2]);
    rtssSetTPtrPtr(sfcnInfo,Hardware_FRF_setup_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Hardware_FRF_setup_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Hardware_FRF_setup_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (Hardware_FRF_setup_M));
    rtssSetStepSizePtr(sfcnInfo, &Hardware_FRF_setup_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Hardware_FRF_setup_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Hardware_FRF_setup_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &Hardware_FRF_setup_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Hardware_FRF_setup_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Hardware_FRF_setup_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Hardware_FRF_setup_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Hardware_FRF_setup_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Hardware_FRF_setup_M->solverInfoPtr);
  }

  Hardware_FRF_setup_M->Sizes.numSFcns = (6);

  /* register each child */
  {
    (void) memset((void *)&Hardware_FRF_setup_M->
                  NonInlinedSFcns.childSFunctions[0], 0,
                  6*sizeof(SimStruct));
    Hardware_FRF_setup_M->childSfunctions =
      (&Hardware_FRF_setup_M->NonInlinedSFcns.childSFunctionPtrs[0]);

    {
      int_T i;
      for (i = 0; i < 6; i++) {
        Hardware_FRF_setup_M->childSfunctions[i] =
          (&Hardware_FRF_setup_M->NonInlinedSFcns.childSFunctions[i]);
      }
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S8>/S-Function1 (getTiming) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_FRF_setup_B.SFunction1));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function1");
      ssSetPath(rts,
                "Hardware_FRF_setup/Fourth Order Motion System/Ethercat Supervisor/S-Function1");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Hardware_FRF_setup_P.SFunction1_P1_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &Hardware_FRF_setup_DW.SFunction1_RWORK[0]);
      ssSetIWork(rts, (int_T *) &Hardware_FRF_setup_DW.SFunction1_IWORK);
      ssSetPWork(rts, (void **) &Hardware_FRF_setup_DW.SFunction1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 3);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_FRF_setup_DW.SFunction1_RWORK[0]);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Hardware_FRF_setup_DW.SFunction1_IWORK);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 2, 1);
        ssSetDWorkDataType(rts, 2,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 2, 0);
        ssSetDWork(rts, 2, &Hardware_FRF_setup_DW.SFunction1_PWORK);
      }

      /* registration */
      getTiming(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S8>/S-Function (ec_Supervisor) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_FRF_setup_B.SFunction));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function");
      ssSetPath(rts,
                "Hardware_FRF_setup/Fourth Order Motion System/Ethercat Supervisor/S-Function");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 2);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_FRF_setup_P.SFunction_P1_Size_f);
        ssSetSFcnParam(rts, 1, (mxArray*)Hardware_FRF_setup_P.SFunction_P2_Size);
      }

      /* registration */
      ec_Supervisor(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S7>/ec_Ebox (ec_Ebox) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[2]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 3);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        ssSetInputPortUnit(rts, 2, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);
        ssSetInputPortIsContinuousQuantity(rts, 2, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.UPtrs0;
          sfcnUPtrs[0] = Hardware_FRF_setup_B.Saturation;
          sfcnUPtrs[1] = &Hardware_FRF_setup_B.Saturation[1];
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 2);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.UPtrs1;
          sfcnUPtrs[0] = Hardware_FRF_setup_B.Gain;
          sfcnUPtrs[1] = &Hardware_FRF_setup_B.Gain[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.UPtrs2;

          {
            int_T i1;
            const real_T *u2 = Hardware_FRF_setup_B.Constant1;
            for (i1=0; i1 < 8; i1++) {
              sfcnUPtrs[i1] = &u2[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidthAsInt(rts, 2, 8);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 3);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        ssSetOutputPortUnit(rts, 2, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 2, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            Hardware_FRF_setup_B.ec_Ebox_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidthAsInt(rts, 1, 2);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            Hardware_FRF_setup_B.ec_Ebox_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidthAsInt(rts, 2, 8);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            Hardware_FRF_setup_B.ec_Ebox_o3));
        }
      }

      /* path info */
      ssSetModelName(rts, "ec_Ebox");
      ssSetPath(rts,
                "Hardware_FRF_setup/Fourth Order Motion System/Ethercat E-box/ec_Ebox");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Hardware_FRF_setup_P.ec_Ebox_P1_Size);
      }

      /* registration */
      ec_Ebox(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S6>/S-Function (ref3b) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[3];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[3]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[3]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [3]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [3]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [3]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[3]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[3]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.UPtrs0;
          sfcnUPtrs[0] = &Hardware_FRF_setup_B.Startsetpoint;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 3);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            Hardware_FRF_setup_B.SFunction_c));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function");
      ssSetPath(rts, "Hardware_FRF_setup/Subsystem/S-Function");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Hardware_FRF_setup_P.SFunction_P1_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &Hardware_FRF_setup_DW.SFunction_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn3.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 50);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_FRF_setup_DW.SFunction_RWORK[0]);
      }

      /* registration */
      ref3b(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S2>/Dctleadlag2 (dleadlag) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[4];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[4]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[4]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [4]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [4]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [4]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[4]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[4]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.UPtrs0;
          sfcnUPtrs[0] = &Hardware_FRF_setup_B.Gain1;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_FRF_setup_B.Dctleadlag2));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dctleadlag2");
      ssSetPath(rts, "Hardware_FRF_setup/Load_FFW_5Hz/Dctleadlag2");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.params;
        ssSetSFcnParamsCount(rts, 3);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_FRF_setup_P.Dctleadlag2_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_FRF_setup_P.Dctleadlag2_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Hardware_FRF_setup_P.Dctleadlag2_P3_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &Hardware_FRF_setup_DW.Dctleadlag2_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn4.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_FRF_setup_DW.Dctleadlag2_RWORK[0]);
      }

      /* registration */
      dleadlag(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }

    /* Level2 S-Function Block: Hardware_FRF_setup/<S2>/Dct1lowpass3 (dlowpass1) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[5];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnOffset;
      int_T *sfcnTsMap = Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.blkInfo2[5]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[5]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods2
                           [5]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods3
                           [5]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Hardware_FRF_setup_M->NonInlinedSFcns.methods4
                           [5]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Hardware_FRF_setup_M->
                         NonInlinedSFcns.statesInfo2[5]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[5]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.UPtrs0;
          sfcnUPtrs[0] = &Hardware_FRF_setup_B.Dctleadlag2;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_FRF_setup_B.Dct1lowpass3));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dct1lowpass3");
      ssSetPath(rts, "Hardware_FRF_setup/Load_FFW_5Hz/Dct1lowpass3");
      ssSetRTModel(rts,Hardware_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.params;
        ssSetSFcnParamsCount(rts, 2);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_FRF_setup_P.Dct1lowpass3_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_FRF_setup_P.Dct1lowpass3_P2_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &Hardware_FRF_setup_DW.Dct1lowpass3_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_FRF_setup_M->NonInlinedSFcns.Sfcn5.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_FRF_setup_DW.Dct1lowpass3_RWORK[0]);
      }

      /* registration */
      dlowpass1(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }
  }

  /* Start for S-Function (getTiming): '<S8>/S-Function1' */
  /* Level2 S-Function Block: '<S8>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for ToFile: '<S8>/To File ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Ts_meas.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Hardware_FRF_setup_M,
                        "Error creating .mat file Ts_meas.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "Ts_meas")) {
      fclose(fp);
      rtmSetErrorStatus(Hardware_FRF_setup_M,
                        "Error writing mat file header to file Ts_meas.mat");
      return;
    }

    Hardware_FRF_setup_DW.ToFile_IWORK.Count = 0;
    Hardware_FRF_setup_DW.ToFile_IWORK.Decimation = -1;
    Hardware_FRF_setup_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (ec_Supervisor): '<S8>/S-Function' */
  /* Level2 S-Function Block: '<S8>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for Constant: '<S5>/Start setpoint' */
  Hardware_FRF_setup_B.Startsetpoint = Hardware_FRF_setup_P.Refpower_stat;

  /* Start for S-Function (dleadlag): '<S2>/Dctleadlag2' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag2' (dleadlag) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[4];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (dlowpass1): '<S2>/Dct1lowpass3' */
  /* Level2 S-Function Block: '<S2>/Dct1lowpass3' (dlowpass1) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[5];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for Constant: '<S1>/Constant1' */
  memcpy(&Hardware_FRF_setup_B.Constant1[0],
         &Hardware_FRF_setup_P.Constant1_Value[0], sizeof(real_T) << 3U);

  {
    real_T tmp;
    int32_T i;
    uint32_T r;
    uint32_T t;
    uint32_T tseed;

    /* InitializeConditions for S-Function (ref3b): '<S6>/S-Function' */
    /* Level2 S-Function Block: '<S6>/S-Function' (ref3b) */
    {
      SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[3];
      sfcnInitializeConditions(rts);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }

    /* InitializeConditions for RandomNumber: '<Root>/Noise' */
    tmp = floor(Hardware_FRF_setup_P.Noise_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = tseed >> 16U;
    t = tseed & 32768U;
    Hardware_FRF_setup_DW.RandSeed = ((((tseed - (r << 16U)) + t) << 16U) + t) +
      r;
    if (Hardware_FRF_setup_DW.RandSeed < 1U) {
      Hardware_FRF_setup_DW.RandSeed = 1144108930U;
    } else if (Hardware_FRF_setup_DW.RandSeed > 2147483646U) {
      Hardware_FRF_setup_DW.RandSeed = 2147483646U;
    }

    Hardware_FRF_setup_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&Hardware_FRF_setup_DW.RandSeed) * Hardware_FRF_setup_P.Noise_StdDev +
      Hardware_FRF_setup_P.Noise_Mean;

    /* End of InitializeConditions for RandomNumber: '<Root>/Noise' */

    /* SystemInitialize for MATLAB Function: '<S3>/SPERTE_measurement_function' */
    for (i = 0; i < 20; i++) {
      Hardware_FRF_setup_DW.eml_autoflush[i] = false;
    }

    Hardware_FRF_setup_DW.eml_autoflush_not_empty = true;
    for (i = 0; i < 20; i++) {
      Hardware_FRF_setup_DW.eml_openfiles[i] = NULL;
    }

    Hardware_FRF_setup_DW.eml_openfiles_not_empty = true;
    Hardware_FRF_setup_DW.NF = 0;
    Hardware_FRF_setup_DW.NF_not_empty = true;
    Hardware_FRF_setup_DW.NS = 0U;
    Hardware_FRF_setup_DW.NS_not_empty = true;
    Hardware_FRF_setup_DW.fileID = 0.0;
    Hardware_FRF_setup_DW.fileID_not_empty = true;
    Hardware_FRF_setup_DW.busy = 0U;
    Hardware_FRF_setup_DW.busy_not_empty = true;
    Hardware_FRF_setup_DW.sfEvent = Hardware_FRF_setup_CALL_EVENT;

    /* End of SystemInitialize for MATLAB Function: '<S3>/SPERTE_measurement_function' */
  }
}

/* Model terminate function */
void Hardware_FRF_setup_terminate(void)
{
  /* Terminate for S-Function (getTiming): '<S8>/S-Function1' */
  /* Level2 S-Function Block: '<S8>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for ToFile: '<S8>/To File ' */
  {
    FILE *fp = (FILE *) Hardware_FRF_setup_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Ts_meas.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Hardware_FRF_setup_M,
                          "Error closing MAT-file Ts_meas.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Hardware_FRF_setup_M,
                          "Error reopening MAT-file Ts_meas.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           Hardware_FRF_setup_DW.ToFile_IWORK.Count, "Ts_meas")) {
        rtmSetErrorStatus(Hardware_FRF_setup_M,
                          "Error writing header for Ts_meas to MAT-file Ts_meas.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Hardware_FRF_setup_M,
                          "Error closing MAT-file Ts_meas.mat");
        return;
      }

      Hardware_FRF_setup_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (ec_Supervisor): '<S8>/S-Function' */
  /* Level2 S-Function Block: '<S8>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (ec_Ebox): '<S7>/ec_Ebox' */
  /* Level2 S-Function Block: '<S7>/ec_Ebox' (ec_Ebox) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[2];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (ref3b): '<S6>/S-Function' */
  /* Level2 S-Function Block: '<S6>/S-Function' (ref3b) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[3];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dleadlag): '<S2>/Dctleadlag2' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag2' (dleadlag) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[4];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dlowpass1): '<S2>/Dct1lowpass3' */
  /* Level2 S-Function Block: '<S2>/Dct1lowpass3' (dlowpass1) */
  {
    SimStruct *rts = Hardware_FRF_setup_M->childSfunctions[5];
    sfcnTerminate(rts);
  }
}
