/*
 * File: guidance_simulink.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.32
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 22:48:37 2016
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
      static const int_T colCidxRow0[30] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *y0 = &rtb_DiscreteZeroPole;
      int_T numNonZero = 29;
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
      static const int_T colCidxRow0[30] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C_p;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *y0 = &rtb_DiscreteZeroPole_b;
      int_T numNonZero = 29;
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
    real32_T xnew[41];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B[0])*rtb_Sum1[0];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B[1])*rtb_Sum1[0];
    xnew[2] = (guidance_simulink_P.DiscreteZeroPole_A[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[1];
    xnew[3] = (guidance_simulink_P.DiscreteZeroPole_A[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B[2])*rtb_Sum1[0];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[3];
    xnew[5] = (guidance_simulink_P.DiscreteZeroPole_A[5])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B[3])*rtb_Sum1[0];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A[6])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[5];
    xnew[7] = (guidance_simulink_P.DiscreteZeroPole_A[7])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B[4])*rtb_Sum1[0];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A[8])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[7];
    xnew[9] = (guidance_simulink_P.DiscreteZeroPole_A[9])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B[5])*rtb_Sum1[0];
    xnew[10] = 0.0;
    xnew[11] = (guidance_simulink_P.DiscreteZeroPole_A[10])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0]
      + (guidance_simulink_P.DiscreteZeroPole_A[11])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[11];
    xnew[11] += (guidance_simulink_P.DiscreteZeroPole_B[6])*rtb_Sum1[0];
    xnew[12] = 0.0;
    xnew[13] = (guidance_simulink_P.DiscreteZeroPole_A[12])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0]
      + (guidance_simulink_P.DiscreteZeroPole_A[13])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[11]
      + (guidance_simulink_P.DiscreteZeroPole_A[14])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[13]
      + (guidance_simulink_P.DiscreteZeroPole_A[15])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[14];
    xnew[13] += (guidance_simulink_P.DiscreteZeroPole_B[7])*rtb_Sum1[0];
    xnew[14] = (guidance_simulink_P.DiscreteZeroPole_A[16])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[13];

    {
      static const int_T colAidxRow15[6] = { 0, 11, 13, 14, 15, 16 };

      const int_T *pAidx = &colAidxRow15[0];
      const real32_T *pA17 = &guidance_simulink_P.DiscreteZeroPole_A[17];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew15 = &xnew[15];
      int_T numNonZero = 5;
      *pxnew15 = (*pA17++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew15 += (*pA17++) * xd[*pAidx++];
      }
    }

    xnew[15] += (guidance_simulink_P.DiscreteZeroPole_B[8])*rtb_Sum1[0];
    xnew[16] = (guidance_simulink_P.DiscreteZeroPole_A[23])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[15];

    {
      static const int_T colAidxRow17[8] = { 0, 11, 13, 14, 15, 16, 17, 18 };

      const int_T *pAidx = &colAidxRow17[0];
      const real32_T *pA24 = &guidance_simulink_P.DiscreteZeroPole_A[24];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew17 = &xnew[17];
      int_T numNonZero = 7;
      *pxnew17 = (*pA24++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew17 += (*pA24++) * xd[*pAidx++];
      }
    }

    xnew[17] += (guidance_simulink_P.DiscreteZeroPole_B[9])*rtb_Sum1[0];
    xnew[18] = (guidance_simulink_P.DiscreteZeroPole_A[32])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[17];

    {
      static const int_T colAidxRow19[10] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20 };

      const int_T *pAidx = &colAidxRow19[0];
      const real32_T *pA33 = &guidance_simulink_P.DiscreteZeroPole_A[33];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew19 = &xnew[19];
      int_T numNonZero = 9;
      *pxnew19 = (*pA33++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew19 += (*pA33++) * xd[*pAidx++];
      }
    }

    xnew[19] += (guidance_simulink_P.DiscreteZeroPole_B[10])*rtb_Sum1[0];
    xnew[20] = (guidance_simulink_P.DiscreteZeroPole_A[43])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[19];

    {
      static const int_T colAidxRow21[12] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22 };

      const int_T *pAidx = &colAidxRow21[0];
      const real32_T *pA44 = &guidance_simulink_P.DiscreteZeroPole_A[44];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew21 = &xnew[21];
      int_T numNonZero = 11;
      *pxnew21 = (*pA44++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew21 += (*pA44++) * xd[*pAidx++];
      }
    }

    xnew[21] += (guidance_simulink_P.DiscreteZeroPole_B[11])*rtb_Sum1[0];
    xnew[22] = (guidance_simulink_P.DiscreteZeroPole_A[56])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[21];

    {
      static const int_T colAidxRow23[14] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24 };

      const int_T *pAidx = &colAidxRow23[0];
      const real32_T *pA57 = &guidance_simulink_P.DiscreteZeroPole_A[57];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew23 = &xnew[23];
      int_T numNonZero = 13;
      *pxnew23 = (*pA57++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew23 += (*pA57++) * xd[*pAidx++];
      }
    }

    xnew[23] += (guidance_simulink_P.DiscreteZeroPole_B[12])*rtb_Sum1[0];
    xnew[24] = (guidance_simulink_P.DiscreteZeroPole_A[71])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[23];

    {
      static const int_T colAidxRow25[16] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26 };

      const int_T *pAidx = &colAidxRow25[0];
      const real32_T *pA72 = &guidance_simulink_P.DiscreteZeroPole_A[72];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew25 = &xnew[25];
      int_T numNonZero = 15;
      *pxnew25 = (*pA72++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew25 += (*pA72++) * xd[*pAidx++];
      }
    }

    xnew[25] += (guidance_simulink_P.DiscreteZeroPole_B[13])*rtb_Sum1[0];
    xnew[26] = (guidance_simulink_P.DiscreteZeroPole_A[88])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[25];

    {
      static const int_T colAidxRow27[18] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28 };

      const int_T *pAidx = &colAidxRow27[0];
      const real32_T *pA89 = &guidance_simulink_P.DiscreteZeroPole_A[89];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew27 = &xnew[27];
      int_T numNonZero = 17;
      *pxnew27 = (*pA89++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew27 += (*pA89++) * xd[*pAidx++];
      }
    }

    xnew[27] += (guidance_simulink_P.DiscreteZeroPole_B[14])*rtb_Sum1[0];
    xnew[28] = (guidance_simulink_P.DiscreteZeroPole_A[107])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[27];

    {
      static const int_T colAidxRow29[20] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };

      const int_T *pAidx = &colAidxRow29[0];
      const real32_T *pA108 = &guidance_simulink_P.DiscreteZeroPole_A[108];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew29 = &xnew[29];
      int_T numNonZero = 19;
      *pxnew29 = (*pA108++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew29 += (*pA108++) * xd[*pAidx++];
      }
    }

    xnew[29] += (guidance_simulink_P.DiscreteZeroPole_B[15])*rtb_Sum1[0];
    xnew[30] = (guidance_simulink_P.DiscreteZeroPole_A[128])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[29];

    {
      static const int_T colAidxRow31[22] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

      const int_T *pAidx = &colAidxRow31[0];
      const real32_T *pA129 = &guidance_simulink_P.DiscreteZeroPole_A[129];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew31 = &xnew[31];
      int_T numNonZero = 21;
      *pxnew31 = (*pA129++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew31 += (*pA129++) * xd[*pAidx++];
      }
    }

    xnew[31] += (guidance_simulink_P.DiscreteZeroPole_B[16])*rtb_Sum1[0];
    xnew[32] = (guidance_simulink_P.DiscreteZeroPole_A[151])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[31];

    {
      static const int_T colAidxRow33[24] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow33[0];
      const real32_T *pA152 = &guidance_simulink_P.DiscreteZeroPole_A[152];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew33 = &xnew[33];
      int_T numNonZero = 23;
      *pxnew33 = (*pA152++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew33 += (*pA152++) * xd[*pAidx++];
      }
    }

    xnew[33] += (guidance_simulink_P.DiscreteZeroPole_B[17])*rtb_Sum1[0];
    xnew[34] = (guidance_simulink_P.DiscreteZeroPole_A[176])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[33];

    {
      static const int_T colAidxRow35[26] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };

      const int_T *pAidx = &colAidxRow35[0];
      const real32_T *pA177 = &guidance_simulink_P.DiscreteZeroPole_A[177];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew35 = &xnew[35];
      int_T numNonZero = 25;
      *pxnew35 = (*pA177++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew35 += (*pA177++) * xd[*pAidx++];
      }
    }

    xnew[35] += (guidance_simulink_P.DiscreteZeroPole_B[18])*rtb_Sum1[0];
    xnew[36] = (guidance_simulink_P.DiscreteZeroPole_A[203])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[35];

    {
      static const int_T colAidxRow37[28] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38 };

      const int_T *pAidx = &colAidxRow37[0];
      const real32_T *pA204 = &guidance_simulink_P.DiscreteZeroPole_A[204];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew37 = &xnew[37];
      int_T numNonZero = 27;
      *pxnew37 = (*pA204++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew37 += (*pA204++) * xd[*pAidx++];
      }
    }

    xnew[37] += (guidance_simulink_P.DiscreteZeroPole_B[19])*rtb_Sum1[0];
    xnew[38] = (guidance_simulink_P.DiscreteZeroPole_A[232])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[37];

    {
      static const int_T colAidxRow39[30] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40 };

      const int_T *pAidx = &colAidxRow39[0];
      const real32_T *pA233 = &guidance_simulink_P.DiscreteZeroPole_A[233];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew39 = &xnew[39];
      int_T numNonZero = 29;
      *pxnew39 = (*pA233++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew39 += (*pA233++) * xd[*pAidx++];
      }
    }

    xnew[39] += (guidance_simulink_P.DiscreteZeroPole_B[20])*rtb_Sum1[0];
    xnew[40] = (guidance_simulink_P.DiscreteZeroPole_A[263])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[39];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE[0], xnew,
                  sizeof(real32_T)*41);
  }

  /* Update for DiscreteZeroPole: '<S2>/Discrete Zero-Pole' */
  {
    real32_T xnew[41];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A_a[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B_b[0])*rtb_Sum1[1];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A_a[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B_b[1])*rtb_Sum1[1];
    xnew[2] = (guidance_simulink_P.DiscreteZeroPole_A_a[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[1];
    xnew[3] = (guidance_simulink_P.DiscreteZeroPole_A_a[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B_b[2])*rtb_Sum1[1];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A_a[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[3];
    xnew[5] = (guidance_simulink_P.DiscreteZeroPole_A_a[5])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B_b[3])*rtb_Sum1[1];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A_a[6])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[5];
    xnew[7] = (guidance_simulink_P.DiscreteZeroPole_A_a[7])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B_b[4])*rtb_Sum1[1];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A_a[8])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[7];
    xnew[9] = (guidance_simulink_P.DiscreteZeroPole_A_a[9])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B_b[5])*rtb_Sum1[1];
    xnew[10] = 0.0;
    xnew[11] = (guidance_simulink_P.DiscreteZeroPole_A_a[10])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[11])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[11];
    xnew[11] += (guidance_simulink_P.DiscreteZeroPole_B_b[6])*rtb_Sum1[1];
    xnew[12] = 0.0;
    xnew[13] = (guidance_simulink_P.DiscreteZeroPole_A_a[12])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[13])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[11]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[14])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[13]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[15])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[14];
    xnew[13] += (guidance_simulink_P.DiscreteZeroPole_B_b[7])*rtb_Sum1[1];
    xnew[14] = (guidance_simulink_P.DiscreteZeroPole_A_a[16])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[13];

    {
      static const int_T colAidxRow15[6] = { 0, 11, 13, 14, 15, 16 };

      const int_T *pAidx = &colAidxRow15[0];
      const real32_T *pA17 = &guidance_simulink_P.DiscreteZeroPole_A_a[17];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew15 = &xnew[15];
      int_T numNonZero = 5;
      *pxnew15 = (*pA17++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew15 += (*pA17++) * xd[*pAidx++];
      }
    }

    xnew[15] += (guidance_simulink_P.DiscreteZeroPole_B_b[8])*rtb_Sum1[1];
    xnew[16] = (guidance_simulink_P.DiscreteZeroPole_A_a[23])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[15];

    {
      static const int_T colAidxRow17[8] = { 0, 11, 13, 14, 15, 16, 17, 18 };

      const int_T *pAidx = &colAidxRow17[0];
      const real32_T *pA24 = &guidance_simulink_P.DiscreteZeroPole_A_a[24];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew17 = &xnew[17];
      int_T numNonZero = 7;
      *pxnew17 = (*pA24++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew17 += (*pA24++) * xd[*pAidx++];
      }
    }

    xnew[17] += (guidance_simulink_P.DiscreteZeroPole_B_b[9])*rtb_Sum1[1];
    xnew[18] = (guidance_simulink_P.DiscreteZeroPole_A_a[32])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[17];

    {
      static const int_T colAidxRow19[10] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20 };

      const int_T *pAidx = &colAidxRow19[0];
      const real32_T *pA33 = &guidance_simulink_P.DiscreteZeroPole_A_a[33];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew19 = &xnew[19];
      int_T numNonZero = 9;
      *pxnew19 = (*pA33++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew19 += (*pA33++) * xd[*pAidx++];
      }
    }

    xnew[19] += (guidance_simulink_P.DiscreteZeroPole_B_b[10])*rtb_Sum1[1];
    xnew[20] = (guidance_simulink_P.DiscreteZeroPole_A_a[43])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[19];

    {
      static const int_T colAidxRow21[12] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22 };

      const int_T *pAidx = &colAidxRow21[0];
      const real32_T *pA44 = &guidance_simulink_P.DiscreteZeroPole_A_a[44];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew21 = &xnew[21];
      int_T numNonZero = 11;
      *pxnew21 = (*pA44++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew21 += (*pA44++) * xd[*pAidx++];
      }
    }

    xnew[21] += (guidance_simulink_P.DiscreteZeroPole_B_b[11])*rtb_Sum1[1];
    xnew[22] = (guidance_simulink_P.DiscreteZeroPole_A_a[56])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[21];

    {
      static const int_T colAidxRow23[14] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24 };

      const int_T *pAidx = &colAidxRow23[0];
      const real32_T *pA57 = &guidance_simulink_P.DiscreteZeroPole_A_a[57];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew23 = &xnew[23];
      int_T numNonZero = 13;
      *pxnew23 = (*pA57++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew23 += (*pA57++) * xd[*pAidx++];
      }
    }

    xnew[23] += (guidance_simulink_P.DiscreteZeroPole_B_b[12])*rtb_Sum1[1];
    xnew[24] = (guidance_simulink_P.DiscreteZeroPole_A_a[71])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[23];

    {
      static const int_T colAidxRow25[16] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26 };

      const int_T *pAidx = &colAidxRow25[0];
      const real32_T *pA72 = &guidance_simulink_P.DiscreteZeroPole_A_a[72];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew25 = &xnew[25];
      int_T numNonZero = 15;
      *pxnew25 = (*pA72++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew25 += (*pA72++) * xd[*pAidx++];
      }
    }

    xnew[25] += (guidance_simulink_P.DiscreteZeroPole_B_b[13])*rtb_Sum1[1];
    xnew[26] = (guidance_simulink_P.DiscreteZeroPole_A_a[88])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[25];

    {
      static const int_T colAidxRow27[18] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28 };

      const int_T *pAidx = &colAidxRow27[0];
      const real32_T *pA89 = &guidance_simulink_P.DiscreteZeroPole_A_a[89];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew27 = &xnew[27];
      int_T numNonZero = 17;
      *pxnew27 = (*pA89++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew27 += (*pA89++) * xd[*pAidx++];
      }
    }

    xnew[27] += (guidance_simulink_P.DiscreteZeroPole_B_b[14])*rtb_Sum1[1];
    xnew[28] = (guidance_simulink_P.DiscreteZeroPole_A_a[107])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[27];

    {
      static const int_T colAidxRow29[20] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };

      const int_T *pAidx = &colAidxRow29[0];
      const real32_T *pA108 = &guidance_simulink_P.DiscreteZeroPole_A_a[108];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew29 = &xnew[29];
      int_T numNonZero = 19;
      *pxnew29 = (*pA108++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew29 += (*pA108++) * xd[*pAidx++];
      }
    }

    xnew[29] += (guidance_simulink_P.DiscreteZeroPole_B_b[15])*rtb_Sum1[1];
    xnew[30] = (guidance_simulink_P.DiscreteZeroPole_A_a[128])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[29];

    {
      static const int_T colAidxRow31[22] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

      const int_T *pAidx = &colAidxRow31[0];
      const real32_T *pA129 = &guidance_simulink_P.DiscreteZeroPole_A_a[129];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew31 = &xnew[31];
      int_T numNonZero = 21;
      *pxnew31 = (*pA129++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew31 += (*pA129++) * xd[*pAidx++];
      }
    }

    xnew[31] += (guidance_simulink_P.DiscreteZeroPole_B_b[16])*rtb_Sum1[1];
    xnew[32] = (guidance_simulink_P.DiscreteZeroPole_A_a[151])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[31];

    {
      static const int_T colAidxRow33[24] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow33[0];
      const real32_T *pA152 = &guidance_simulink_P.DiscreteZeroPole_A_a[152];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew33 = &xnew[33];
      int_T numNonZero = 23;
      *pxnew33 = (*pA152++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew33 += (*pA152++) * xd[*pAidx++];
      }
    }

    xnew[33] += (guidance_simulink_P.DiscreteZeroPole_B_b[17])*rtb_Sum1[1];
    xnew[34] = (guidance_simulink_P.DiscreteZeroPole_A_a[176])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[33];

    {
      static const int_T colAidxRow35[26] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };

      const int_T *pAidx = &colAidxRow35[0];
      const real32_T *pA177 = &guidance_simulink_P.DiscreteZeroPole_A_a[177];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew35 = &xnew[35];
      int_T numNonZero = 25;
      *pxnew35 = (*pA177++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew35 += (*pA177++) * xd[*pAidx++];
      }
    }

    xnew[35] += (guidance_simulink_P.DiscreteZeroPole_B_b[18])*rtb_Sum1[1];
    xnew[36] = (guidance_simulink_P.DiscreteZeroPole_A_a[203])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[35];

    {
      static const int_T colAidxRow37[28] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38 };

      const int_T *pAidx = &colAidxRow37[0];
      const real32_T *pA204 = &guidance_simulink_P.DiscreteZeroPole_A_a[204];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew37 = &xnew[37];
      int_T numNonZero = 27;
      *pxnew37 = (*pA204++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew37 += (*pA204++) * xd[*pAidx++];
      }
    }

    xnew[37] += (guidance_simulink_P.DiscreteZeroPole_B_b[19])*rtb_Sum1[1];
    xnew[38] = (guidance_simulink_P.DiscreteZeroPole_A_a[232])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[37];

    {
      static const int_T colAidxRow39[30] = { 0, 11, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40 };

      const int_T *pAidx = &colAidxRow39[0];
      const real32_T *pA233 = &guidance_simulink_P.DiscreteZeroPole_A_a[233];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew39 = &xnew[39];
      int_T numNonZero = 29;
      *pxnew39 = (*pA233++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew39 += (*pA233++) * xd[*pAidx++];
      }
    }

    xnew[39] += (guidance_simulink_P.DiscreteZeroPole_B_b[20])*rtb_Sum1[1];
    xnew[40] = (guidance_simulink_P.DiscreteZeroPole_A_a[263])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[39];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0], xnew,
                  sizeof(real32_T)*41);
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
