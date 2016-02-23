/*
 * File: guidance_simulink_data.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.27
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 15:50:01 2016
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

  /*  Computed Parameter: DiscreteZeroPole_A
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 0.998632073F, 0.00119379605F, 0.00119379605F, 0.000122637197F,
    -1.50491652E-9F, 1.50491652E-9F, 0.00119379605F, 0.00012259034F,
    -1.50491652E-9F, 0.55857259F, -0.192477882F, 0.192477882F, 0.00119379605F,
    0.00012259034F, -1.50491652E-9F, 0.29600206F, -0.181670025F, 1.75462711F,
    -0.874890924F, 0.874890924F, 0.00119379605F, 0.00012259034F, -1.50491652E-9F,
    0.29600206F, -0.181670025F, 0.182566985F, -0.182246149F, 1.97847068F,
    -0.989217281F, 0.989217281F, 0.0F, 0.0F, -7.58950782E-36F, -1.55724609F,
    0.0F, 0.0F, -1.26321836E+11F, 1.99730873F, 2.39557256E-32F, 1.87230432F,
    2.39557226E-32F },

  /*  Computed Parameter: DiscreteZeroPole_B
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /*  Computed Parameter: DiscreteZeroPole_C
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 0.00119430188F, 0.00012264229F, -1.50555424E-9F, 0.296127498F, -0.181747F,
    0.182644352F, -0.182323381F, 0.0185723491F, -0.0185736883F, -4.83298501E-14F,
    0.0F },
  1.00042379F,                         /* Computed Parameter: DiscreteZeroPole_D
                                        * Referenced by: '<S1>/Discrete Zero-Pole'
                                        */

  /*  Computed Parameter: DiscreteZeroPole_A_a
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 0.998632073F, 0.00119379605F, 0.00119379605F, 0.000122637197F,
    -1.50491652E-9F, 1.50491652E-9F, 0.00119379605F, 0.00012259034F,
    -1.50491652E-9F, 0.55857259F, -0.192477882F, 0.192477882F, 0.00119379605F,
    0.00012259034F, -1.50491652E-9F, 0.29600206F, -0.181670025F, 1.75462711F,
    -0.874890924F, 0.874890924F, 0.00119379605F, 0.00012259034F, -1.50491652E-9F,
    0.29600206F, -0.181670025F, 0.182566985F, -0.182246149F, 1.97847068F,
    -0.989217281F, 0.989217281F, -2.79694796E-5F, 0.826402903F, 0.0F, 0.0F,
    -2.79694796E-5F, 0.826402903F, 0.0F, 0.0F, -2.79694796E-5F, 0.826402903F,
    0.0F },

  /*  Computed Parameter: DiscreteZeroPole_B_b
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /*  Computed Parameter: DiscreteZeroPole_C_p
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 0.00119430188F, 0.00012264229F, -1.50555424E-9F, 0.296127498F, -0.181747F,
    0.182644352F, -0.182323381F, 0.0185723491F, -0.0185736883F, 0.0F, 0.0F },
  1.00042379F,                         /* Computed Parameter: DiscreteZeroPole_D_b
                                        * Referenced by: '<S2>/Discrete Zero-Pole'
                                        */
  20.0F,                               /* Computed Parameter: I_Gain
                                        * Referenced by: '<Root>/I'
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
  -3216.99097F                         /* Computed Parameter: TOTAL_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
