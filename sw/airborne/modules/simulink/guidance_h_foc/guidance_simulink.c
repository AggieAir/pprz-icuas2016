/*
 * File: guidance_simulink.c
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

/* Block states (auto storage) */
DW_guidance_simulink_T guidance_simulink_DW;

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
  /* local block i/o variables */
  real32_T rtb_Sum1[2];
  real32_T rtb_DiscreteZeroPole;
  real32_T rtb_DiscreteZeroPole_b;
  real32_T rtb_MAX_INTEGRATOR_idx;
  real32_T rtb_MAX_INTEGRATOR_idx_0;
  real32_T rtb_MAX_POS_ERR_idx;
  real32_T rtb_MAX_POS_ERR_idx_0;
  real32_T rtb_MAX_SPEED_ERR_idx;
  real32_T rtb_MAX_SPEED_ERR_idx_0;
  real32_T u;

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
  rtb_Sum1[0] = guidance_simulink_P.D_Gain * rtb_MAX_SPEED_ERR_idx *
    guidance_simulink_P.scale2_Gain * guidance_simulink_P.scale3_Gain +
    guidance_simulink_P.P_Gain * rtb_MAX_POS_ERR_idx *
    guidance_simulink_P.scale1_Gain;
  rtb_Sum1[1] = guidance_simulink_P.D_Gain * rtb_MAX_SPEED_ERR_idx_0 *
    guidance_simulink_P.scale2_Gain * guidance_simulink_P.scale3_Gain +
    guidance_simulink_P.P_Gain * rtb_MAX_POS_ERR_idx_0 *
    guidance_simulink_P.scale1_Gain;

  /* DiscreteZeroPole: '<S1>/Discrete Zero-Pole' */
  {
    {
      static const int_T colCidxRow0[9] = { 0, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *y0 = &rtb_DiscreteZeroPole;
      int_T numNonZero = 8;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    rtb_DiscreteZeroPole += guidance_simulink_P.DiscreteZeroPole_D*rtb_Sum1[0];
  }

  /* DiscreteZeroPole: '<S2>/Discrete Zero-Pole' */
  {
    {
      static const int_T colCidxRow0[9] = { 0, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C_p;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *y0 = &rtb_DiscreteZeroPole_b;
      int_T numNonZero = 8;
      *y0 = (*pC0++) * xd[*pCidx++];
      while (numNonZero--) {
        *y0 += (*pC0++) * xd[*pCidx++];
      }
    }

    rtb_DiscreteZeroPole_b += guidance_simulink_P.DiscreteZeroPole_D_b*rtb_Sum1
      [1];
  }

  /* Gain: '<Root>/I' */
  rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.I_Gain * rtb_DiscreteZeroPole;

  /* Saturate: '<Root>/MAX_INTEGRATOR' */
  if (rtb_MAX_INTEGRATOR_idx >= guidance_simulink_P.MAX_INTEGRATOR_UpperSat) {
    rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.MAX_INTEGRATOR_UpperSat;
  } else {
    if (rtb_MAX_INTEGRATOR_idx <= guidance_simulink_P.MAX_INTEGRATOR_LowerSat) {
      rtb_MAX_INTEGRATOR_idx = guidance_simulink_P.MAX_INTEGRATOR_LowerSat;
    }
  }

  /* Gain: '<Root>/I' */
  rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.I_Gain * rtb_DiscreteZeroPole_b;

  /* Saturate: '<Root>/MAX_INTEGRATOR' */
  if (rtb_MAX_INTEGRATOR_idx_0 >= guidance_simulink_P.MAX_INTEGRATOR_UpperSat) {
    rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.MAX_INTEGRATOR_UpperSat;
  } else {
    if (rtb_MAX_INTEGRATOR_idx_0 <= guidance_simulink_P.MAX_INTEGRATOR_LowerSat)
    {
      rtb_MAX_INTEGRATOR_idx_0 = guidance_simulink_P.MAX_INTEGRATOR_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/A'
   *  Gain: '<Root>/V'
   *  Gain: '<Root>/scale4'
   *  Gain: '<Root>/scale5'
   *  Inport: '<Root>/ref_accel'
   *  Inport: '<Root>/ref_speed'
   */
  u = (guidance_simulink_P.A_Gain * guidance_simulink_U.ref_accel[0] *
       guidance_simulink_P.scale5_Gain + rtb_Sum1[0]) +
    guidance_simulink_P.V_Gain * guidance_simulink_U.ref_speed[0] *
    guidance_simulink_P.scale4_Gain;

  /* Saturate: '<Root>/TRAJ_MAX_BANK' */
  if (u >= guidance_simulink_P.TRAJ_MAX_BANK_UpperSat) {
    u = guidance_simulink_P.TRAJ_MAX_BANK_UpperSat;
  } else {
    if (u <= guidance_simulink_P.TRAJ_MAX_BANK_LowerSat) {
      u = guidance_simulink_P.TRAJ_MAX_BANK_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/scale6'
   *  Saturate: '<Root>/TRAJ_MAX_BANK'
   */
  u += guidance_simulink_P.scale6_Gain * rtb_MAX_INTEGRATOR_idx;

  /* Saturate: '<Root>/TOTAL_MAX_BANK' */
  if (u >= guidance_simulink_P.TOTAL_MAX_BANK_UpperSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] =
      guidance_simulink_P.TOTAL_MAX_BANK_UpperSat;
  } else if (u <= guidance_simulink_P.TOTAL_MAX_BANK_LowerSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] =
      guidance_simulink_P.TOTAL_MAX_BANK_LowerSat;
  } else {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[0] = u;
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/A'
   *  Gain: '<Root>/V'
   *  Gain: '<Root>/scale4'
   *  Gain: '<Root>/scale5'
   *  Inport: '<Root>/ref_accel'
   *  Inport: '<Root>/ref_speed'
   */
  u = (guidance_simulink_P.A_Gain * guidance_simulink_U.ref_accel[1] *
       guidance_simulink_P.scale5_Gain + rtb_Sum1[1]) +
    guidance_simulink_P.V_Gain * guidance_simulink_U.ref_speed[1] *
    guidance_simulink_P.scale4_Gain;

  /* Saturate: '<Root>/TRAJ_MAX_BANK' */
  if (u >= guidance_simulink_P.TRAJ_MAX_BANK_UpperSat) {
    u = guidance_simulink_P.TRAJ_MAX_BANK_UpperSat;
  } else {
    if (u <= guidance_simulink_P.TRAJ_MAX_BANK_LowerSat) {
      u = guidance_simulink_P.TRAJ_MAX_BANK_LowerSat;
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/scale6'
   *  Saturate: '<Root>/TRAJ_MAX_BANK'
   */
  u += guidance_simulink_P.scale6_Gain * rtb_MAX_INTEGRATOR_idx_0;

  /* Saturate: '<Root>/TOTAL_MAX_BANK' */
  if (u >= guidance_simulink_P.TOTAL_MAX_BANK_UpperSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] =
      guidance_simulink_P.TOTAL_MAX_BANK_UpperSat;
  } else if (u <= guidance_simulink_P.TOTAL_MAX_BANK_LowerSat) {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] =
      guidance_simulink_P.TOTAL_MAX_BANK_LowerSat;
  } else {
    /* Outport: '<Root>/guidance_h_cmd_earth' */
    guidance_simulink_Y.guidance_h_cmd_earth[1] = u;
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

  /* Update for DiscreteZeroPole: '<S1>/Discrete Zero-Pole' */
  {
    real32_T xnew[11];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B[0])*rtb_Sum1[0];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B[1])*rtb_Sum1[0];
    xnew[2] = 0.0;
    xnew[3] = (guidance_simulink_P.DiscreteZeroPole_A[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0]
      + (guidance_simulink_P.DiscreteZeroPole_A[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[3]
      + (guidance_simulink_P.DiscreteZeroPole_A[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[4];
    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B[2])*rtb_Sum1[0];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A[5])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[3];

    {
      static const int_T colAidxRow5[5] = { 0, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real32_T *pA6 = &guidance_simulink_P.DiscreteZeroPole_A[6];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew5 = &xnew[5];
      int_T numNonZero = 4;
      *pxnew5 = (*pA6++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA6++) * xd[*pAidx++];
      }
    }

    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B[3])*rtb_Sum1[0];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A[11])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[5];

    {
      static const int_T colAidxRow7[7] = { 0, 3, 4, 5, 6, 7, 8 };

      const int_T *pAidx = &colAidxRow7[0];
      const real32_T *pA12 = &guidance_simulink_P.DiscreteZeroPole_A[12];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew7 = &xnew[7];
      int_T numNonZero = 6;
      *pxnew7 = (*pA12++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew7 += (*pA12++) * xd[*pAidx++];
      }
    }

    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B[4])*rtb_Sum1[0];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A[19])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[7];

    {
      static const int_T colAidxRow9[9] = { 0, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow9[0];
      const real32_T *pA20 = &guidance_simulink_P.DiscreteZeroPole_A[20];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew9 = &xnew[9];
      int_T numNonZero = 8;
      *pxnew9 = (*pA20++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew9 += (*pA20++) * xd[*pAidx++];
      }
    }

    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B[5])*rtb_Sum1[0];
    xnew[10] = (guidance_simulink_P.DiscreteZeroPole_A[29])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[9];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE[0], xnew,
                  sizeof(real32_T)*11);
  }

  /* Update for DiscreteZeroPole: '<S2>/Discrete Zero-Pole' */
  {
    real32_T xnew[11];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A_a[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B_b[0])*rtb_Sum1[1];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A_a[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B_b[1])*rtb_Sum1[1];
    xnew[2] = 0.0;
    xnew[3] = (guidance_simulink_P.DiscreteZeroPole_A_a[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[3]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[4];
    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B_b[2])*rtb_Sum1[1];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A_a[5])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[3];

    {
      static const int_T colAidxRow5[5] = { 0, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real32_T *pA6 = &guidance_simulink_P.DiscreteZeroPole_A_a[6];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew5 = &xnew[5];
      int_T numNonZero = 4;
      *pxnew5 = (*pA6++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA6++) * xd[*pAidx++];
      }
    }

    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B_b[3])*rtb_Sum1[1];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A_a[11])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[5];

    {
      static const int_T colAidxRow7[7] = { 0, 3, 4, 5, 6, 7, 8 };

      const int_T *pAidx = &colAidxRow7[0];
      const real32_T *pA12 = &guidance_simulink_P.DiscreteZeroPole_A_a[12];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew7 = &xnew[7];
      int_T numNonZero = 6;
      *pxnew7 = (*pA12++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew7 += (*pA12++) * xd[*pAidx++];
      }
    }

    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B_b[4])*rtb_Sum1[1];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A_a[19])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[7];

    {
      static const int_T colAidxRow9[9] = { 0, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow9[0];
      const real32_T *pA20 = &guidance_simulink_P.DiscreteZeroPole_A_a[20];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew9 = &xnew[9];
      int_T numNonZero = 8;
      *pxnew9 = (*pA20++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew9 += (*pA20++) * xd[*pAidx++];
      }
    }

    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B_b[5])*rtb_Sum1[1];
    xnew[10] = (guidance_simulink_P.DiscreteZeroPole_A_a[29])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[9];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0], xnew,
                  sizeof(real32_T)*11);
  }
}

/* Model initialize function */
void guidance_simulink_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(guidance_simulink_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&guidance_simulink_DW, 0,
                sizeof(DW_guidance_simulink_T));

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
