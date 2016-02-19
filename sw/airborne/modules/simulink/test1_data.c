/*
 * File: test1_data.c
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

/* Block parameters (auto storage) */
P_test1_T test1_P = {
  11.0,                                /* Expression: P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
  0.0025,                              /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  6.0,                                 /* Expression: D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
  0.0025,                              /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  100.0,                               /* Expression: N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  12.0                                 /* Expression: I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
