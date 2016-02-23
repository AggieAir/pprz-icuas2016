/*
 * File: guidance_simulink.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 12:52:16 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "guidance_simulink.h"
#include "guidance_simulink_private.h"

/* External inputs (root inport signals with auto storage) */
ExtU_guidance_simulink_T guidance_simulink_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_guidance_simulink_T guidance_simulink_Y;

/* Real-time model */
RT_MODEL_guidance_simulink_T guidance_simulink_M_;
RT_MODEL_guidance_simulink_T *const guidance_simulink_M = &guidance_simulink_M_;

/* Model step function */
void guidance_simulink_step(void)
{
  real32_T rtb_MAX_POS_ERR_idx;
  real32_T rtb_MAX_POS_ERR_idx_0;
  real32_T rtb_MAX_SPEED_ERR_idx;
  real32_T rtb_MAX_SPEED_ERR_idx_0;
  real32_T rtb_Sum1_idx;
  real32_T rtb_Sum1_idx_0;
  real32_T rtb_MAX_INTEGRATOR_idx;
  real32_T rtb_MAX_INTEGRATOR_idx_0;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/positionNed_i'
   *  Inport: '<Root>/ref_pos'
   */
  rtb_MAX_POS_ERR_idx = guidance_simulink_U.ref_pos[0] -
    guidance_simulink_U.positionNed_i[0];

  /* Saturate: '<Root>/MAX_POS_ERR' */
  if (rtb_MAX_POS_ERR_idx >= guidance_simulink_P.MAX_POS_ERR_UpperSat) {
    rtb_MAX_POS_ERR_idx = guidance_simulink_P.MAX_POS_ERR_UpperSat;
  } else {
    if (rtb_MAX_POS_ERR_idx <= guidance_simulink_P.MAX_POS_ERR_LowerSat) {
      rtb_MAX_POS_ERR_idx = guidance_simulink_P.MAX_POS_ERR_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/positionNed_i'
   *  Inport: '<Root>/ref_pos'
   */
  rtb_MAX_POS_ERR_idx_0 = guidance_simulink_U.ref_pos[1] -
    guidance_simulink_U.positionNed_i[1];

  /* Saturate: '<Root>/MAX_POS_ERR' */
  if (rtb_MAX_POS_ERR_idx_0 >= guidance_simulink_P.MAX_POS_ERR_UpperSat) {
    rtb_MAX_POS_ERR_idx_0 = guidance_simulink_P.MAX_POS_ERR_UpperSat;
  } else {
    if (rtb_MAX_POS_ERR_idx_0 <= guidance_simulink_P.MAX_POS_ERR_LowerSat) {
      rtb_MAX_POS_ERR_idx_0 = guidance_simulink_P.MAX_POS_ERR_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/ref_speed'
   *  Inport: '<Root>/speedNed_i'
   */
  rtb_MAX_SPEED_ERR_idx = guidance_simulink_U.ref_speed[0] -
    guidance_simulink_U.speedNed_i[0];

  /* Saturate: '<Root>/MAX_SPEED_ERR' */
  if (rtb_MAX_SPEED_ERR_idx >= guidance_simulink_P.MAX_SPEED_ERR_UpperSat) {
    rtb_MAX_SPEED_ERR_idx = guidance_simulink_P.MAX_SPEED_ERR_UpperSat;
  } else {
    if (rtb_MAX_SPEED_ERR_idx <= guidance_simulink_P.MAX_SPEED_ERR_LowerSat) {
      rtb_MAX_SPEED_ERR_idx = guidance_simulink_P.MAX_SPEED_ERR_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/ref_speed'
   *  Inport: '<Root>/speedNed_i'
   */
  rtb_MAX_SPEED_ERR_idx_0 = guidance_simulink_U.ref_speed[1] -
    guidance_simulink_U.speedNed_i[1];

  /* Saturate: '<Root>/MAX_SPEED_ERR' */
  if (rtb_MAX_SPEED_ERR_idx_0 >= guidance_simulink_P.MAX_SPEED_ERR_UpperSat) {
    rtb_MAX_SPEED_ERR_idx_0 = guidance_simulink_P.MAX_SPEED_ERR_UpperSat;
  } else {
    if (rtb_MAX_SPEED_ERR_idx_0 <= guidance_simulink_P.MAX_SPEED_ERR_LowerSat) {
      rtb_MAX_SPEED_ERR_idx_0 = guidance_simulink_P.MAX_SPEED_ERR_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<Root>/D'
   *  Gain: '<Root>/P'
   *  Gain: '<Root>/scale1'
   *  Gain: '<Root>/scale2'
   *  Gain: '<Root>/scale3'
   */
  rtb_Sum1_idx = guidance_simulink_P.D_Gain * rtb_MAX_SPEED_ERR_idx *
    guidance_simulink_P.scale2_Gain * guidance_simulink_P.scale3_Gain +
    guidance_simulink_P.P_Gain * rtb_MAX_POS_ERR_idx *
    guidance_simulink_P.scale1_Gain;
  rtb_Sum1_idx_0 = guidance_simulink_P.D_Gain * rtb_MAX_SPEED_ERR_idx_0 *
    guidance_simulink_P.scale2_Gain * guidance_simulink_P.scale3_Gain +
    guidance_simulink_P.P_Gain * rtb_MAX_POS_ERR_idx_0 *
    guidance_simulink_P.scale1_Gain;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/I'
   *  Inport: '<Root>/is_in_flight'
   */
  if (guidance_simulink_U.is_in_flight) {
    rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.I_Gain * rtb_Sum1_idx;
    rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.I_Gain * rtb_Sum1_idx_0;
  } else {
    rtb_MAX_INTEGRATOR_idx = (real32_T)guidance_simulink_P.Constant_Value[0];
    rtb_MAX_INTEGRATOR_idx_0 = (real32_T)guidance_simulink_P.Constant_Value[1];
  }

  /* End of Switch: '<Root>/Switch' */

  /* Saturate: '<Root>/MAX_INTEGRATOR' */
  if (rtb_MAX_INTEGRATOR_idx >= guidance_simulink_P.MAX_INTEGRATOR_UpperSat) {
    rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.MAX_INTEGRATOR_UpperSat;
  } else {
    if (rtb_MAX_INTEGRATOR_idx <= guidance_simulink_P.MAX_INTEGRATOR_LowerSat) {
      rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.MAX_INTEGRATOR_LowerSat;
    }
  }

  if (rtb_MAX_INTEGRATOR_idx_0 >= guidance_simulink_P.MAX_INTEGRATOR_UpperSat) {
    rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.MAX_INTEGRATOR_UpperSat;
  } else {
    if (rtb_MAX_INTEGRATOR_idx_0 <= guidance_simulink_P.MAX_INTEGRATOR_LowerSat)
    {
      rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.MAX_INTEGRATOR_LowerSat;
    }
  }

  /* End of Saturate: '<Root>/MAX_INTEGRATOR' */

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/A'
   *  Gain: '<Root>/V'
   *  Gain: '<Root>/scale4'
   *  Gain: '<Root>/scale5'
   *  Inport: '<Root>/ref_accel'
   *  Inport: '<Root>/ref_speed'
   */
  rtb_Sum1_idx = (guidance_simulink_P.A_Gain * guidance_simulink_U.ref_accel[0] *
                  guidance_simulink_P.scale5_Gain + rtb_Sum1_idx) +
    guidance_simulink_P.V_Gain * guidance_simulink_U.ref_speed[0] *
    guidance_simulink_P.scale4_Gain;

  /* Saturate: '<Root>/TRAJ_MAX_BANK' */
  if (rtb_Sum1_idx >= guidance_simulink_P.TRAJ_MAX_BANK_UpperSat) {
    rtb_Sum1_idx = guidance_simulink_P.TRAJ_MAX_BANK_UpperSat;
  } else {
    if (rtb_Sum1_idx <= guidance_simulink_P.TRAJ_MAX_BANK_LowerSat) {
      rtb_Sum1_idx = guidance_simulink_P.TRAJ_MAX_BANK_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/scale6'
   *  Saturate: '<Root>/TRAJ_MAX_BANK'
   */
  rtb_Sum1_idx += guidance_simulink_P.scale6_Gain * rtb_MAX_INTEGRATOR_idx;

  /* Saturate: '<Root>/TOTAL_MAX_BANK' */
  if (rtb_Sum1_idx >= guidance_simulink_P.TOTAL_MAX_BANK_UpperSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] =
      guidance_simulink_P.TOTAL_MAX_BANK_UpperSat;
  } else if (rtb_Sum1_idx <= guidance_simulink_P.TOTAL_MAX_BANK_LowerSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] =
      guidance_simulink_P.TOTAL_MAX_BANK_LowerSat;
  } else {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] = rtb_Sum1_idx;
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/A'
   *  Gain: '<Root>/V'
   *  Gain: '<Root>/scale4'
   *  Gain: '<Root>/scale5'
   *  Inport: '<Root>/ref_accel'
   *  Inport: '<Root>/ref_speed'
   */
  rtb_Sum1_idx = (guidance_simulink_P.A_Gain * guidance_simulink_U.ref_accel[1] *
                  guidance_simulink_P.scale5_Gain + rtb_Sum1_idx_0) +
    guidance_simulink_P.V_Gain * guidance_simulink_U.ref_speed[1] *
    guidance_simulink_P.scale4_Gain;

  /* Saturate: '<Root>/TRAJ_MAX_BANK' */
  if (rtb_Sum1_idx >= guidance_simulink_P.TRAJ_MAX_BANK_UpperSat) {
    rtb_Sum1_idx = guidance_simulink_P.TRAJ_MAX_BANK_UpperSat;
  } else {
    if (rtb_Sum1_idx <= guidance_simulink_P.TRAJ_MAX_BANK_LowerSat) {
      rtb_Sum1_idx = guidance_simulink_P.TRAJ_MAX_BANK_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/scale6'
   *  Saturate: '<Root>/TRAJ_MAX_BANK'
   */
  rtb_Sum1_idx += guidance_simulink_P.scale6_Gain * rtb_MAX_INTEGRATOR_idx_0;

  /* Saturate: '<Root>/TOTAL_MAX_BANK' */
  if (rtb_Sum1_idx >= guidance_simulink_P.TOTAL_MAX_BANK_UpperSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] =
      guidance_simulink_P.TOTAL_MAX_BANK_UpperSat;
  } else if (rtb_Sum1_idx <= guidance_simulink_P.TOTAL_MAX_BANK_LowerSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] =
      guidance_simulink_P.TOTAL_MAX_BANK_LowerSat;
  } else {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] = rtb_Sum1_idx;
  }

  /* Outport: '<Root>/guidance_h_trim_att_integrator_f' */
  guidance_simulink_Y.guidance_h_trim_att_integrator_[0] =
    rtb_MAX_INTEGRATOR_idx;
  guidance_simulink_Y.guidance_h_trim_att_integrator_[1] =
    rtb_MAX_INTEGRATOR_idx_0;

  /* Outport: '<Root>/pos_err_f' */
  guidance_simulink_Y.pos_err_f[0] = rtb_MAX_POS_ERR_idx;
  guidance_simulink_Y.pos_err_f[1] = rtb_MAX_POS_ERR_idx_0;

  /* Outport: '<Root>/speed_err_f' */
  guidance_simulink_Y.speed_err_f[0] = rtb_MAX_SPEED_ERR_idx;
  guidance_simulink_Y.speed_err_f[1] = rtb_MAX_SPEED_ERR_idx_0;
}

/* Model initialize function */
void guidance_simulink_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(guidance_simulink_M, (NULL));

  /* external inputs */
  (void) memset((void *)&guidance_simulink_U, 0,
                sizeof(ExtU_guidance_simulink_T));

  /* external outputs */
  (void) memset((void *)&guidance_simulink_Y, 0,
                sizeof(ExtY_guidance_simulink_T));
}

/* Model terminate function */
void guidance_simulink_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
