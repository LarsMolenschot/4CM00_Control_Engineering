/*
 * Hardware_Openloop_FRF_setup.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Hardware_Openloop_FRF_setup".
 *
 * Model version              : 14.20
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Oct 21 13:19:38 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (32-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Hardware_Openloop_FRF_setup.h"
#include "Hardware_Openloop_FRF_setup_types.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "Hardware_Openloop_FRF_setup_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Named constants for MATLAB Function: '<S3>/SPERTE_measurement_function' */
#define Hardware_Openloop_FR_CALL_EVENT (-1)

/* Block signals (default storage) */
B_Hardware_Openloop_FRF_setup_T Hardware_Openloop_FRF_setup_B;

/* Block states (default storage) */
DW_Hardware_Openloop_FRF_setup_T Hardware_Openloop_FRF_setup_DW;

/* Real-time model */
static RT_MODEL_Hardware_Openloop_FRF_setup_T Hardware_Openloop_FRF_setup_M_;
RT_MODEL_Hardware_Openloop_FRF_setup_T *const Hardware_Openloop_FRF_setup_M =
  &Hardware_Openloop_FRF_setup_M_;

/* Forward declaration for local functions */
static void Hardware_Openloo_emxInit_char_T(emxArray_char_T_Hardware_Open_T
  **pEmxArray, int32_T numDimensions);
static void Hardwa_emxEnsureCapacity_char_T(emxArray_char_T_Hardware_Open_T
  *emxArray, int32_T oldNumel);
static void Hardware_Openloo_emxFree_char_T(emxArray_char_T_Hardware_Open_T
  **pEmxArray);
static int8_T Hardware_Openloop_FRF__filedata(void);
static int8_T Hardware_Openloop_FRF_se_cfopen(const
  emxArray_char_T_Hardware_Open_T *cfilename, const char_T *cpermission);
static int32_T Hardware_Openloop_FRF_s_cfclose(real_T fid);

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

static void Hardware_Openloo_emxInit_char_T(emxArray_char_T_Hardware_Open_T
  **pEmxArray, int32_T numDimensions)
{
  emxArray_char_T_Hardware_Open_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_char_T_Hardware_Open_T *)malloc(sizeof
    (emxArray_char_T_Hardware_Open_T));
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

static void Hardwa_emxEnsureCapacity_char_T(emxArray_char_T_Hardware_Open_T
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

static void Hardware_Openloo_emxFree_char_T(emxArray_char_T_Hardware_Open_T
  **pEmxArray)
{
  if (*pEmxArray != (emxArray_char_T_Hardware_Open_T *)NULL) {
    if (((*pEmxArray)->data != (char_T *)NULL) && (*pEmxArray)->canFreeData) {
      free((*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_char_T_Hardware_Open_T *)NULL;
  }
}

/* Function for MATLAB Function: '<S3>/SPERTE_measurement_function' */
static int8_T Hardware_Openloop_FRF__filedata(void)
{
  int32_T k;
  int8_T f;
  boolean_T exitg1;
  f = 0;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k - 1 < 20)) {
    if (Hardware_Openloop_FRF_setup_DW.eml_openfiles[(int8_T)k - 1] == NULL) {
      f = (int8_T)k;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/* Function for MATLAB Function: '<S3>/SPERTE_measurement_function' */
static int8_T Hardware_Openloop_FRF_se_cfopen(const
  emxArray_char_T_Hardware_Open_T *cfilename, const char_T *cpermission)
{
  FILE *filestar;
  emxArray_char_T_Hardware_Open_T *ccfilename;
  int32_T loop_ub;
  int8_T fileid;
  int8_T j;
  fileid = -1;
  j = Hardware_Openloop_FRF__filedata();
  if (j >= 1) {
    Hardware_Openloo_emxInit_char_T(&ccfilename, 2);
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
    Hardware_Openloo_emxFree_char_T(&ccfilename);
    if (filestar != NULL) {
      Hardware_Openloop_FRF_setup_DW.eml_openfiles[j - 1] = filestar;
      Hardware_Openloop_FRF_setup_DW.eml_autoflush[j - 1] = true;
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
static int32_T Hardware_Openloop_FRF_s_cfclose(real_T fid)
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
    f = Hardware_Openloop_FRF_setup_DW.eml_openfiles[b_fileid - 3];
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
      Hardware_Openloop_FRF_setup_DW.eml_openfiles[fileid - 3] = NULL;
      Hardware_Openloop_FRF_setup_DW.eml_autoflush[fileid - 3] = true;
    }
  }

  return st;
}

/* Model step function */
void Hardware_Openloop_FRF_setup_step(void)
{
  FILE *f;
  size_t bytesOutSizet;
  emxArray_char_T_Hardware_Open_T *str;
  emxArray_char_T_Hardware_Open_T *str_0;
  real_T y;
  int32_T i;
  int32_T tmp;
  real32_T xout[5];
  int8_T b_fileid;
  boolean_T autoflush;

  /* Constant: '<S1>/Constant1' */
  memcpy(&Hardware_Openloop_FRF_setup_B.Constant1[0],
         &Hardware_Openloop_FRF_setup_P.Constant1_Value[0], sizeof(real_T) << 3U);

  /* S-Function (getTiming): '<S5>/S-Function1' */

  /* Level2 S-Function Block: '<S5>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* ToFile: '<S5>/To File ' */
  {
    if (!(++Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Decimation % 1) &&
        (Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Count * (1 + 1)) + 1 <
        100000000 ) {
      FILE *fp = (FILE *) Hardware_Openloop_FRF_setup_DW.ToFile_PWORK.FilePtr;
      if (fp != (NULL)) {
        real_T u[1 + 1];
        Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Decimation = 0;
        u[0] = Hardware_Openloop_FRF_setup_M->Timing.t[0];
        u[1] = Hardware_Openloop_FRF_setup_B.SFunction1;
        if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
          rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                            "Error writing to MAT-file Ts_meas.mat");
          return;
        }

        if (((++Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Count) * (1 + 1))+1 >=
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

  /* S-Function (ec_Supervisor): '<S5>/S-Function' */

  /* Level2 S-Function Block: '<S5>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<S2>/Gain1' incorporates:
   *  RandomNumber: '<Root>/Noise'
   */
  Hardware_Openloop_FRF_setup_B.Gain1 = Hardware_Openloop_FRF_setup_P.Gain1_Gain
    * Hardware_Openloop_FRF_setup_DW.NextOutput;

  /* S-Function (dnotch): '<S2>/Dctnotch2' */

  /* Level2 S-Function Block: '<S2>/Dctnotch2' (dnotch) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* S-Function (dleadlag): '<S2>/Dctleadlag3' */

  /* Level2 S-Function Block: '<S2>/Dctleadlag3' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[3];
    sfcnOutputs(rts,0);
  }

  /* S-Function (dleadlag): '<S2>/Dctleadlag4' */

  /* Level2 S-Function Block: '<S2>/Dctleadlag4' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[4];
    sfcnOutputs(rts,0);
  }

  /* S-Function (dlowpass1): '<S2>/Dct1lowpass5' */

  /* Level2 S-Function Block: '<S2>/Dct1lowpass5' (dlowpass1) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[5];
    sfcnOutputs(rts,0);
  }

  /* S-Function (ec_Ebox): '<S4>/ec_Ebox' */

  /* Level2 S-Function Block: '<S4>/ec_Ebox' (ec_Ebox) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[6];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<S4>/Gain' incorporates:
   *  Constant: '<S1>/Constant'
   */
  Hardware_Openloop_FRF_setup_B.Gain[0] =
    Hardware_Openloop_FRF_setup_P.Gain_Gain *
    Hardware_Openloop_FRF_setup_P.Constant_Value[0];
  Hardware_Openloop_FRF_setup_B.Gain[1] =
    Hardware_Openloop_FRF_setup_P.Gain_Gain *
    Hardware_Openloop_FRF_setup_P.Constant_Value[1];

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Sum: '<Root>/Sum1'
   */
  if (Hardware_Openloop_FRF_setup_B.Dct1lowpass5 >
      Hardware_Openloop_FRF_setup_P.Saturation_UpperSat) {
    y = Hardware_Openloop_FRF_setup_P.Saturation_UpperSat;
  } else if (Hardware_Openloop_FRF_setup_B.Dct1lowpass5 <
             Hardware_Openloop_FRF_setup_P.Saturation_LowerSat) {
    y = Hardware_Openloop_FRF_setup_P.Saturation_LowerSat;
  } else {
    y = Hardware_Openloop_FRF_setup_B.Dct1lowpass5;
  }

  /* Saturate: '<S4>/Saturation' */
  if (y > Hardware_Openloop_FRF_setup_P.Saturation_UpperSat_d) {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[0] =
      Hardware_Openloop_FRF_setup_P.Saturation_UpperSat_d;
  } else if (y < Hardware_Openloop_FRF_setup_P.Saturation_LowerSat_e) {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[0] =
      Hardware_Openloop_FRF_setup_P.Saturation_LowerSat_e;
  } else {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[0] = y;
  }

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  if (Hardware_Openloop_FRF_setup_P.Constant2_Value >
      Hardware_Openloop_FRF_setup_P.Saturation_UpperSat) {
    y = Hardware_Openloop_FRF_setup_P.Saturation_UpperSat;
  } else if (Hardware_Openloop_FRF_setup_P.Constant2_Value <
             Hardware_Openloop_FRF_setup_P.Saturation_LowerSat) {
    y = Hardware_Openloop_FRF_setup_P.Saturation_LowerSat;
  } else {
    y = Hardware_Openloop_FRF_setup_P.Constant2_Value;
  }

  /* Saturate: '<S4>/Saturation' */
  if (y > Hardware_Openloop_FRF_setup_P.Saturation_UpperSat_d) {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[1] =
      Hardware_Openloop_FRF_setup_P.Saturation_UpperSat_d;
  } else if (y < Hardware_Openloop_FRF_setup_P.Saturation_LowerSat_e) {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[1] =
      Hardware_Openloop_FRF_setup_P.Saturation_LowerSat_e;
  } else {
    /* Saturate: '<S4>/Saturation' */
    Hardware_Openloop_FRF_setup_B.Saturation[1] = y;
  }

  /* MATLAB Function: '<S3>/SPERTE_measurement_function' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S3>/SPERTE_measurement_samples'
   *  Constant: '<S3>/SPERTE_measurement_trigger_command'
   *  RandomNumber: '<Root>/Noise'
   *  Sum: '<Root>/Sum1'
   */
  Hardware_Openloop_FRF_setup_DW.sfEvent = Hardware_Openloop_FR_CALL_EVENT;
  if ((((Hardware_Openloop_FRF_setup_P.MeasurementBlock_triggertype == 1) &&
        (Hardware_Openloop_FRF_setup_P.MeasurementBlock_trigger_comman == 1)) ||
       ((Hardware_Openloop_FRF_setup_P.MeasurementBlock_triggertype == 2) &&
        (Hardware_Openloop_FRF_setup_P.MeasurementBlock_trigger_comman == 1))) &&
      (Hardware_Openloop_FRF_setup_DW.busy != 1)) {
    i = (int32_T)snprintf(NULL, 0, "measurement_%d.bin",
                          Hardware_Openloop_FRF_setup_DW.NF) + 1;
    Hardware_Openloo_emxInit_char_T(&str, 2);
    tmp = str->size[0] * str->size[1];
    str->size[0] = 1;
    str->size[1] = i;
    Hardwa_emxEnsureCapacity_char_T(str, tmp);
    snprintf(&str->data[0], (size_t)i, "measurement_%d.bin",
             Hardware_Openloop_FRF_setup_DW.NF);
    if (i - 1 < 1) {
      i = -1;
    } else {
      i -= 2;
    }

    Hardware_Openloo_emxInit_char_T(&str_0, 2);
    tmp = str_0->size[0] * str_0->size[1];
    str_0->size[0] = 1;
    str_0->size[1] = i + 1;
    Hardwa_emxEnsureCapacity_char_T(str_0, tmp);
    if (i >= 0) {
      memcpy(&str_0->data[0], &str->data[0], (uint32_T)(i + 1) * sizeof(char_T));
    }

    Hardware_Openloo_emxFree_char_T(&str);
    b_fileid = Hardware_Openloop_FRF_se_cfopen(str_0, "wb");
    Hardware_Openloo_emxFree_char_T(&str_0);
    Hardware_Openloop_FRF_setup_DW.fileID = b_fileid;
    i = Hardware_Openloop_FRF_setup_DW.NF + 1;
    if (Hardware_Openloop_FRF_setup_DW.NF + 1 > 32767) {
      i = 32767;
    }

    Hardware_Openloop_FRF_setup_DW.NF = (int16_T)i;
    Hardware_Openloop_FRF_setup_DW.busy = 1U;
    Hardware_Openloop_FRF_setup_DW.NS = 0U;
  }

  if (Hardware_Openloop_FRF_setup_DW.busy == 1) {
    if (Hardware_Openloop_FRF_setup_DW.NS <
        Hardware_Openloop_FRF_setup_P.MeasurementBlock_N_samples) {
      b_fileid = (int8_T)Hardware_Openloop_FRF_setup_DW.fileID;
      if (((int8_T)Hardware_Openloop_FRF_setup_DW.fileID < 0) ||
          (Hardware_Openloop_FRF_setup_DW.fileID != (int8_T)
           Hardware_Openloop_FRF_setup_DW.fileID)) {
        b_fileid = -1;
      }

      if (b_fileid >= 3) {
        autoflush = Hardware_Openloop_FRF_setup_DW.eml_autoflush[b_fileid - 3];
        f = Hardware_Openloop_FRF_setup_DW.eml_openfiles[b_fileid - 3];
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

      if (!(Hardware_Openloop_FRF_setup_DW.fileID != 0.0)) {
        f = NULL;
      }

      if (!(f == NULL)) {
        xout[0] = (real32_T)Hardware_Openloop_FRF_setup_DW.NextOutput;

        /* ManualSwitch: '<Root>/Select encoder' incorporates:
         *  Gain: '<Root>/Gain6'
         *  Gain: '<Root>/Gain7'
         *  Gain: '<S1>/count2rad'
         *  RandomNumber: '<Root>/Noise'
         */
        if (Hardware_Openloop_FRF_setup_P.Selectencoder_CurrentSetting == 1) {
          xout[1] = (real32_T)(Hardware_Openloop_FRF_setup_P.count2rad_Gain *
                               Hardware_Openloop_FRF_setup_B.ec_Ebox_o2[0] *
                               Hardware_Openloop_FRF_setup_P.Gain7_Gain);
        } else {
          xout[1] = (real32_T)(Hardware_Openloop_FRF_setup_P.count2rad_Gain *
                               Hardware_Openloop_FRF_setup_B.ec_Ebox_o2[1] *
                               Hardware_Openloop_FRF_setup_P.Gain6_Gain);
        }

        /* End of ManualSwitch: '<Root>/Select encoder' */
        xout[2] = (real32_T)Hardware_Openloop_FRF_setup_B.Dct1lowpass5;
        xout[3] = (real32_T)Hardware_Openloop_FRF_setup_P.Constant_Value_n;
        xout[4] = (real32_T)Hardware_Openloop_FRF_setup_P.Constant_Value_n;
        bytesOutSizet = fwrite(&xout[0], sizeof(real32_T), (size_t)5, f);
        if (((real_T)bytesOutSizet > 0.0) && autoflush) {
          fflush(f);
        }
      }

      Hardware_Openloop_FRF_setup_DW.NS++;
    } else {
      Hardware_Openloop_FRF_s_cfclose(Hardware_Openloop_FRF_setup_DW.fileID);
      Hardware_Openloop_FRF_setup_DW.busy = 0U;
      Hardware_Openloop_FRF_setup_DW.NS = 0U;
    }
  }

  /* End of MATLAB Function: '<S3>/SPERTE_measurement_function' */

  /* Update for RandomNumber: '<Root>/Noise' */
  Hardware_Openloop_FRF_setup_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
    (&Hardware_Openloop_FRF_setup_DW.RandSeed) *
    Hardware_Openloop_FRF_setup_P.Noise_StdDev +
    Hardware_Openloop_FRF_setup_P.Noise_Mean;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Hardware_Openloop_FRF_setup_M->Timing.clockTick0)) {
    ++Hardware_Openloop_FRF_setup_M->Timing.clockTickH0;
  }

  Hardware_Openloop_FRF_setup_M->Timing.t[0] =
    Hardware_Openloop_FRF_setup_M->Timing.clockTick0 *
    Hardware_Openloop_FRF_setup_M->Timing.stepSize0 +
    Hardware_Openloop_FRF_setup_M->Timing.clockTickH0 *
    Hardware_Openloop_FRF_setup_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Hardware_Openloop_FRF_setup_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Hardware_Openloop_FRF_setup_M, 0,
                sizeof(RT_MODEL_Hardware_Openloop_FRF_setup_T));
  rtsiSetSolverName(&Hardware_Openloop_FRF_setup_M->solverInfo,
                    "FixedStepDiscrete");
  Hardware_Openloop_FRF_setup_M->solverInfoPtr =
    (&Hardware_Openloop_FRF_setup_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      Hardware_Openloop_FRF_setup_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Hardware_Openloop_FRF_setup_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Hardware_Openloop_FRF_setup_M->Timing.sampleTimes =
      (&Hardware_Openloop_FRF_setup_M->Timing.sampleTimesArray[0]);
    Hardware_Openloop_FRF_setup_M->Timing.offsetTimes =
      (&Hardware_Openloop_FRF_setup_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Hardware_Openloop_FRF_setup_M->Timing.sampleTimes[0] = (0.00025);

    /* task offsets */
    Hardware_Openloop_FRF_setup_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Hardware_Openloop_FRF_setup_M,
             &Hardware_Openloop_FRF_setup_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Hardware_Openloop_FRF_setup_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Hardware_Openloop_FRF_setup_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Hardware_Openloop_FRF_setup_M, -1);
  Hardware_Openloop_FRF_setup_M->Timing.stepSize0 = 0.00025;

  /* External mode info */
  Hardware_Openloop_FRF_setup_M->Sizes.checksums[0] = (1417179012U);
  Hardware_Openloop_FRF_setup_M->Sizes.checksums[1] = (2208739487U);
  Hardware_Openloop_FRF_setup_M->Sizes.checksums[2] = (3530425936U);
  Hardware_Openloop_FRF_setup_M->Sizes.checksums[3] = (2616421866U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    Hardware_Openloop_FRF_setup_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Hardware_Openloop_FRF_setup_M->extModeInfo,
      &Hardware_Openloop_FRF_setup_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Hardware_Openloop_FRF_setup_M->extModeInfo,
                        Hardware_Openloop_FRF_setup_M->Sizes.checksums);
    rteiSetTPtr(Hardware_Openloop_FRF_setup_M->extModeInfo, rtmGetTPtr
                (Hardware_Openloop_FRF_setup_M));
  }

  Hardware_Openloop_FRF_setup_M->solverInfoPtr =
    (&Hardware_Openloop_FRF_setup_M->solverInfo);
  Hardware_Openloop_FRF_setup_M->Timing.stepSize = (0.00025);
  rtsiSetFixedStepSize(&Hardware_Openloop_FRF_setup_M->solverInfo, 0.00025);
  rtsiSetSolverMode(&Hardware_Openloop_FRF_setup_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) memset(((void *) &Hardware_Openloop_FRF_setup_B), 0,
                sizeof(B_Hardware_Openloop_FRF_setup_T));

  /* states (dwork) */
  (void) memset((void *)&Hardware_Openloop_FRF_setup_DW, 0,
                sizeof(DW_Hardware_Openloop_FRF_setup_T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo =
      &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.sfcnInfo;
    Hardware_Openloop_FRF_setup_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus
      (Hardware_Openloop_FRF_setup_M)));
    Hardware_Openloop_FRF_setup_M->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &Hardware_Openloop_FRF_setup_M->Sizes.numSampTimes);
    Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.taskTimePtrs[0] =
      (&rtmGetTPtr(Hardware_Openloop_FRF_setup_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,
                   Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Hardware_Openloop_FRF_setup_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Hardware_Openloop_FRF_setup_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (Hardware_Openloop_FRF_setup_M));
    rtssSetStepSizePtr(sfcnInfo, &Hardware_Openloop_FRF_setup_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (Hardware_Openloop_FRF_setup_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Hardware_Openloop_FRF_setup_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &Hardware_Openloop_FRF_setup_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Hardware_Openloop_FRF_setup_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo,
                         &Hardware_Openloop_FRF_setup_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Hardware_Openloop_FRF_setup_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Hardware_Openloop_FRF_setup_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Hardware_Openloop_FRF_setup_M->solverInfoPtr);
  }

  Hardware_Openloop_FRF_setup_M->Sizes.numSFcns = (7);

  /* register each child */
  {
    (void) memset((void *)
                  &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.childSFunctions
                  [0], 0,
                  7*sizeof(SimStruct));
    Hardware_Openloop_FRF_setup_M->childSfunctions =
      (&Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.childSFunctionPtrs[0]);

    {
      int_T i;
      for (i = 0; i < 7; i++) {
        Hardware_Openloop_FRF_setup_M->childSfunctions[i] =
          (&Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.childSFunctions[i]);
      }
    }

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S5>/S-Function1 (getTiming) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [0]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.SFunction1));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function1");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Fourth Order Motion System/Ethercat Supervisor/S-Function1");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.SFunction1_P1_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &Hardware_Openloop_FRF_setup_DW.SFunction1_RWORK[0]);
      ssSetIWork(rts, (int_T *) &Hardware_Openloop_FRF_setup_DW.SFunction1_IWORK);
      ssSetPWork(rts, (void **) &Hardware_Openloop_FRF_setup_DW.SFunction1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 3);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_Openloop_FRF_setup_DW.SFunction1_RWORK[0]);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Hardware_Openloop_FRF_setup_DW.SFunction1_IWORK);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 2, 1);
        ssSetDWorkDataType(rts, 2,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 2, 0);
        ssSetDWork(rts, 2, &Hardware_Openloop_FRF_setup_DW.SFunction1_PWORK);
      }

      /* registration */
      getTiming(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S5>/S-Function (ec_Supervisor) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [1]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.SFunction));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Fourth Order Motion System/Ethercat Supervisor/S-Function");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 2);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.SFunction_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.SFunction_P2_Size);
      }

      /* registration */
      ec_Supervisor(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S2>/Dctnotch2 (dnotch) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [2]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.UPtrs0;
          sfcnUPtrs[0] = &Hardware_Openloop_FRF_setup_B.Gain1;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.Dctnotch2));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dctnotch2");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Load_Controller_V2_lowpass_13_5Hz_noI/Dctnotch2");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctnotch2_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctnotch2_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctnotch2_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctnotch2_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctnotch2_P5_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &Hardware_Openloop_FRF_setup_DW.Dctnotch2_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 4);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_Openloop_FRF_setup_DW.Dctnotch2_RWORK[0]);
      }

      /* registration */
      dnotch(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
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

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S2>/Dctleadlag3 (dleadlag) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[3];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [3]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[3]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [3]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [3]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [3]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [3]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[3]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.UPtrs0;
          sfcnUPtrs[0] = &Hardware_Openloop_FRF_setup_B.Dctnotch2;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.Dctleadlag3));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dctleadlag3");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Load_Controller_V2_lowpass_13_5Hz_noI/Dctleadlag3");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.params;
        ssSetSFcnParamsCount(rts, 3);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag3_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag3_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag3_P3_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &Hardware_Openloop_FRF_setup_DW.Dctleadlag3_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn3.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_Openloop_FRF_setup_DW.Dctleadlag3_RWORK[0]);
      }

      /* registration */
      dleadlag(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
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

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S2>/Dctleadlag4 (dleadlag) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[4];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [4]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[4]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [4]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [4]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [4]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [4]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[4]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.UPtrs0;
          sfcnUPtrs[0] = &Hardware_Openloop_FRF_setup_B.Dctleadlag3;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.Dctleadlag4));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dctleadlag4");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Load_Controller_V2_lowpass_13_5Hz_noI/Dctleadlag4");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.params;
        ssSetSFcnParamsCount(rts, 3);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag4_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag4_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dctleadlag4_P3_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &Hardware_Openloop_FRF_setup_DW.Dctleadlag4_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn4.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_Openloop_FRF_setup_DW.Dctleadlag4_RWORK[0]);
      }

      /* registration */
      dleadlag(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
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

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S2>/Dct1lowpass5 (dlowpass1) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[5];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [5]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[5]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [5]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [5]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [5]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [5]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[5]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.UPtrs0;
          sfcnUPtrs[0] = &Hardware_Openloop_FRF_setup_B.Dctleadlag4;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Hardware_Openloop_FRF_setup_B.Dct1lowpass5));
        }
      }

      /* path info */
      ssSetModelName(rts, "Dct1lowpass5");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Load_Controller_V2_lowpass_13_5Hz_noI/Dct1lowpass5");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.params;
        ssSetSFcnParamsCount(rts, 2);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dct1lowpass5_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.Dct1lowpass5_P2_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &Hardware_Openloop_FRF_setup_DW.Dct1lowpass5_RWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn5.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 1);

        /* RWORK */
        ssSetDWorkWidthAsInt(rts, 0, 2);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Hardware_Openloop_FRF_setup_DW.Dct1lowpass5_RWORK[0]);
      }

      /* registration */
      dlowpass1(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
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

    /* Level2 S-Function Block: Hardware_Openloop_FRF_setup/<S4>/ec_Ebox (ec_Ebox) */
    {
      SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[6];

      /* timing info */
      time_T *sfcnPeriod =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.sfcnPeriod;
      time_T *sfcnOffset =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.sfcnOffset;
      int_T *sfcnTsMap =
        Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.blkInfo2
                         [6]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.inputOutputPortInfo2[6]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Hardware_Openloop_FRF_setup_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods2
                           [6]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods3
                           [6]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.methods4
                           [6]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.statesInfo2
                         [6]);
        ssSetPeriodicStatesInfo(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.periodicStatesInfo[6]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 3);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        ssSetInputPortUnit(rts, 2, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);
        ssSetInputPortIsContinuousQuantity(rts, 2, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.UPtrs0;
          sfcnUPtrs[0] = Hardware_Openloop_FRF_setup_B.Saturation;
          sfcnUPtrs[1] = &Hardware_Openloop_FRF_setup_B.Saturation[1];
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 2);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.UPtrs1;
          sfcnUPtrs[0] = Hardware_Openloop_FRF_setup_B.Gain;
          sfcnUPtrs[1] = &Hardware_Openloop_FRF_setup_B.Gain[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.UPtrs2;

          {
            int_T i1;
            const real_T *u2 = Hardware_Openloop_FRF_setup_B.Constant1;
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
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 3);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.outputPortUnits
          [0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        ssSetOutputPortUnit(rts, 2, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 2, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            Hardware_Openloop_FRF_setup_B.ec_Ebox_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidthAsInt(rts, 1, 2);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            Hardware_Openloop_FRF_setup_B.ec_Ebox_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidthAsInt(rts, 2, 8);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            Hardware_Openloop_FRF_setup_B.ec_Ebox_o3));
        }
      }

      /* path info */
      ssSetModelName(rts, "ec_Ebox");
      ssSetPath(rts,
                "Hardware_Openloop_FRF_setup/Fourth Order Motion System/Ethercat E-box/ec_Ebox");
      ssSetRTModel(rts,Hardware_Openloop_FRF_setup_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Hardware_Openloop_FRF_setup_M->NonInlinedSFcns.Sfcn6.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Hardware_Openloop_FRF_setup_P.ec_Ebox_P1_Size);
      }

      /* registration */
      ec_Ebox(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.00025);
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
  }

  /* Start for Constant: '<S1>/Constant1' */
  memcpy(&Hardware_Openloop_FRF_setup_B.Constant1[0],
         &Hardware_Openloop_FRF_setup_P.Constant1_Value[0], sizeof(real_T) << 3U);

  /* Start for S-Function (getTiming): '<S5>/S-Function1' */
  /* Level2 S-Function Block: '<S5>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for ToFile: '<S5>/To File ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Ts_meas.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                        "Error creating .mat file Ts_meas.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "Ts_meas")) {
      fclose(fp);
      rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                        "Error writing mat file header to file Ts_meas.mat");
      return;
    }

    Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Count = 0;
    Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Decimation = -1;
    Hardware_Openloop_FRF_setup_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (ec_Supervisor): '<S5>/S-Function' */
  /* Level2 S-Function Block: '<S5>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (dnotch): '<S2>/Dctnotch2' */
  /* Level2 S-Function Block: '<S2>/Dctnotch2' (dnotch) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (dleadlag): '<S2>/Dctleadlag3' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag3' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[3];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (dleadlag): '<S2>/Dctleadlag4' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag4' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[4];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (dlowpass1): '<S2>/Dct1lowpass5' */
  /* Level2 S-Function Block: '<S2>/Dct1lowpass5' (dlowpass1) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[5];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  {
    real_T tmp;
    int32_T i;
    uint32_T r;
    uint32_T t;
    uint32_T tseed;

    /* InitializeConditions for RandomNumber: '<Root>/Noise' */
    tmp = floor(Hardware_Openloop_FRF_setup_P.Noise_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = tseed >> 16U;
    t = tseed & 32768U;
    Hardware_Openloop_FRF_setup_DW.RandSeed = ((((tseed - (r << 16U)) + t) <<
      16U) + t) + r;
    if (Hardware_Openloop_FRF_setup_DW.RandSeed < 1U) {
      Hardware_Openloop_FRF_setup_DW.RandSeed = 1144108930U;
    } else if (Hardware_Openloop_FRF_setup_DW.RandSeed > 2147483646U) {
      Hardware_Openloop_FRF_setup_DW.RandSeed = 2147483646U;
    }

    Hardware_Openloop_FRF_setup_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&Hardware_Openloop_FRF_setup_DW.RandSeed) *
      Hardware_Openloop_FRF_setup_P.Noise_StdDev +
      Hardware_Openloop_FRF_setup_P.Noise_Mean;

    /* End of InitializeConditions for RandomNumber: '<Root>/Noise' */

    /* SystemInitialize for MATLAB Function: '<S3>/SPERTE_measurement_function' */
    for (i = 0; i < 20; i++) {
      Hardware_Openloop_FRF_setup_DW.eml_autoflush[i] = false;
    }

    Hardware_Openloop_FRF_setup_DW.eml_autoflush_not_empty = true;
    for (i = 0; i < 20; i++) {
      Hardware_Openloop_FRF_setup_DW.eml_openfiles[i] = NULL;
    }

    Hardware_Openloop_FRF_setup_DW.eml_openfiles_not_empty = true;
    Hardware_Openloop_FRF_setup_DW.NF = 0;
    Hardware_Openloop_FRF_setup_DW.NF_not_empty = true;
    Hardware_Openloop_FRF_setup_DW.NS = 0U;
    Hardware_Openloop_FRF_setup_DW.NS_not_empty = true;
    Hardware_Openloop_FRF_setup_DW.fileID = 0.0;
    Hardware_Openloop_FRF_setup_DW.fileID_not_empty = true;
    Hardware_Openloop_FRF_setup_DW.busy = 0U;
    Hardware_Openloop_FRF_setup_DW.busy_not_empty = true;
    Hardware_Openloop_FRF_setup_DW.sfEvent = Hardware_Openloop_FR_CALL_EVENT;

    /* End of SystemInitialize for MATLAB Function: '<S3>/SPERTE_measurement_function' */
  }
}

/* Model terminate function */
void Hardware_Openloop_FRF_setup_terminate(void)
{
  /* Terminate for S-Function (getTiming): '<S5>/S-Function1' */
  /* Level2 S-Function Block: '<S5>/S-Function1' (getTiming) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for ToFile: '<S5>/To File ' */
  {
    FILE *fp = (FILE *) Hardware_Openloop_FRF_setup_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Ts_meas.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                          "Error closing MAT-file Ts_meas.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                          "Error reopening MAT-file Ts_meas.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           Hardware_Openloop_FRF_setup_DW.ToFile_IWORK.Count, "Ts_meas")) {
        rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                          "Error writing header for Ts_meas to MAT-file Ts_meas.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Hardware_Openloop_FRF_setup_M,
                          "Error closing MAT-file Ts_meas.mat");
        return;
      }

      Hardware_Openloop_FRF_setup_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (ec_Supervisor): '<S5>/S-Function' */
  /* Level2 S-Function Block: '<S5>/S-Function' (ec_Supervisor) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dnotch): '<S2>/Dctnotch2' */
  /* Level2 S-Function Block: '<S2>/Dctnotch2' (dnotch) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[2];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dleadlag): '<S2>/Dctleadlag3' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag3' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[3];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dleadlag): '<S2>/Dctleadlag4' */
  /* Level2 S-Function Block: '<S2>/Dctleadlag4' (dleadlag) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[4];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (dlowpass1): '<S2>/Dct1lowpass5' */
  /* Level2 S-Function Block: '<S2>/Dct1lowpass5' (dlowpass1) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[5];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (ec_Ebox): '<S4>/ec_Ebox' */
  /* Level2 S-Function Block: '<S4>/ec_Ebox' (ec_Ebox) */
  {
    SimStruct *rts = Hardware_Openloop_FRF_setup_M->childSfunctions[6];
    sfcnTerminate(rts);
  }
}
