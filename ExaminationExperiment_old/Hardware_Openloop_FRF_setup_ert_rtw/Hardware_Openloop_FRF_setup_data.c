/*
 * Hardware_Openloop_FRF_setup_data.c
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

/* Block parameters (default storage) */
P_Hardware_Openloop_FRF_setup_T Hardware_Openloop_FRF_setup_P = {
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

  /* Expression: [0,0,0,0,0,0,0,0]
   * Referenced by: '<S1>/Constant1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: SFunction1_P1_Size
   * Referenced by: '<S5>/S-Function1'
   */
  { 1.0, 1.0 },

  /* Expression: 1
   * Referenced by: '<S5>/S-Function1'
   */
  1.0,

  /* Computed Parameter: SFunction_P1_Size
   * Referenced by: '<S5>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: portid
   * Referenced by: '<S5>/S-Function'
   */
  0.0,

  /* Computed Parameter: SFunction_P2_Size
   * Referenced by: '<S5>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: ectimeout
   * Referenced by: '<S5>/S-Function'
   */
  500.0,

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

  /* Computed Parameter: ec_Ebox_P1_Size
   * Referenced by: '<S4>/ec_Ebox'
   */
  { 1.0, 1.0 },

  /* Expression: link_id
   * Referenced by: '<S4>/ec_Ebox'
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
   * Referenced by: '<S4>/Gain'
   */
  0.01,

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
   * Referenced by: '<S4>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S4>/Saturation'
   */
  -10.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant'
   */
  0.0,

  /* Computed Parameter: Selectencoder_CurrentSetting
   * Referenced by: '<Root>/Select encoder'
   */
  0U
};
