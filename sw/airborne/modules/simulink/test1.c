/*
 * File: test1.c
 *
 * Code generated for Simulink model 'test1'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Fri Feb 19 11:30:47 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit Embedded Processor
 * Emulation hardware selection:
 *    Differs from embedded hardware (STMicroelectronics->ST10/Super10)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test1.h"
#include "test1_private.h"

/* Block states (auto storage) */
DW_test1_T test1_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_test1_T test1_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_test1_T test1_Y;

/* Real-time model */
RT_MODEL_test1_T test1_M_;
RT_MODEL_test1_T *const test1_M = &test1_M_;

/* Model step function */
void test1_step(void)
{
  real_T rtb_FilterCoefficient_idx;
  real_T rtb_FilterCoefficient_idx_0;

  /* Gain: '<S1>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Gain: '<S1>/Derivative Gain'
   *  Inport: '<Root>/In1'
   *  Sum: '<S1>/SumD'
   */
  rtb_FilterCoefficient_idx = (test1_P.DerivativeGain_Gain * test1_U.In1[0] -
    test1_DW.Filter_DSTATE[0]) * test1_P.FilterCoefficient_Gain;
  rtb_FilterCoefficient_idx_0 = (test1_P.DerivativeGain_Gain * test1_U.In1[1] -
    test1_DW.Filter_DSTATE[1]) * test1_P.FilterCoefficient_Gain;

  /* Outport: '<Root>/Out1' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   *  Inport: '<Root>/In1'
   *  Sum: '<S1>/Sum'
   */
  test1_Y.Out1[0] = (test1_P.ProportionalGain_Gain * test1_U.In1[0] +
                     test1_DW.Integrator_DSTATE[0]) + rtb_FilterCoefficient_idx;
  test1_Y.Out1[1] = (test1_P.ProportionalGain_Gain * test1_U.In1[1] +
                     test1_DW.Integrator_DSTATE[1]) +
    rtb_FilterCoefficient_idx_0;

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Gain: '<S1>/Integral Gain'
   *  Inport: '<Root>/In1'
   */
  test1_DW.Integrator_DSTATE[0] += test1_P.IntegralGain_Gain * test1_U.In1[0] *
    test1_P.Integrator_gainval;
  test1_DW.Integrator_DSTATE[1] += test1_P.IntegralGain_Gain * test1_U.In1[1] *
    test1_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  test1_DW.Filter_DSTATE[0] += test1_P.Filter_gainval *
    rtb_FilterCoefficient_idx;
  test1_DW.Filter_DSTATE[1] += test1_P.Filter_gainval *
    rtb_FilterCoefficient_idx_0;
}

/* Model initialize function */
void test1_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(test1_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&test1_DW, 0,
                sizeof(DW_test1_T));

  /* external inputs */
  (void) memset(test1_U.In1, 0,
                2U*sizeof(real_T));

  /* external outputs */
  (void) memset(&test1_Y.Out1[0], 0,
                2U*sizeof(real_T));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  test1_DW.Integrator_DSTATE[0] = test1_P.Integrator_IC;
  test1_DW.Integrator_DSTATE[1] = test1_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  test1_DW.Filter_DSTATE[0] = test1_P.Filter_IC;
  test1_DW.Filter_DSTATE[1] = test1_P.Filter_IC;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
