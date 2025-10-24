/*
 * Hardware_Performance_run_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Hardware_Performance_run".
 *
 * Model version              : 14.22
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Oct 21 12:46:58 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (32-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Hardware_Performance_run_private_h_
#define Hardware_Performance_run_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Hardware_Performance_run_types.h"
#include "Hardware_Performance_run.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_roundd_snf(real_T u);
int_T rt_WriteMat4FileHeader(FILE *fp,
  int32_T m,
  int32_T n,
  const char_T *name);
extern void getTiming(SimStruct *rts);
extern void ec_Supervisor(SimStruct *rts);
extern void ref3b(SimStruct *rts);
extern void ec_Ebox(SimStruct *rts);
extern void dnotch(SimStruct *rts);
extern void dleadlag(SimStruct *rts);
extern void dlowpass1(SimStruct *rts);

#endif                                 /* Hardware_Performance_run_private_h_ */
