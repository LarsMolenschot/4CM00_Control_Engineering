/*
 * Hardware_Performance_run_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Hardware_Performance_run".
 *
 * Model version              : 14.19
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Oct 21 11:14:12 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (32-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Hardware_Performance_run.h"

/* Block parameters (default storage) */
P_Hardware_Performance_run_T Hardware_Performance_run_P = {
  /* Computed Parameter: SFunction_P1_Size
   * Referenced by: '<S5>/S-Function'
   */
  { 2.0, 6.0 },

  /* Variable: ref_part
   * Referenced by: '<S5>/S-Function'
   */
  { 0.0, 125.0, 0.0, 5.5, 125.0, 0.0, 23.6, 23.6, 0.20338933535356463,
    0.20338933535356463, 2282.0, 2282.0 },

  /* Mask Parameter: Refpower_stat
   * Referenced by: '<S4>/Start setpoint'
   */
  2.0,

  /* Mask Parameter: MeasurementBlock_N_samples
   * Referenced by: '<S3>/SPERTE_measurement_samples'
   */
  120000U,

  /* Mask Parameter: MeasurementBlock_trigger_comman
   * Referenced by: '<S3>/SPERTE_measurement_trigger_command'
   */
  0U,

  /* Mask Parameter: MeasurementBlock_triggertype
   * Referenced by: '<S3>/SPERTE_measurement_function'
   */
  2U,

  /* Expression: [0,0,0,0,0,0,0,0]
   * Referenced by: '<S1>/Constant1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: SFunction1_P1_Size
   * Referenced by: '<S7>/S-Function1'
   */
  { 1.0, 1.0 },

  /* Expression: 1
   * Referenced by: '<S7>/S-Function1'
   */
  1.0,

  /* Computed Parameter: SFunction_P1_Size_f
   * Referenced by: '<S7>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: portid
   * Referenced by: '<S7>/S-Function'
   */
  0.0,

  /* Computed Parameter: SFunction_P2_Size
   * Referenced by: '<S7>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: ectimeout
   * Referenced by: '<S7>/S-Function'
   */
  500.0,

  /* Computed Parameter: ec_Ebox_P1_Size
   * Referenced by: '<S6>/ec_Ebox'
   */
  { 1.0, 1.0 },

  /* Expression: link_id
   * Referenced by: '<S6>/ec_Ebox'
   */
  0.0,

  /* Expression: (2*pi)/(4*500)
   * Referenced by: '<S1>/count2rad'
   */
  0.0031415926535897933,

  /* Expression: [0,0]
   * Referenced by: '<S1>/Constant'
   */
  { 0.0, 0.0 },

  /* Expression: 1/100
   * Referenced by: '<S6>/Gain'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S1>/Constant2'
   */
  0.0,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer2'
   */
  0.0031415926535897933,

  /* Expression: 0.0052
   * Referenced by: '<Root>/Gain'
   */
  0.0052,

  /* Expression: 0.000024
   * Referenced by: '<Root>/Gain1'
   */
  2.4E-5,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer3'
   */
  0.0031415926535897933,

  /* Expression: 0.000271
   * Referenced by: '<Root>/Gain2'
   */
  0.000271,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer1'
   */
  0.0031415926535897933,

  /* Expression: -1
   * Referenced by: '<Root>/Gain6'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S2>/Gain1'
   */
  1.0,

  /* Computed Parameter: Dctnotch2_P1_Size
   * Referenced by: '<S2>/Dctnotch2'
   */
  { 1.0, 1.0 },

  /* Expression: f_num
   * Referenced by: '<S2>/Dctnotch2'
   */
  55.0,

  /* Computed Parameter: Dctnotch2_P2_Size
   * Referenced by: '<S2>/Dctnotch2'
   */
  { 1.0, 1.0 },

  /* Expression: b_num
   * Referenced by: '<S2>/Dctnotch2'
   */
  0.03,

  /* Computed Parameter: Dctnotch2_P3_Size
   * Referenced by: '<S2>/Dctnotch2'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dctnotch2'
   */
  55.0,

  /* Computed Parameter: Dctnotch2_P4_Size
   * Referenced by: '<S2>/Dctnotch2'
   */
  { 1.0, 1.0 },

  /* Expression: b_den
   * Referenced by: '<S2>/Dctnotch2'
   */
  0.3,

  /* Computed Parameter: Dctnotch2_P5_Size
   * Referenced by: '<S2>/Dctnotch2'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dctnotch2'
   */
  0.001,

  /* Computed Parameter: Dctleadlag3_P1_Size
   * Referenced by: '<S2>/Dctleadlag3'
   */
  { 1.0, 1.0 },

  /* Expression: f_num
   * Referenced by: '<S2>/Dctleadlag3'
   */
  10.0,

  /* Computed Parameter: Dctleadlag3_P2_Size
   * Referenced by: '<S2>/Dctleadlag3'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dctleadlag3'
   */
  60.0,

  /* Computed Parameter: Dctleadlag3_P3_Size
   * Referenced by: '<S2>/Dctleadlag3'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dctleadlag3'
   */
  0.001,

  /* Computed Parameter: Dctleadlag4_P1_Size
   * Referenced by: '<S2>/Dctleadlag4'
   */
  { 1.0, 1.0 },

  /* Expression: f_num
   * Referenced by: '<S2>/Dctleadlag4'
   */
  18.0,

  /* Computed Parameter: Dctleadlag4_P2_Size
   * Referenced by: '<S2>/Dctleadlag4'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dctleadlag4'
   */
  30.0,

  /* Computed Parameter: Dctleadlag4_P3_Size
   * Referenced by: '<S2>/Dctleadlag4'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dctleadlag4'
   */
  0.001,

  /* Computed Parameter: Dct1lowpass5_P1_Size
   * Referenced by: '<S2>/Dct1lowpass5'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dct1lowpass5'
   */
  200.0,

  /* Computed Parameter: Dct1lowpass5_P2_Size
   * Referenced by: '<S2>/Dct1lowpass5'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dct1lowpass5'
   */
  0.001,

  /* Expression: 2.5
   * Referenced by: '<S1>/Saturation'
   */
  2.5,

  /* Expression: -2.5
   * Referenced by: '<S1>/Saturation'
   */
  -2.5,

  /* Expression: 10
   * Referenced by: '<S6>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S6>/Saturation'
   */
  -10.0
};
