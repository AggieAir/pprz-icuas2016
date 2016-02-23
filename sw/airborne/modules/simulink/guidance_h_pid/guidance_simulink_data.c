/*
 * File: guidance_simulink_data.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Mon Feb 22 15:59:21 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "guidance_simulink.h"
#include "guidance_simulink_private.h"

/* Block parameters (auto storage) */
P_guidance_simulink_T guidance_simulink_P = {
  0.1F,                                /* Computed Parameter: I_Gain
                                        * Referenced by: '<Root>/I'
                                        */
  10000.0F,                            /* Computed Parameter: MAX_POS_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  -10000.0F,                           /* Computed Parameter: MAX_POS_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  1.0F,                                /* Computed Parameter: P_Gain
                                        * Referenced by: '<Root>/P'
                                        */
  10000.0F,                            /* Computed Parameter: MAX_SPEED_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  -10000.0F,                           /* Computed Parameter: MAX_SPEED_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  1.0F,                                /* Computed Parameter: D_Gain
                                        * Referenced by: '<Root>/D'
                                        */
  10000.0F,                            /* Computed Parameter: MAX_INTEGRATOR_UpperSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  -10000.0F,                           /* Computed Parameter: MAX_INTEGRATOR_LowerSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  0.0F,                                /* Computed Parameter: A_Gain
                                        * Referenced by: '<Root>/A'
                                        */
  0.0F,                                /* Computed Parameter: V_Gain
                                        * Referenced by: '<Root>/V'
                                        */
  10000.0F,                            /* Computed Parameter: TRAJ_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  -10000.0F,                           /* Computed Parameter: TRAJ_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  10000.0F,                            /* Computed Parameter: TOTAL_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
  -10000.0F,                           /* Computed Parameter: TOTAL_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */

  /*  Computed Parameter: Constant_Value
   * Referenced by: '<Root>/Constant'
   */
  { 0, 0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
