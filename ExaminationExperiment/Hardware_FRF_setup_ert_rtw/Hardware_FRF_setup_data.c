/*
 * Hardware_FRF_setup_data.c
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

/* Block parameters (default storage) */
P_Hardware_FRF_setup_T Hardware_FRF_setup_P = {
  /* Computed Parameter: SFunction_P1_Size
   * Referenced by: '<S6>/S-Function'
   */
  { 2.0, 6.0 },

  /* Variable: ref_part
   * Referenced by: '<S6>/S-Function'
   */
  { 0.0, 300.0, 1.0, 3.5, 300.0, 0.0, 300.0, 300.0, 0.56, 0.56, 10000.0, 10000.0
  },

  /* Mask Parameter: Refpower_stat
   * Referenced by: '<S5>/Start setpoint'
   */
  2.0,

  /* Mask Parameter: MeasurementBlock_N_samples
   * Referenced by: '<S3>/SPERTE_measurement_samples'
   */
  480000U,

  /* Mask Parameter: MeasurementBlock_trigger_comman
   * Referenced by: '<S3>/SPERTE_measurement_trigger_command'
   */
  0U,

  /* Mask Parameter: MeasurementBlock_triggertype
   * Referenced by: '<S3>/SPERTE_measurement_function'
   */
  2U,

  /* Expression: 1
   * Referenced by: '<Root>/Gain7'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<Root>/Gain6'
   */
  -1.0,

  /* Computed Parameter: SFunction1_P1_Size
   * Referenced by: '<S8>/S-Function1'
   */
  { 1.0, 1.0 },

  /* Expression: 1
   * Referenced by: '<S8>/S-Function1'
   */
  1.0,

  /* Computed Parameter: SFunction_P1_Size_f
   * Referenced by: '<S8>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: portid
   * Referenced by: '<S8>/S-Function'
   */
  0.0,

  /* Computed Parameter: SFunction_P2_Size
   * Referenced by: '<S8>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: ectimeout
   * Referenced by: '<S8>/S-Function'
   */
  500.0,

  /* Computed Parameter: ec_Ebox_P1_Size
   * Referenced by: '<S7>/ec_Ebox'
   */
  { 1.0, 1.0 },

  /* Expression: link_id
   * Referenced by: '<S7>/ec_Ebox'
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
   * Referenced by: '<S7>/Gain'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<Root>/Noise'
   */
  0.0,

  /* Computed Parameter: Noise_StdDev
   * Referenced by: '<Root>/Noise'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Noise'
   */
  0.0,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer2'
   */
  0.0031415926535897933,

  /* Expression: 0.007
   * Referenced by: '<Root>/Gain'
   */
  0.007,

  /* Expression: 0%0.000015
   * Referenced by: '<Root>/Gain1'
   */
  0.0,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer3'
   */
  0.0031415926535897933,

  /* Expression: 0%0.0002705
   * Referenced by: '<Root>/Gain2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Gain5'
   */
  0.0,

  /* Expression: (2*pi)/(500*4)
   * Referenced by: '<Root>/Quantizer1'
   */
  0.0031415926535897933,

  /* Expression: 0.15
   * Referenced by: '<S2>/Gain1'
   */
  0.15,

  /* Computed Parameter: Dctleadlag2_P1_Size
   * Referenced by: '<S2>/Dctleadlag2'
   */
  { 1.0, 1.0 },

  /* Expression: f_num
   * Referenced by: '<S2>/Dctleadlag2'
   */
  3.0,

  /* Computed Parameter: Dctleadlag2_P2_Size
   * Referenced by: '<S2>/Dctleadlag2'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dctleadlag2'
   */
  60.0,

  /* Computed Parameter: Dctleadlag2_P3_Size
   * Referenced by: '<S2>/Dctleadlag2'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dctleadlag2'
   */
  0.001,

  /* Computed Parameter: Dct1lowpass3_P1_Size
   * Referenced by: '<S2>/Dct1lowpass3'
   */
  { 1.0, 1.0 },

  /* Expression: f_den
   * Referenced by: '<S2>/Dct1lowpass3'
   */
  20.0,

  /* Computed Parameter: Dct1lowpass3_P2_Size
   * Referenced by: '<S2>/Dct1lowpass3'
   */
  { 1.0, 1.0 },

  /* Expression: 0.001
   * Referenced by: '<S2>/Dct1lowpass3'
   */
  0.001,

  /* Expression: 1
   * Referenced by: '<Root>/Gain4'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Constant2'
   */
  0.0,

  /* Expression: 2.5
   * Referenced by: '<S1>/Saturation'
   */
  2.5,

  /* Expression: -2.5
   * Referenced by: '<S1>/Saturation'
   */
  -2.5,

  /* Expression: 10
   * Referenced by: '<S7>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S7>/Saturation'
   */
  -10.0,

  /* Expression: 0.0001
   * Referenced by: '<Root>/Gain3'
   */
  0.0001,

  /* Expression: [0,0,0,0,0,0,0,0]
   * Referenced by: '<S1>/Constant1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: Selectencoder_CurrentSetting
   * Referenced by: '<Root>/Select encoder'
   */
  0U
};
