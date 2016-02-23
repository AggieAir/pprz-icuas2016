/*
 * File: guidance_simulink_data.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 12:40:50 2016
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
  20.0F,                               /* Computed Parameter: I_Gain
                                        * Referenced by: '<Root>/I'
                                        */
  4096.0F,                             /* Computed Parameter: MAX_POS_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  -4096.0F,                            /* Computed Parameter: MAX_POS_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  50.0F,                               /* Computed Parameter: P_Gain
                                        * Referenced by: '<Root>/P'
                                        */
  0.015625F,                           /* Computed Parameter: scale1_Gain
                                        * Referenced by: '<Root>/scale1'
                                        */
  8.388608E+6F,                        /* Computed Parameter: MAX_SPEED_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  -8.388608E+6F,                       /* Computed Parameter: MAX_SPEED_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  80.0F,                               /* Computed Parameter: D_Gain
                                        * Referenced by: '<Root>/D'
                                        */
  0.25F,                               /* Computed Parameter: scale2_Gain
                                        * Referenced by: '<Root>/scale2'
                                        */
  3.05175781E-5F,                      /* Computed Parameter: scale3_Gain
                                        * Referenced by: '<Root>/scale3'
                                        */
  6.1408312E+12F,                      /* Computed Parameter: MAX_INTEGRATOR_UpperSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  -6.1408312E+12F,                     /* Computed Parameter: MAX_INTEGRATOR_LowerSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  1.52587891E-5F,                      /* Computed Parameter: scale6_Gain
                                        * Referenced by: '<Root>/scale6'
                                        */
  70.0F,                               /* Computed Parameter: A_Gain
                                        * Referenced by: '<Root>/A'
                                        */
  0.00390625F,                         /* Computed Parameter: scale5_Gain
                                        * Referenced by: '<Root>/scale5'
                                        */
  0.0F,                                /* Computed Parameter: V_Gain
                                        * Referenced by: '<Root>/V'
                                        */
  7.62939453E-6F,                      /* Computed Parameter: scale4_Gain
                                        * Referenced by: '<Root>/scale4'
                                        */
  1429.77368F,                         /* Computed Parameter: TRAJ_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  -1429.77368F,                        /* Computed Parameter: TRAJ_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  3216.99097F,                         /* Computed Parameter: TOTAL_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
  -3216.99097F,                        /* Computed Parameter: TOTAL_MAX_BANK_LowerSat
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
