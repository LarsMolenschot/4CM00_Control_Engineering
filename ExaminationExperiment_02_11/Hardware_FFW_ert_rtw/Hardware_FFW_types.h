/*
 * Hardware_FFW_types.h
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

#ifndef Hardware_FFW_types_h_
#define Hardware_FFW_types_h_
#include "rtwtypes.h"

/* Custom Type definition for MATLAB Function: '<S3>/SPERTE_measurement_function' */
#include <stdio.h>
#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T

struct emxArray_char_T
{
  char_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /* struct_emxArray_char_T */

#ifndef typedef_emxArray_char_T_Hardware_FFW_T
#define typedef_emxArray_char_T_Hardware_FFW_T

typedef struct emxArray_char_T emxArray_char_T_Hardware_FFW_T;

#endif                              /* typedef_emxArray_char_T_Hardware_FFW_T */

/* Parameters (default storage) */
typedef struct P_Hardware_FFW_T_ P_Hardware_FFW_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Hardware_FFW_T RT_MODEL_Hardware_FFW_T;

#endif                                 /* Hardware_FFW_types_h_ */
