/*
 * File: guidance_simulink.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.33
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Thu Jun  9 18:41:20 2016
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
      static const int_T colCidxRow0[195] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249,
        250 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *y0 = &rtb_DiscreteZeroPole;
      int_T numNonZero = 194;
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
      static const int_T colCidxRow0[195] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249,
        250 };

      const int_T *pCidx = &colCidxRow0[0];
      const real32_T *pC0 = guidance_simulink_P.DiscreteZeroPole_C_p;
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *y0 = &rtb_DiscreteZeroPole_b;
      int_T numNonZero = 194;
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
    real32_T xnew[251];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B[0])*rtb_Sum1[0];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[0]
      + (guidance_simulink_P.DiscreteZeroPole_A[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[1]
      + (guidance_simulink_P.DiscreteZeroPole_A[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[2];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B[1])*rtb_Sum1[0];
    xnew[2] = (guidance_simulink_P.DiscreteZeroPole_A[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[1];

    {
      static const int_T colAidxRow3[5] = { 0, 1, 2, 3, 4 };

      const int_T *pAidx = &colAidxRow3[0];
      const real32_T *pA5 = &guidance_simulink_P.DiscreteZeroPole_A[5];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew3 = &xnew[3];
      int_T numNonZero = 4;
      *pxnew3 = (*pA5++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA5++) * xd[*pAidx++];
      }
    }

    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B[2])*rtb_Sum1[0];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A[10])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[3];

    {
      static const int_T colAidxRow5[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real32_T *pA11 = &guidance_simulink_P.DiscreteZeroPole_A[11];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew5 = &xnew[5];
      int_T numNonZero = 6;
      *pxnew5 = (*pA11++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA11++) * xd[*pAidx++];
      }
    }

    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B[3])*rtb_Sum1[0];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A[18])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[5];

    {
      static const int_T colAidxRow7[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

      const int_T *pAidx = &colAidxRow7[0];
      const real32_T *pA19 = &guidance_simulink_P.DiscreteZeroPole_A[19];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew7 = &xnew[7];
      int_T numNonZero = 8;
      *pxnew7 = (*pA19++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew7 += (*pA19++) * xd[*pAidx++];
      }
    }

    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B[4])*rtb_Sum1[0];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A[28])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[7];

    {
      static const int_T colAidxRow9[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow9[0];
      const real32_T *pA29 = &guidance_simulink_P.DiscreteZeroPole_A[29];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew9 = &xnew[9];
      int_T numNonZero = 10;
      *pxnew9 = (*pA29++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew9 += (*pA29++) * xd[*pAidx++];
      }
    }

    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B[5])*rtb_Sum1[0];
    xnew[10] = (guidance_simulink_P.DiscreteZeroPole_A[40])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[9];

    {
      static const int_T colAidxRow11[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12 };

      const int_T *pAidx = &colAidxRow11[0];
      const real32_T *pA41 = &guidance_simulink_P.DiscreteZeroPole_A[41];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew11 = &xnew[11];
      int_T numNonZero = 12;
      *pxnew11 = (*pA41++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew11 += (*pA41++) * xd[*pAidx++];
      }
    }

    xnew[11] += (guidance_simulink_P.DiscreteZeroPole_B[6])*rtb_Sum1[0];
    xnew[12] = (guidance_simulink_P.DiscreteZeroPole_A[54])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[11];

    {
      static const int_T colAidxRow13[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14 };

      const int_T *pAidx = &colAidxRow13[0];
      const real32_T *pA55 = &guidance_simulink_P.DiscreteZeroPole_A[55];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew13 = &xnew[13];
      int_T numNonZero = 14;
      *pxnew13 = (*pA55++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew13 += (*pA55++) * xd[*pAidx++];
      }
    }

    xnew[13] += (guidance_simulink_P.DiscreteZeroPole_B[7])*rtb_Sum1[0];
    xnew[14] = (guidance_simulink_P.DiscreteZeroPole_A[70])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[13];

    {
      static const int_T colAidxRow15[17] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16 };

      const int_T *pAidx = &colAidxRow15[0];
      const real32_T *pA71 = &guidance_simulink_P.DiscreteZeroPole_A[71];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew15 = &xnew[15];
      int_T numNonZero = 16;
      *pxnew15 = (*pA71++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew15 += (*pA71++) * xd[*pAidx++];
      }
    }

    xnew[15] += (guidance_simulink_P.DiscreteZeroPole_B[8])*rtb_Sum1[0];
    xnew[16] = (guidance_simulink_P.DiscreteZeroPole_A[88])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[15];

    {
      static const int_T colAidxRow17[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18 };

      const int_T *pAidx = &colAidxRow17[0];
      const real32_T *pA89 = &guidance_simulink_P.DiscreteZeroPole_A[89];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew17 = &xnew[17];
      int_T numNonZero = 18;
      *pxnew17 = (*pA89++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew17 += (*pA89++) * xd[*pAidx++];
      }
    }

    xnew[17] += (guidance_simulink_P.DiscreteZeroPole_B[9])*rtb_Sum1[0];
    xnew[18] = (guidance_simulink_P.DiscreteZeroPole_A[108])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[17];

    {
      static const int_T colAidxRow19[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

      const int_T *pAidx = &colAidxRow19[0];
      const real32_T *pA109 = &guidance_simulink_P.DiscreteZeroPole_A[109];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew19 = &xnew[19];
      int_T numNonZero = 20;
      *pxnew19 = (*pA109++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew19 += (*pA109++) * xd[*pAidx++];
      }
    }

    xnew[19] += (guidance_simulink_P.DiscreteZeroPole_B[10])*rtb_Sum1[0];
    xnew[20] = (guidance_simulink_P.DiscreteZeroPole_A[130])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[19];

    {
      static const int_T colAidxRow21[23] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };

      const int_T *pAidx = &colAidxRow21[0];
      const real32_T *pA131 = &guidance_simulink_P.DiscreteZeroPole_A[131];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew21 = &xnew[21];
      int_T numNonZero = 22;
      *pxnew21 = (*pA131++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew21 += (*pA131++) * xd[*pAidx++];
      }
    }

    xnew[21] += (guidance_simulink_P.DiscreteZeroPole_B[11])*rtb_Sum1[0];
    xnew[22] = (guidance_simulink_P.DiscreteZeroPole_A[154])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[21];

    {
      static const int_T colAidxRow23[25] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

      const int_T *pAidx = &colAidxRow23[0];
      const real32_T *pA155 = &guidance_simulink_P.DiscreteZeroPole_A[155];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew23 = &xnew[23];
      int_T numNonZero = 24;
      *pxnew23 = (*pA155++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew23 += (*pA155++) * xd[*pAidx++];
      }
    }

    xnew[23] += (guidance_simulink_P.DiscreteZeroPole_B[12])*rtb_Sum1[0];
    xnew[24] = (guidance_simulink_P.DiscreteZeroPole_A[180])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[23];

    {
      static const int_T colAidxRow25[27] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };

      const int_T *pAidx = &colAidxRow25[0];
      const real32_T *pA181 = &guidance_simulink_P.DiscreteZeroPole_A[181];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew25 = &xnew[25];
      int_T numNonZero = 26;
      *pxnew25 = (*pA181++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew25 += (*pA181++) * xd[*pAidx++];
      }
    }

    xnew[25] += (guidance_simulink_P.DiscreteZeroPole_B[13])*rtb_Sum1[0];
    xnew[26] = (guidance_simulink_P.DiscreteZeroPole_A[208])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[25];

    {
      static const int_T colAidxRow27[29] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 };

      const int_T *pAidx = &colAidxRow27[0];
      const real32_T *pA209 = &guidance_simulink_P.DiscreteZeroPole_A[209];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew27 = &xnew[27];
      int_T numNonZero = 28;
      *pxnew27 = (*pA209++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew27 += (*pA209++) * xd[*pAidx++];
      }
    }

    xnew[27] += (guidance_simulink_P.DiscreteZeroPole_B[14])*rtb_Sum1[0];
    xnew[28] = (guidance_simulink_P.DiscreteZeroPole_A[238])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[27];

    {
      static const int_T colAidxRow29[31] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30 };

      const int_T *pAidx = &colAidxRow29[0];
      const real32_T *pA239 = &guidance_simulink_P.DiscreteZeroPole_A[239];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew29 = &xnew[29];
      int_T numNonZero = 30;
      *pxnew29 = (*pA239++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew29 += (*pA239++) * xd[*pAidx++];
      }
    }

    xnew[29] += (guidance_simulink_P.DiscreteZeroPole_B[15])*rtb_Sum1[0];
    xnew[30] = (guidance_simulink_P.DiscreteZeroPole_A[270])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[29];

    {
      static const int_T colAidxRow31[33] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32 };

      const int_T *pAidx = &colAidxRow31[0];
      const real32_T *pA271 = &guidance_simulink_P.DiscreteZeroPole_A[271];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew31 = &xnew[31];
      int_T numNonZero = 32;
      *pxnew31 = (*pA271++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew31 += (*pA271++) * xd[*pAidx++];
      }
    }

    xnew[31] += (guidance_simulink_P.DiscreteZeroPole_B[16])*rtb_Sum1[0];
    xnew[32] = (guidance_simulink_P.DiscreteZeroPole_A[304])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[31];

    {
      static const int_T colAidxRow33[35] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow33[0];
      const real32_T *pA305 = &guidance_simulink_P.DiscreteZeroPole_A[305];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew33 = &xnew[33];
      int_T numNonZero = 34;
      *pxnew33 = (*pA305++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew33 += (*pA305++) * xd[*pAidx++];
      }
    }

    xnew[33] += (guidance_simulink_P.DiscreteZeroPole_B[17])*rtb_Sum1[0];
    xnew[34] = (guidance_simulink_P.DiscreteZeroPole_A[340])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[33];

    {
      static const int_T colAidxRow35[35] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow35[0];
      const real32_T *pA341 = &guidance_simulink_P.DiscreteZeroPole_A[341];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew35 = &xnew[35];
      int_T numNonZero = 34;
      *pxnew35 = (*pA341++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew35 += (*pA341++) * xd[*pAidx++];
      }
    }

    xnew[35] += (guidance_simulink_P.DiscreteZeroPole_B[18])*rtb_Sum1[0];
    xnew[36] = 0.0;

    {
      static const int_T colAidxRow37[37] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36 };

      const int_T *pAidx = &colAidxRow37[0];
      const real32_T *pA376 = &guidance_simulink_P.DiscreteZeroPole_A[376];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew37 = &xnew[37];
      int_T numNonZero = 36;
      *pxnew37 = (*pA376++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew37 += (*pA376++) * xd[*pAidx++];
      }
    }

    xnew[37] += (guidance_simulink_P.DiscreteZeroPole_B[19])*rtb_Sum1[0];
    xnew[38] = 0.0;

    {
      static const int_T colAidxRow39[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow39[0];
      const real32_T *pA413 = &guidance_simulink_P.DiscreteZeroPole_A[413];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew39 = &xnew[39];
      int_T numNonZero = 37;
      *pxnew39 = (*pA413++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew39 += (*pA413++) * xd[*pAidx++];
      }
    }

    xnew[39] += (guidance_simulink_P.DiscreteZeroPole_B[20])*rtb_Sum1[0];
    xnew[40] = 0.0;

    {
      static const int_T colAidxRow41[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow41[0];
      const real32_T *pA451 = &guidance_simulink_P.DiscreteZeroPole_A[451];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew41 = &xnew[41];
      int_T numNonZero = 37;
      *pxnew41 = (*pA451++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew41 += (*pA451++) * xd[*pAidx++];
      }
    }

    xnew[41] += (guidance_simulink_P.DiscreteZeroPole_B[21])*rtb_Sum1[0];
    xnew[42] = 0.0;

    {
      static const int_T colAidxRow43[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow43[0];
      const real32_T *pA489 = &guidance_simulink_P.DiscreteZeroPole_A[489];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew43 = &xnew[43];
      int_T numNonZero = 37;
      *pxnew43 = (*pA489++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew43 += (*pA489++) * xd[*pAidx++];
      }
    }

    xnew[43] += (guidance_simulink_P.DiscreteZeroPole_B[22])*rtb_Sum1[0];
    xnew[44] = (guidance_simulink_P.DiscreteZeroPole_A[527])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[43];

    {
      static const int_T colAidxRow45[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow45[0];
      const real32_T *pA528 = &guidance_simulink_P.DiscreteZeroPole_A[528];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew45 = &xnew[45];
      int_T numNonZero = 37;
      *pxnew45 = (*pA528++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew45 += (*pA528++) * xd[*pAidx++];
      }
    }

    xnew[45] += (guidance_simulink_P.DiscreteZeroPole_B[23])*rtb_Sum1[0];
    xnew[46] = (guidance_simulink_P.DiscreteZeroPole_A[566])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[45];

    {
      static const int_T colAidxRow47[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow47[0];
      const real32_T *pA567 = &guidance_simulink_P.DiscreteZeroPole_A[567];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew47 = &xnew[47];
      int_T numNonZero = 37;
      *pxnew47 = (*pA567++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew47 += (*pA567++) * xd[*pAidx++];
      }
    }

    xnew[47] += (guidance_simulink_P.DiscreteZeroPole_B[24])*rtb_Sum1[0];
    xnew[48] = (guidance_simulink_P.DiscreteZeroPole_A[605])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[47];

    {
      static const int_T colAidxRow49[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow49[0];
      const real32_T *pA606 = &guidance_simulink_P.DiscreteZeroPole_A[606];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew49 = &xnew[49];
      int_T numNonZero = 37;
      *pxnew49 = (*pA606++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew49 += (*pA606++) * xd[*pAidx++];
      }
    }

    xnew[49] += (guidance_simulink_P.DiscreteZeroPole_B[25])*rtb_Sum1[0];
    xnew[50] = (guidance_simulink_P.DiscreteZeroPole_A[644])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[49];

    {
      static const int_T colAidxRow51[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow51[0];
      const real32_T *pA645 = &guidance_simulink_P.DiscreteZeroPole_A[645];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew51 = &xnew[51];
      int_T numNonZero = 37;
      *pxnew51 = (*pA645++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew51 += (*pA645++) * xd[*pAidx++];
      }
    }

    xnew[51] += (guidance_simulink_P.DiscreteZeroPole_B[26])*rtb_Sum1[0];
    xnew[52] = 0.0;

    {
      static const int_T colAidxRow53[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow53[0];
      const real32_T *pA683 = &guidance_simulink_P.DiscreteZeroPole_A[683];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew53 = &xnew[53];
      int_T numNonZero = 37;
      *pxnew53 = (*pA683++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew53 += (*pA683++) * xd[*pAidx++];
      }
    }

    xnew[53] += (guidance_simulink_P.DiscreteZeroPole_B[27])*rtb_Sum1[0];
    xnew[54] = 0.0;

    {
      static const int_T colAidxRow55[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow55[0];
      const real32_T *pA721 = &guidance_simulink_P.DiscreteZeroPole_A[721];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew55 = &xnew[55];
      int_T numNonZero = 37;
      *pxnew55 = (*pA721++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew55 += (*pA721++) * xd[*pAidx++];
      }
    }

    xnew[55] += (guidance_simulink_P.DiscreteZeroPole_B[28])*rtb_Sum1[0];
    xnew[56] = 0.0;

    {
      static const int_T colAidxRow57[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow57[0];
      const real32_T *pA759 = &guidance_simulink_P.DiscreteZeroPole_A[759];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew57 = &xnew[57];
      int_T numNonZero = 37;
      *pxnew57 = (*pA759++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew57 += (*pA759++) * xd[*pAidx++];
      }
    }

    xnew[57] += (guidance_simulink_P.DiscreteZeroPole_B[29])*rtb_Sum1[0];
    xnew[58] = 0.0;

    {
      static const int_T colAidxRow59[40] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60 };

      const int_T *pAidx = &colAidxRow59[0];
      const real32_T *pA797 = &guidance_simulink_P.DiscreteZeroPole_A[797];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew59 = &xnew[59];
      int_T numNonZero = 39;
      *pxnew59 = (*pA797++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew59 += (*pA797++) * xd[*pAidx++];
      }
    }

    xnew[59] += (guidance_simulink_P.DiscreteZeroPole_B[30])*rtb_Sum1[0];
    xnew[60] = (guidance_simulink_P.DiscreteZeroPole_A[837])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[59];

    {
      static const int_T colAidxRow61[42] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62 };

      const int_T *pAidx = &colAidxRow61[0];
      const real32_T *pA838 = &guidance_simulink_P.DiscreteZeroPole_A[838];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew61 = &xnew[61];
      int_T numNonZero = 41;
      *pxnew61 = (*pA838++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew61 += (*pA838++) * xd[*pAidx++];
      }
    }

    xnew[61] += (guidance_simulink_P.DiscreteZeroPole_B[31])*rtb_Sum1[0];
    xnew[62] = (guidance_simulink_P.DiscreteZeroPole_A[880])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[61];

    {
      static const int_T colAidxRow63[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64 };

      const int_T *pAidx = &colAidxRow63[0];
      const real32_T *pA881 = &guidance_simulink_P.DiscreteZeroPole_A[881];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew63 = &xnew[63];
      int_T numNonZero = 43;
      *pxnew63 = (*pA881++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew63 += (*pA881++) * xd[*pAidx++];
      }
    }

    xnew[63] += (guidance_simulink_P.DiscreteZeroPole_B[32])*rtb_Sum1[0];
    xnew[64] = (guidance_simulink_P.DiscreteZeroPole_A[925])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[63];

    {
      static const int_T colAidxRow65[46] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66 };

      const int_T *pAidx = &colAidxRow65[0];
      const real32_T *pA926 = &guidance_simulink_P.DiscreteZeroPole_A[926];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew65 = &xnew[65];
      int_T numNonZero = 45;
      *pxnew65 = (*pA926++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew65 += (*pA926++) * xd[*pAidx++];
      }
    }

    xnew[65] += (guidance_simulink_P.DiscreteZeroPole_B[33])*rtb_Sum1[0];
    xnew[66] = (guidance_simulink_P.DiscreteZeroPole_A[972])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[65];

    {
      static const int_T colAidxRow67[48] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68 };

      const int_T *pAidx = &colAidxRow67[0];
      const real32_T *pA973 = &guidance_simulink_P.DiscreteZeroPole_A[973];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew67 = &xnew[67];
      int_T numNonZero = 47;
      *pxnew67 = (*pA973++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew67 += (*pA973++) * xd[*pAidx++];
      }
    }

    xnew[67] += (guidance_simulink_P.DiscreteZeroPole_B[34])*rtb_Sum1[0];
    xnew[68] = (guidance_simulink_P.DiscreteZeroPole_A[1021])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[67];

    {
      static const int_T colAidxRow69[50] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70 };

      const int_T *pAidx = &colAidxRow69[0];
      const real32_T *pA1022 = &guidance_simulink_P.DiscreteZeroPole_A[1022];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew69 = &xnew[69];
      int_T numNonZero = 49;
      *pxnew69 = (*pA1022++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew69 += (*pA1022++) * xd[*pAidx++];
      }
    }

    xnew[69] += (guidance_simulink_P.DiscreteZeroPole_B[35])*rtb_Sum1[0];
    xnew[70] = (guidance_simulink_P.DiscreteZeroPole_A[1072])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[69];

    {
      static const int_T colAidxRow71[52] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72 };

      const int_T *pAidx = &colAidxRow71[0];
      const real32_T *pA1073 = &guidance_simulink_P.DiscreteZeroPole_A[1073];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew71 = &xnew[71];
      int_T numNonZero = 51;
      *pxnew71 = (*pA1073++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew71 += (*pA1073++) * xd[*pAidx++];
      }
    }

    xnew[71] += (guidance_simulink_P.DiscreteZeroPole_B[36])*rtb_Sum1[0];
    xnew[72] = (guidance_simulink_P.DiscreteZeroPole_A[1125])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[71];

    {
      static const int_T colAidxRow73[54] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74 };

      const int_T *pAidx = &colAidxRow73[0];
      const real32_T *pA1126 = &guidance_simulink_P.DiscreteZeroPole_A[1126];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew73 = &xnew[73];
      int_T numNonZero = 53;
      *pxnew73 = (*pA1126++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew73 += (*pA1126++) * xd[*pAidx++];
      }
    }

    xnew[73] += (guidance_simulink_P.DiscreteZeroPole_B[37])*rtb_Sum1[0];
    xnew[74] = (guidance_simulink_P.DiscreteZeroPole_A[1180])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[73];

    {
      static const int_T colAidxRow75[56] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76 };

      const int_T *pAidx = &colAidxRow75[0];
      const real32_T *pA1181 = &guidance_simulink_P.DiscreteZeroPole_A[1181];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew75 = &xnew[75];
      int_T numNonZero = 55;
      *pxnew75 = (*pA1181++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew75 += (*pA1181++) * xd[*pAidx++];
      }
    }

    xnew[75] += (guidance_simulink_P.DiscreteZeroPole_B[38])*rtb_Sum1[0];
    xnew[76] = (guidance_simulink_P.DiscreteZeroPole_A[1237])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[75];

    {
      static const int_T colAidxRow77[58] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 };

      const int_T *pAidx = &colAidxRow77[0];
      const real32_T *pA1238 = &guidance_simulink_P.DiscreteZeroPole_A[1238];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew77 = &xnew[77];
      int_T numNonZero = 57;
      *pxnew77 = (*pA1238++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew77 += (*pA1238++) * xd[*pAidx++];
      }
    }

    xnew[77] += (guidance_simulink_P.DiscreteZeroPole_B[39])*rtb_Sum1[0];
    xnew[78] = (guidance_simulink_P.DiscreteZeroPole_A[1296])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[77];

    {
      static const int_T colAidxRow79[60] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };

      const int_T *pAidx = &colAidxRow79[0];
      const real32_T *pA1297 = &guidance_simulink_P.DiscreteZeroPole_A[1297];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew79 = &xnew[79];
      int_T numNonZero = 59;
      *pxnew79 = (*pA1297++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew79 += (*pA1297++) * xd[*pAidx++];
      }
    }

    xnew[79] += (guidance_simulink_P.DiscreteZeroPole_B[40])*rtb_Sum1[0];
    xnew[80] = (guidance_simulink_P.DiscreteZeroPole_A[1357])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[79];

    {
      static const int_T colAidxRow81[62] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82 };

      const int_T *pAidx = &colAidxRow81[0];
      const real32_T *pA1358 = &guidance_simulink_P.DiscreteZeroPole_A[1358];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew81 = &xnew[81];
      int_T numNonZero = 61;
      *pxnew81 = (*pA1358++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew81 += (*pA1358++) * xd[*pAidx++];
      }
    }

    xnew[81] += (guidance_simulink_P.DiscreteZeroPole_B[41])*rtb_Sum1[0];
    xnew[82] = (guidance_simulink_P.DiscreteZeroPole_A[1420])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[81];

    {
      static const int_T colAidxRow83[64] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84 };

      const int_T *pAidx = &colAidxRow83[0];
      const real32_T *pA1421 = &guidance_simulink_P.DiscreteZeroPole_A[1421];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew83 = &xnew[83];
      int_T numNonZero = 63;
      *pxnew83 = (*pA1421++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew83 += (*pA1421++) * xd[*pAidx++];
      }
    }

    xnew[83] += (guidance_simulink_P.DiscreteZeroPole_B[42])*rtb_Sum1[0];
    xnew[84] = (guidance_simulink_P.DiscreteZeroPole_A[1485])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[83];

    {
      static const int_T colAidxRow85[66] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86 };

      const int_T *pAidx = &colAidxRow85[0];
      const real32_T *pA1486 = &guidance_simulink_P.DiscreteZeroPole_A[1486];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew85 = &xnew[85];
      int_T numNonZero = 65;
      *pxnew85 = (*pA1486++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew85 += (*pA1486++) * xd[*pAidx++];
      }
    }

    xnew[85] += (guidance_simulink_P.DiscreteZeroPole_B[43])*rtb_Sum1[0];
    xnew[86] = (guidance_simulink_P.DiscreteZeroPole_A[1552])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[85];

    {
      static const int_T colAidxRow87[68] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88 };

      const int_T *pAidx = &colAidxRow87[0];
      const real32_T *pA1553 = &guidance_simulink_P.DiscreteZeroPole_A[1553];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew87 = &xnew[87];
      int_T numNonZero = 67;
      *pxnew87 = (*pA1553++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew87 += (*pA1553++) * xd[*pAidx++];
      }
    }

    xnew[87] += (guidance_simulink_P.DiscreteZeroPole_B[44])*rtb_Sum1[0];
    xnew[88] = (guidance_simulink_P.DiscreteZeroPole_A[1621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[87];

    {
      static const int_T colAidxRow89[70] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90 };

      const int_T *pAidx = &colAidxRow89[0];
      const real32_T *pA1622 = &guidance_simulink_P.DiscreteZeroPole_A[1622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew89 = &xnew[89];
      int_T numNonZero = 69;
      *pxnew89 = (*pA1622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew89 += (*pA1622++) * xd[*pAidx++];
      }
    }

    xnew[89] += (guidance_simulink_P.DiscreteZeroPole_B[45])*rtb_Sum1[0];
    xnew[90] = (guidance_simulink_P.DiscreteZeroPole_A[1692])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[89];

    {
      static const int_T colAidxRow91[72] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92 };

      const int_T *pAidx = &colAidxRow91[0];
      const real32_T *pA1693 = &guidance_simulink_P.DiscreteZeroPole_A[1693];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew91 = &xnew[91];
      int_T numNonZero = 71;
      *pxnew91 = (*pA1693++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew91 += (*pA1693++) * xd[*pAidx++];
      }
    }

    xnew[91] += (guidance_simulink_P.DiscreteZeroPole_B[46])*rtb_Sum1[0];
    xnew[92] = (guidance_simulink_P.DiscreteZeroPole_A[1765])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[91];

    {
      static const int_T colAidxRow93[74] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94 };

      const int_T *pAidx = &colAidxRow93[0];
      const real32_T *pA1766 = &guidance_simulink_P.DiscreteZeroPole_A[1766];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew93 = &xnew[93];
      int_T numNonZero = 73;
      *pxnew93 = (*pA1766++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew93 += (*pA1766++) * xd[*pAidx++];
      }
    }

    xnew[93] += (guidance_simulink_P.DiscreteZeroPole_B[47])*rtb_Sum1[0];
    xnew[94] = (guidance_simulink_P.DiscreteZeroPole_A[1840])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[93];

    {
      static const int_T colAidxRow95[76] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96 };

      const int_T *pAidx = &colAidxRow95[0];
      const real32_T *pA1841 = &guidance_simulink_P.DiscreteZeroPole_A[1841];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew95 = &xnew[95];
      int_T numNonZero = 75;
      *pxnew95 = (*pA1841++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew95 += (*pA1841++) * xd[*pAidx++];
      }
    }

    xnew[95] += (guidance_simulink_P.DiscreteZeroPole_B[48])*rtb_Sum1[0];
    xnew[96] = (guidance_simulink_P.DiscreteZeroPole_A[1917])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[95];

    {
      static const int_T colAidxRow97[78] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98 };

      const int_T *pAidx = &colAidxRow97[0];
      const real32_T *pA1918 = &guidance_simulink_P.DiscreteZeroPole_A[1918];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew97 = &xnew[97];
      int_T numNonZero = 77;
      *pxnew97 = (*pA1918++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew97 += (*pA1918++) * xd[*pAidx++];
      }
    }

    xnew[97] += (guidance_simulink_P.DiscreteZeroPole_B[49])*rtb_Sum1[0];
    xnew[98] = (guidance_simulink_P.DiscreteZeroPole_A[1996])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[97];

    {
      static const int_T colAidxRow99[80] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 };

      const int_T *pAidx = &colAidxRow99[0];
      const real32_T *pA1997 = &guidance_simulink_P.DiscreteZeroPole_A[1997];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew99 = &xnew[99];
      int_T numNonZero = 79;
      *pxnew99 = (*pA1997++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew99 += (*pA1997++) * xd[*pAidx++];
      }
    }

    xnew[99] += (guidance_simulink_P.DiscreteZeroPole_B[50])*rtb_Sum1[0];
    xnew[100] = (guidance_simulink_P.DiscreteZeroPole_A[2077])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[99];

    {
      static const int_T colAidxRow101[82] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102 };

      const int_T *pAidx = &colAidxRow101[0];
      const real32_T *pA2078 = &guidance_simulink_P.DiscreteZeroPole_A[2078];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew101 = &xnew[101];
      int_T numNonZero = 81;
      *pxnew101 = (*pA2078++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew101 += (*pA2078++) * xd[*pAidx++];
      }
    }

    xnew[101] += (guidance_simulink_P.DiscreteZeroPole_B[51])*rtb_Sum1[0];
    xnew[102] = (guidance_simulink_P.DiscreteZeroPole_A[2160])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[101];

    {
      static const int_T colAidxRow103[84] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104 };

      const int_T *pAidx = &colAidxRow103[0];
      const real32_T *pA2161 = &guidance_simulink_P.DiscreteZeroPole_A[2161];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew103 = &xnew[103];
      int_T numNonZero = 83;
      *pxnew103 = (*pA2161++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew103 += (*pA2161++) * xd[*pAidx++];
      }
    }

    xnew[103] += (guidance_simulink_P.DiscreteZeroPole_B[52])*rtb_Sum1[0];
    xnew[104] = (guidance_simulink_P.DiscreteZeroPole_A[2245])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[103];

    {
      static const int_T colAidxRow105[86] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106 };

      const int_T *pAidx = &colAidxRow105[0];
      const real32_T *pA2246 = &guidance_simulink_P.DiscreteZeroPole_A[2246];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew105 = &xnew[105];
      int_T numNonZero = 85;
      *pxnew105 = (*pA2246++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew105 += (*pA2246++) * xd[*pAidx++];
      }
    }

    xnew[105] += (guidance_simulink_P.DiscreteZeroPole_B[53])*rtb_Sum1[0];
    xnew[106] = (guidance_simulink_P.DiscreteZeroPole_A[2332])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[105];

    {
      static const int_T colAidxRow107[88] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108 };

      const int_T *pAidx = &colAidxRow107[0];
      const real32_T *pA2333 = &guidance_simulink_P.DiscreteZeroPole_A[2333];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew107 = &xnew[107];
      int_T numNonZero = 87;
      *pxnew107 = (*pA2333++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew107 += (*pA2333++) * xd[*pAidx++];
      }
    }

    xnew[107] += (guidance_simulink_P.DiscreteZeroPole_B[54])*rtb_Sum1[0];
    xnew[108] = (guidance_simulink_P.DiscreteZeroPole_A[2421])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[107];

    {
      static const int_T colAidxRow109[90] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110 };

      const int_T *pAidx = &colAidxRow109[0];
      const real32_T *pA2422 = &guidance_simulink_P.DiscreteZeroPole_A[2422];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew109 = &xnew[109];
      int_T numNonZero = 89;
      *pxnew109 = (*pA2422++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew109 += (*pA2422++) * xd[*pAidx++];
      }
    }

    xnew[109] += (guidance_simulink_P.DiscreteZeroPole_B[55])*rtb_Sum1[0];
    xnew[110] = (guidance_simulink_P.DiscreteZeroPole_A[2512])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[109];

    {
      static const int_T colAidxRow111[92] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112 };

      const int_T *pAidx = &colAidxRow111[0];
      const real32_T *pA2513 = &guidance_simulink_P.DiscreteZeroPole_A[2513];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew111 = &xnew[111];
      int_T numNonZero = 91;
      *pxnew111 = (*pA2513++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew111 += (*pA2513++) * xd[*pAidx++];
      }
    }

    xnew[111] += (guidance_simulink_P.DiscreteZeroPole_B[56])*rtb_Sum1[0];
    xnew[112] = (guidance_simulink_P.DiscreteZeroPole_A[2605])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[111];

    {
      static const int_T colAidxRow113[94] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114 };

      const int_T *pAidx = &colAidxRow113[0];
      const real32_T *pA2606 = &guidance_simulink_P.DiscreteZeroPole_A[2606];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew113 = &xnew[113];
      int_T numNonZero = 93;
      *pxnew113 = (*pA2606++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew113 += (*pA2606++) * xd[*pAidx++];
      }
    }

    xnew[113] += (guidance_simulink_P.DiscreteZeroPole_B[57])*rtb_Sum1[0];
    xnew[114] = (guidance_simulink_P.DiscreteZeroPole_A[2700])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[113];

    {
      static const int_T colAidxRow115[96] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116 };

      const int_T *pAidx = &colAidxRow115[0];
      const real32_T *pA2701 = &guidance_simulink_P.DiscreteZeroPole_A[2701];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew115 = &xnew[115];
      int_T numNonZero = 95;
      *pxnew115 = (*pA2701++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew115 += (*pA2701++) * xd[*pAidx++];
      }
    }

    xnew[115] += (guidance_simulink_P.DiscreteZeroPole_B[58])*rtb_Sum1[0];
    xnew[116] = (guidance_simulink_P.DiscreteZeroPole_A[2797])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[115];

    {
      static const int_T colAidxRow117[98] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118 };

      const int_T *pAidx = &colAidxRow117[0];
      const real32_T *pA2798 = &guidance_simulink_P.DiscreteZeroPole_A[2798];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew117 = &xnew[117];
      int_T numNonZero = 97;
      *pxnew117 = (*pA2798++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew117 += (*pA2798++) * xd[*pAidx++];
      }
    }

    xnew[117] += (guidance_simulink_P.DiscreteZeroPole_B[59])*rtb_Sum1[0];
    xnew[118] = (guidance_simulink_P.DiscreteZeroPole_A[2896])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[117];

    {
      static const int_T colAidxRow119[100] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120 };

      const int_T *pAidx = &colAidxRow119[0];
      const real32_T *pA2897 = &guidance_simulink_P.DiscreteZeroPole_A[2897];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew119 = &xnew[119];
      int_T numNonZero = 99;
      *pxnew119 = (*pA2897++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew119 += (*pA2897++) * xd[*pAidx++];
      }
    }

    xnew[119] += (guidance_simulink_P.DiscreteZeroPole_B[60])*rtb_Sum1[0];
    xnew[120] = (guidance_simulink_P.DiscreteZeroPole_A[2997])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[119];

    {
      static const int_T colAidxRow121[102] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122 };

      const int_T *pAidx = &colAidxRow121[0];
      const real32_T *pA2998 = &guidance_simulink_P.DiscreteZeroPole_A[2998];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew121 = &xnew[121];
      int_T numNonZero = 101;
      *pxnew121 = (*pA2998++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew121 += (*pA2998++) * xd[*pAidx++];
      }
    }

    xnew[121] += (guidance_simulink_P.DiscreteZeroPole_B[61])*rtb_Sum1[0];
    xnew[122] = (guidance_simulink_P.DiscreteZeroPole_A[3100])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[121];

    {
      static const int_T colAidxRow123[104] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124 };

      const int_T *pAidx = &colAidxRow123[0];
      const real32_T *pA3101 = &guidance_simulink_P.DiscreteZeroPole_A[3101];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew123 = &xnew[123];
      int_T numNonZero = 103;
      *pxnew123 = (*pA3101++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew123 += (*pA3101++) * xd[*pAidx++];
      }
    }

    xnew[123] += (guidance_simulink_P.DiscreteZeroPole_B[62])*rtb_Sum1[0];
    xnew[124] = (guidance_simulink_P.DiscreteZeroPole_A[3205])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[123];

    {
      static const int_T colAidxRow125[106] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126 };

      const int_T *pAidx = &colAidxRow125[0];
      const real32_T *pA3206 = &guidance_simulink_P.DiscreteZeroPole_A[3206];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew125 = &xnew[125];
      int_T numNonZero = 105;
      *pxnew125 = (*pA3206++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew125 += (*pA3206++) * xd[*pAidx++];
      }
    }

    xnew[125] += (guidance_simulink_P.DiscreteZeroPole_B[63])*rtb_Sum1[0];
    xnew[126] = (guidance_simulink_P.DiscreteZeroPole_A[3312])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[125];

    {
      static const int_T colAidxRow127[108] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128 };

      const int_T *pAidx = &colAidxRow127[0];
      const real32_T *pA3313 = &guidance_simulink_P.DiscreteZeroPole_A[3313];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew127 = &xnew[127];
      int_T numNonZero = 107;
      *pxnew127 = (*pA3313++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew127 += (*pA3313++) * xd[*pAidx++];
      }
    }

    xnew[127] += (guidance_simulink_P.DiscreteZeroPole_B[64])*rtb_Sum1[0];
    xnew[128] = (guidance_simulink_P.DiscreteZeroPole_A[3421])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[127];

    {
      static const int_T colAidxRow129[110] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130 };

      const int_T *pAidx = &colAidxRow129[0];
      const real32_T *pA3422 = &guidance_simulink_P.DiscreteZeroPole_A[3422];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew129 = &xnew[129];
      int_T numNonZero = 109;
      *pxnew129 = (*pA3422++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew129 += (*pA3422++) * xd[*pAidx++];
      }
    }

    xnew[129] += (guidance_simulink_P.DiscreteZeroPole_B[65])*rtb_Sum1[0];
    xnew[130] = (guidance_simulink_P.DiscreteZeroPole_A[3532])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[129];

    {
      static const int_T colAidxRow131[112] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132 };

      const int_T *pAidx = &colAidxRow131[0];
      const real32_T *pA3533 = &guidance_simulink_P.DiscreteZeroPole_A[3533];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew131 = &xnew[131];
      int_T numNonZero = 111;
      *pxnew131 = (*pA3533++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew131 += (*pA3533++) * xd[*pAidx++];
      }
    }

    xnew[131] += (guidance_simulink_P.DiscreteZeroPole_B[66])*rtb_Sum1[0];
    xnew[132] = (guidance_simulink_P.DiscreteZeroPole_A[3645])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[131];

    {
      static const int_T colAidxRow133[114] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134 };

      const int_T *pAidx = &colAidxRow133[0];
      const real32_T *pA3646 = &guidance_simulink_P.DiscreteZeroPole_A[3646];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew133 = &xnew[133];
      int_T numNonZero = 113;
      *pxnew133 = (*pA3646++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew133 += (*pA3646++) * xd[*pAidx++];
      }
    }

    xnew[133] += (guidance_simulink_P.DiscreteZeroPole_B[67])*rtb_Sum1[0];
    xnew[134] = (guidance_simulink_P.DiscreteZeroPole_A[3760])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[133];

    {
      static const int_T colAidxRow135[116] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136 };

      const int_T *pAidx = &colAidxRow135[0];
      const real32_T *pA3761 = &guidance_simulink_P.DiscreteZeroPole_A[3761];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew135 = &xnew[135];
      int_T numNonZero = 115;
      *pxnew135 = (*pA3761++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew135 += (*pA3761++) * xd[*pAidx++];
      }
    }

    xnew[135] += (guidance_simulink_P.DiscreteZeroPole_B[68])*rtb_Sum1[0];
    xnew[136] = (guidance_simulink_P.DiscreteZeroPole_A[3877])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[135];

    {
      static const int_T colAidxRow137[118] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138 };

      const int_T *pAidx = &colAidxRow137[0];
      const real32_T *pA3878 = &guidance_simulink_P.DiscreteZeroPole_A[3878];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew137 = &xnew[137];
      int_T numNonZero = 117;
      *pxnew137 = (*pA3878++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew137 += (*pA3878++) * xd[*pAidx++];
      }
    }

    xnew[137] += (guidance_simulink_P.DiscreteZeroPole_B[69])*rtb_Sum1[0];
    xnew[138] = (guidance_simulink_P.DiscreteZeroPole_A[3996])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[137];

    {
      static const int_T colAidxRow139[120] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140 };

      const int_T *pAidx = &colAidxRow139[0];
      const real32_T *pA3997 = &guidance_simulink_P.DiscreteZeroPole_A[3997];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew139 = &xnew[139];
      int_T numNonZero = 119;
      *pxnew139 = (*pA3997++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew139 += (*pA3997++) * xd[*pAidx++];
      }
    }

    xnew[139] += (guidance_simulink_P.DiscreteZeroPole_B[70])*rtb_Sum1[0];
    xnew[140] = (guidance_simulink_P.DiscreteZeroPole_A[4117])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[139];

    {
      static const int_T colAidxRow141[122] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142 };

      const int_T *pAidx = &colAidxRow141[0];
      const real32_T *pA4118 = &guidance_simulink_P.DiscreteZeroPole_A[4118];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew141 = &xnew[141];
      int_T numNonZero = 121;
      *pxnew141 = (*pA4118++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew141 += (*pA4118++) * xd[*pAidx++];
      }
    }

    xnew[141] += (guidance_simulink_P.DiscreteZeroPole_B[71])*rtb_Sum1[0];
    xnew[142] = (guidance_simulink_P.DiscreteZeroPole_A[4240])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[141];

    {
      static const int_T colAidxRow143[124] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144 };

      const int_T *pAidx = &colAidxRow143[0];
      const real32_T *pA4241 = &guidance_simulink_P.DiscreteZeroPole_A[4241];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew143 = &xnew[143];
      int_T numNonZero = 123;
      *pxnew143 = (*pA4241++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew143 += (*pA4241++) * xd[*pAidx++];
      }
    }

    xnew[143] += (guidance_simulink_P.DiscreteZeroPole_B[72])*rtb_Sum1[0];
    xnew[144] = (guidance_simulink_P.DiscreteZeroPole_A[4365])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[143];

    {
      static const int_T colAidxRow145[126] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146 };

      const int_T *pAidx = &colAidxRow145[0];
      const real32_T *pA4366 = &guidance_simulink_P.DiscreteZeroPole_A[4366];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew145 = &xnew[145];
      int_T numNonZero = 125;
      *pxnew145 = (*pA4366++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew145 += (*pA4366++) * xd[*pAidx++];
      }
    }

    xnew[145] += (guidance_simulink_P.DiscreteZeroPole_B[73])*rtb_Sum1[0];
    xnew[146] = (guidance_simulink_P.DiscreteZeroPole_A[4492])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[145];

    {
      static const int_T colAidxRow147[128] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148 };

      const int_T *pAidx = &colAidxRow147[0];
      const real32_T *pA4493 = &guidance_simulink_P.DiscreteZeroPole_A[4493];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew147 = &xnew[147];
      int_T numNonZero = 127;
      *pxnew147 = (*pA4493++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew147 += (*pA4493++) * xd[*pAidx++];
      }
    }

    xnew[147] += (guidance_simulink_P.DiscreteZeroPole_B[74])*rtb_Sum1[0];
    xnew[148] = (guidance_simulink_P.DiscreteZeroPole_A[4621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[147];

    {
      static const int_T colAidxRow149[130] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150 };

      const int_T *pAidx = &colAidxRow149[0];
      const real32_T *pA4622 = &guidance_simulink_P.DiscreteZeroPole_A[4622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew149 = &xnew[149];
      int_T numNonZero = 129;
      *pxnew149 = (*pA4622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew149 += (*pA4622++) * xd[*pAidx++];
      }
    }

    xnew[149] += (guidance_simulink_P.DiscreteZeroPole_B[75])*rtb_Sum1[0];
    xnew[150] = (guidance_simulink_P.DiscreteZeroPole_A[4752])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[149];

    {
      static const int_T colAidxRow151[132] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152 };

      const int_T *pAidx = &colAidxRow151[0];
      const real32_T *pA4753 = &guidance_simulink_P.DiscreteZeroPole_A[4753];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew151 = &xnew[151];
      int_T numNonZero = 131;
      *pxnew151 = (*pA4753++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew151 += (*pA4753++) * xd[*pAidx++];
      }
    }

    xnew[151] += (guidance_simulink_P.DiscreteZeroPole_B[76])*rtb_Sum1[0];
    xnew[152] = (guidance_simulink_P.DiscreteZeroPole_A[4885])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[151];

    {
      static const int_T colAidxRow153[134] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154 };

      const int_T *pAidx = &colAidxRow153[0];
      const real32_T *pA4886 = &guidance_simulink_P.DiscreteZeroPole_A[4886];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew153 = &xnew[153];
      int_T numNonZero = 133;
      *pxnew153 = (*pA4886++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew153 += (*pA4886++) * xd[*pAidx++];
      }
    }

    xnew[153] += (guidance_simulink_P.DiscreteZeroPole_B[77])*rtb_Sum1[0];
    xnew[154] = (guidance_simulink_P.DiscreteZeroPole_A[5020])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[153];

    {
      static const int_T colAidxRow155[136] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156 };

      const int_T *pAidx = &colAidxRow155[0];
      const real32_T *pA5021 = &guidance_simulink_P.DiscreteZeroPole_A[5021];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew155 = &xnew[155];
      int_T numNonZero = 135;
      *pxnew155 = (*pA5021++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew155 += (*pA5021++) * xd[*pAidx++];
      }
    }

    xnew[155] += (guidance_simulink_P.DiscreteZeroPole_B[78])*rtb_Sum1[0];
    xnew[156] = (guidance_simulink_P.DiscreteZeroPole_A[5157])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[155];

    {
      static const int_T colAidxRow157[138] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158 };

      const int_T *pAidx = &colAidxRow157[0];
      const real32_T *pA5158 = &guidance_simulink_P.DiscreteZeroPole_A[5158];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew157 = &xnew[157];
      int_T numNonZero = 137;
      *pxnew157 = (*pA5158++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew157 += (*pA5158++) * xd[*pAidx++];
      }
    }

    xnew[157] += (guidance_simulink_P.DiscreteZeroPole_B[79])*rtb_Sum1[0];
    xnew[158] = (guidance_simulink_P.DiscreteZeroPole_A[5296])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[157];

    {
      static const int_T colAidxRow159[140] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160 };

      const int_T *pAidx = &colAidxRow159[0];
      const real32_T *pA5297 = &guidance_simulink_P.DiscreteZeroPole_A[5297];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew159 = &xnew[159];
      int_T numNonZero = 139;
      *pxnew159 = (*pA5297++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew159 += (*pA5297++) * xd[*pAidx++];
      }
    }

    xnew[159] += (guidance_simulink_P.DiscreteZeroPole_B[80])*rtb_Sum1[0];
    xnew[160] = (guidance_simulink_P.DiscreteZeroPole_A[5437])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[159];

    {
      static const int_T colAidxRow161[142] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162 };

      const int_T *pAidx = &colAidxRow161[0];
      const real32_T *pA5438 = &guidance_simulink_P.DiscreteZeroPole_A[5438];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew161 = &xnew[161];
      int_T numNonZero = 141;
      *pxnew161 = (*pA5438++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew161 += (*pA5438++) * xd[*pAidx++];
      }
    }

    xnew[161] += (guidance_simulink_P.DiscreteZeroPole_B[81])*rtb_Sum1[0];
    xnew[162] = (guidance_simulink_P.DiscreteZeroPole_A[5580])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[161];

    {
      static const int_T colAidxRow163[144] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164 };

      const int_T *pAidx = &colAidxRow163[0];
      const real32_T *pA5581 = &guidance_simulink_P.DiscreteZeroPole_A[5581];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew163 = &xnew[163];
      int_T numNonZero = 143;
      *pxnew163 = (*pA5581++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew163 += (*pA5581++) * xd[*pAidx++];
      }
    }

    xnew[163] += (guidance_simulink_P.DiscreteZeroPole_B[82])*rtb_Sum1[0];
    xnew[164] = (guidance_simulink_P.DiscreteZeroPole_A[5725])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[163];

    {
      static const int_T colAidxRow165[146] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166 };

      const int_T *pAidx = &colAidxRow165[0];
      const real32_T *pA5726 = &guidance_simulink_P.DiscreteZeroPole_A[5726];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew165 = &xnew[165];
      int_T numNonZero = 145;
      *pxnew165 = (*pA5726++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew165 += (*pA5726++) * xd[*pAidx++];
      }
    }

    xnew[165] += (guidance_simulink_P.DiscreteZeroPole_B[83])*rtb_Sum1[0];
    xnew[166] = (guidance_simulink_P.DiscreteZeroPole_A[5872])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[165];

    {
      static const int_T colAidxRow167[148] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168 };

      const int_T *pAidx = &colAidxRow167[0];
      const real32_T *pA5873 = &guidance_simulink_P.DiscreteZeroPole_A[5873];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew167 = &xnew[167];
      int_T numNonZero = 147;
      *pxnew167 = (*pA5873++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew167 += (*pA5873++) * xd[*pAidx++];
      }
    }

    xnew[167] += (guidance_simulink_P.DiscreteZeroPole_B[84])*rtb_Sum1[0];
    xnew[168] = (guidance_simulink_P.DiscreteZeroPole_A[6021])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[167];

    {
      static const int_T colAidxRow169[150] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170 };

      const int_T *pAidx = &colAidxRow169[0];
      const real32_T *pA6022 = &guidance_simulink_P.DiscreteZeroPole_A[6022];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew169 = &xnew[169];
      int_T numNonZero = 149;
      *pxnew169 = (*pA6022++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew169 += (*pA6022++) * xd[*pAidx++];
      }
    }

    xnew[169] += (guidance_simulink_P.DiscreteZeroPole_B[85])*rtb_Sum1[0];
    xnew[170] = (guidance_simulink_P.DiscreteZeroPole_A[6172])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[169];

    {
      static const int_T colAidxRow171[152] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172 };

      const int_T *pAidx = &colAidxRow171[0];
      const real32_T *pA6173 = &guidance_simulink_P.DiscreteZeroPole_A[6173];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew171 = &xnew[171];
      int_T numNonZero = 151;
      *pxnew171 = (*pA6173++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew171 += (*pA6173++) * xd[*pAidx++];
      }
    }

    xnew[171] += (guidance_simulink_P.DiscreteZeroPole_B[86])*rtb_Sum1[0];
    xnew[172] = (guidance_simulink_P.DiscreteZeroPole_A[6325])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[171];

    {
      static const int_T colAidxRow173[154] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174 };

      const int_T *pAidx = &colAidxRow173[0];
      const real32_T *pA6326 = &guidance_simulink_P.DiscreteZeroPole_A[6326];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew173 = &xnew[173];
      int_T numNonZero = 153;
      *pxnew173 = (*pA6326++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew173 += (*pA6326++) * xd[*pAidx++];
      }
    }

    xnew[173] += (guidance_simulink_P.DiscreteZeroPole_B[87])*rtb_Sum1[0];
    xnew[174] = (guidance_simulink_P.DiscreteZeroPole_A[6480])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[173];

    {
      static const int_T colAidxRow175[156] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176 };

      const int_T *pAidx = &colAidxRow175[0];
      const real32_T *pA6481 = &guidance_simulink_P.DiscreteZeroPole_A[6481];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew175 = &xnew[175];
      int_T numNonZero = 155;
      *pxnew175 = (*pA6481++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew175 += (*pA6481++) * xd[*pAidx++];
      }
    }

    xnew[175] += (guidance_simulink_P.DiscreteZeroPole_B[88])*rtb_Sum1[0];
    xnew[176] = (guidance_simulink_P.DiscreteZeroPole_A[6637])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[175];

    {
      static const int_T colAidxRow177[158] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178 };

      const int_T *pAidx = &colAidxRow177[0];
      const real32_T *pA6638 = &guidance_simulink_P.DiscreteZeroPole_A[6638];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew177 = &xnew[177];
      int_T numNonZero = 157;
      *pxnew177 = (*pA6638++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew177 += (*pA6638++) * xd[*pAidx++];
      }
    }

    xnew[177] += (guidance_simulink_P.DiscreteZeroPole_B[89])*rtb_Sum1[0];
    xnew[178] = (guidance_simulink_P.DiscreteZeroPole_A[6796])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[177];

    {
      static const int_T colAidxRow179[160] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180 };

      const int_T *pAidx = &colAidxRow179[0];
      const real32_T *pA6797 = &guidance_simulink_P.DiscreteZeroPole_A[6797];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew179 = &xnew[179];
      int_T numNonZero = 159;
      *pxnew179 = (*pA6797++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew179 += (*pA6797++) * xd[*pAidx++];
      }
    }

    xnew[179] += (guidance_simulink_P.DiscreteZeroPole_B[90])*rtb_Sum1[0];
    xnew[180] = (guidance_simulink_P.DiscreteZeroPole_A[6957])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[179];

    {
      static const int_T colAidxRow181[162] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182 };

      const int_T *pAidx = &colAidxRow181[0];
      const real32_T *pA6958 = &guidance_simulink_P.DiscreteZeroPole_A[6958];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew181 = &xnew[181];
      int_T numNonZero = 161;
      *pxnew181 = (*pA6958++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew181 += (*pA6958++) * xd[*pAidx++];
      }
    }

    xnew[181] += (guidance_simulink_P.DiscreteZeroPole_B[91])*rtb_Sum1[0];
    xnew[182] = (guidance_simulink_P.DiscreteZeroPole_A[7120])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[181];

    {
      static const int_T colAidxRow183[164] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184 };

      const int_T *pAidx = &colAidxRow183[0];
      const real32_T *pA7121 = &guidance_simulink_P.DiscreteZeroPole_A[7121];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew183 = &xnew[183];
      int_T numNonZero = 163;
      *pxnew183 = (*pA7121++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew183 += (*pA7121++) * xd[*pAidx++];
      }
    }

    xnew[183] += (guidance_simulink_P.DiscreteZeroPole_B[92])*rtb_Sum1[0];
    xnew[184] = (guidance_simulink_P.DiscreteZeroPole_A[7285])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[183];

    {
      static const int_T colAidxRow185[166] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186 };

      const int_T *pAidx = &colAidxRow185[0];
      const real32_T *pA7286 = &guidance_simulink_P.DiscreteZeroPole_A[7286];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew185 = &xnew[185];
      int_T numNonZero = 165;
      *pxnew185 = (*pA7286++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew185 += (*pA7286++) * xd[*pAidx++];
      }
    }

    xnew[185] += (guidance_simulink_P.DiscreteZeroPole_B[93])*rtb_Sum1[0];
    xnew[186] = (guidance_simulink_P.DiscreteZeroPole_A[7452])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[185];

    {
      static const int_T colAidxRow187[168] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188 };

      const int_T *pAidx = &colAidxRow187[0];
      const real32_T *pA7453 = &guidance_simulink_P.DiscreteZeroPole_A[7453];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew187 = &xnew[187];
      int_T numNonZero = 167;
      *pxnew187 = (*pA7453++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew187 += (*pA7453++) * xd[*pAidx++];
      }
    }

    xnew[187] += (guidance_simulink_P.DiscreteZeroPole_B[94])*rtb_Sum1[0];
    xnew[188] = (guidance_simulink_P.DiscreteZeroPole_A[7621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[187];

    {
      static const int_T colAidxRow189[170] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190 };

      const int_T *pAidx = &colAidxRow189[0];
      const real32_T *pA7622 = &guidance_simulink_P.DiscreteZeroPole_A[7622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew189 = &xnew[189];
      int_T numNonZero = 169;
      *pxnew189 = (*pA7622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew189 += (*pA7622++) * xd[*pAidx++];
      }
    }

    xnew[189] += (guidance_simulink_P.DiscreteZeroPole_B[95])*rtb_Sum1[0];
    xnew[190] = (guidance_simulink_P.DiscreteZeroPole_A[7792])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[189];

    {
      static const int_T colAidxRow191[172] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192 };

      const int_T *pAidx = &colAidxRow191[0];
      const real32_T *pA7793 = &guidance_simulink_P.DiscreteZeroPole_A[7793];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew191 = &xnew[191];
      int_T numNonZero = 171;
      *pxnew191 = (*pA7793++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew191 += (*pA7793++) * xd[*pAidx++];
      }
    }

    xnew[191] += (guidance_simulink_P.DiscreteZeroPole_B[96])*rtb_Sum1[0];
    xnew[192] = (guidance_simulink_P.DiscreteZeroPole_A[7965])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[191];

    {
      static const int_T colAidxRow193[174] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194 };

      const int_T *pAidx = &colAidxRow193[0];
      const real32_T *pA7966 = &guidance_simulink_P.DiscreteZeroPole_A[7966];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew193 = &xnew[193];
      int_T numNonZero = 173;
      *pxnew193 = (*pA7966++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew193 += (*pA7966++) * xd[*pAidx++];
      }
    }

    xnew[193] += (guidance_simulink_P.DiscreteZeroPole_B[97])*rtb_Sum1[0];
    xnew[194] = (guidance_simulink_P.DiscreteZeroPole_A[8140])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[193];

    {
      static const int_T colAidxRow195[176] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196 };

      const int_T *pAidx = &colAidxRow195[0];
      const real32_T *pA8141 = &guidance_simulink_P.DiscreteZeroPole_A[8141];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew195 = &xnew[195];
      int_T numNonZero = 175;
      *pxnew195 = (*pA8141++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew195 += (*pA8141++) * xd[*pAidx++];
      }
    }

    xnew[195] += (guidance_simulink_P.DiscreteZeroPole_B[98])*rtb_Sum1[0];
    xnew[196] = (guidance_simulink_P.DiscreteZeroPole_A[8317])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[195];

    {
      static const int_T colAidxRow197[178] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198 };

      const int_T *pAidx = &colAidxRow197[0];
      const real32_T *pA8318 = &guidance_simulink_P.DiscreteZeroPole_A[8318];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew197 = &xnew[197];
      int_T numNonZero = 177;
      *pxnew197 = (*pA8318++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew197 += (*pA8318++) * xd[*pAidx++];
      }
    }

    xnew[197] += (guidance_simulink_P.DiscreteZeroPole_B[99])*rtb_Sum1[0];
    xnew[198] = (guidance_simulink_P.DiscreteZeroPole_A[8496])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[197];

    {
      static const int_T colAidxRow199[180] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200 };

      const int_T *pAidx = &colAidxRow199[0];
      const real32_T *pA8497 = &guidance_simulink_P.DiscreteZeroPole_A[8497];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew199 = &xnew[199];
      int_T numNonZero = 179;
      *pxnew199 = (*pA8497++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew199 += (*pA8497++) * xd[*pAidx++];
      }
    }

    xnew[199] += (guidance_simulink_P.DiscreteZeroPole_B[100])*rtb_Sum1[0];
    xnew[200] = (guidance_simulink_P.DiscreteZeroPole_A[8677])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[199];

    {
      static const int_T colAidxRow201[182] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202 };

      const int_T *pAidx = &colAidxRow201[0];
      const real32_T *pA8678 = &guidance_simulink_P.DiscreteZeroPole_A[8678];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew201 = &xnew[201];
      int_T numNonZero = 181;
      *pxnew201 = (*pA8678++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew201 += (*pA8678++) * xd[*pAidx++];
      }
    }

    xnew[201] += (guidance_simulink_P.DiscreteZeroPole_B[101])*rtb_Sum1[0];
    xnew[202] = (guidance_simulink_P.DiscreteZeroPole_A[8860])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[201];

    {
      static const int_T colAidxRow203[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow203[0];
      const real32_T *pA8861 = &guidance_simulink_P.DiscreteZeroPole_A[8861];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew203 = &xnew[203];
      int_T numNonZero = 183;
      *pxnew203 = (*pA8861++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew203 += (*pA8861++) * xd[*pAidx++];
      }
    }

    xnew[203] += (guidance_simulink_P.DiscreteZeroPole_B[102])*rtb_Sum1[0];
    xnew[204] = (guidance_simulink_P.DiscreteZeroPole_A[9045])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[203];

    {
      static const int_T colAidxRow205[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow205[0];
      const real32_T *pA9046 = &guidance_simulink_P.DiscreteZeroPole_A[9046];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew205 = &xnew[205];
      int_T numNonZero = 183;
      *pxnew205 = (*pA9046++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew205 += (*pA9046++) * xd[*pAidx++];
      }
    }

    xnew[205] += (guidance_simulink_P.DiscreteZeroPole_B[103])*rtb_Sum1[0];
    xnew[206] = (guidance_simulink_P.DiscreteZeroPole_A[9230])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[205];

    {
      static const int_T colAidxRow207[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow207[0];
      const real32_T *pA9231 = &guidance_simulink_P.DiscreteZeroPole_A[9231];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew207 = &xnew[207];
      int_T numNonZero = 183;
      *pxnew207 = (*pA9231++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew207 += (*pA9231++) * xd[*pAidx++];
      }
    }

    xnew[207] += (guidance_simulink_P.DiscreteZeroPole_B[104])*rtb_Sum1[0];
    xnew[208] = (guidance_simulink_P.DiscreteZeroPole_A[9415])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[207];

    {
      static const int_T colAidxRow209[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow209[0];
      const real32_T *pA9416 = &guidance_simulink_P.DiscreteZeroPole_A[9416];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew209 = &xnew[209];
      int_T numNonZero = 183;
      *pxnew209 = (*pA9416++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew209 += (*pA9416++) * xd[*pAidx++];
      }
    }

    xnew[209] += (guidance_simulink_P.DiscreteZeroPole_B[105])*rtb_Sum1[0];
    xnew[210] = (guidance_simulink_P.DiscreteZeroPole_A[9600])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[209];

    {
      static const int_T colAidxRow211[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow211[0];
      const real32_T *pA9601 = &guidance_simulink_P.DiscreteZeroPole_A[9601];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew211 = &xnew[211];
      int_T numNonZero = 183;
      *pxnew211 = (*pA9601++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew211 += (*pA9601++) * xd[*pAidx++];
      }
    }

    xnew[211] += (guidance_simulink_P.DiscreteZeroPole_B[106])*rtb_Sum1[0];
    xnew[212] = (guidance_simulink_P.DiscreteZeroPole_A[9785])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[211];

    {
      static const int_T colAidxRow213[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow213[0];
      const real32_T *pA9786 = &guidance_simulink_P.DiscreteZeroPole_A[9786];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew213 = &xnew[213];
      int_T numNonZero = 183;
      *pxnew213 = (*pA9786++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew213 += (*pA9786++) * xd[*pAidx++];
      }
    }

    xnew[213] += (guidance_simulink_P.DiscreteZeroPole_B[107])*rtb_Sum1[0];
    xnew[214] = (guidance_simulink_P.DiscreteZeroPole_A[9970])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[213];

    {
      static const int_T colAidxRow215[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow215[0];
      const real32_T *pA9971 = &guidance_simulink_P.DiscreteZeroPole_A[9971];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew215 = &xnew[215];
      int_T numNonZero = 183;
      *pxnew215 = (*pA9971++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew215 += (*pA9971++) * xd[*pAidx++];
      }
    }

    xnew[215] += (guidance_simulink_P.DiscreteZeroPole_B[108])*rtb_Sum1[0];
    xnew[216] = (guidance_simulink_P.DiscreteZeroPole_A[10155])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[215];

    {
      static const int_T colAidxRow217[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow217[0];
      const real32_T *pA10156 = &guidance_simulink_P.DiscreteZeroPole_A[10156];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew217 = &xnew[217];
      int_T numNonZero = 183;
      *pxnew217 = (*pA10156++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew217 += (*pA10156++) * xd[*pAidx++];
      }
    }

    xnew[217] += (guidance_simulink_P.DiscreteZeroPole_B[109])*rtb_Sum1[0];
    xnew[218] = (guidance_simulink_P.DiscreteZeroPole_A[10340])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[217];

    {
      static const int_T colAidxRow219[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow219[0];
      const real32_T *pA10341 = &guidance_simulink_P.DiscreteZeroPole_A[10341];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew219 = &xnew[219];
      int_T numNonZero = 183;
      *pxnew219 = (*pA10341++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew219 += (*pA10341++) * xd[*pAidx++];
      }
    }

    xnew[219] += (guidance_simulink_P.DiscreteZeroPole_B[110])*rtb_Sum1[0];
    xnew[220] = (guidance_simulink_P.DiscreteZeroPole_A[10525])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[219];

    {
      static const int_T colAidxRow221[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow221[0];
      const real32_T *pA10526 = &guidance_simulink_P.DiscreteZeroPole_A[10526];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew221 = &xnew[221];
      int_T numNonZero = 183;
      *pxnew221 = (*pA10526++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew221 += (*pA10526++) * xd[*pAidx++];
      }
    }

    xnew[221] += (guidance_simulink_P.DiscreteZeroPole_B[111])*rtb_Sum1[0];
    xnew[222] = (guidance_simulink_P.DiscreteZeroPole_A[10710])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[221];

    {
      static const int_T colAidxRow223[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow223[0];
      const real32_T *pA10711 = &guidance_simulink_P.DiscreteZeroPole_A[10711];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew223 = &xnew[223];
      int_T numNonZero = 183;
      *pxnew223 = (*pA10711++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew223 += (*pA10711++) * xd[*pAidx++];
      }
    }

    xnew[223] += (guidance_simulink_P.DiscreteZeroPole_B[112])*rtb_Sum1[0];
    xnew[224] = (guidance_simulink_P.DiscreteZeroPole_A[10895])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[223];

    {
      static const int_T colAidxRow225[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow225[0];
      const real32_T *pA10896 = &guidance_simulink_P.DiscreteZeroPole_A[10896];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew225 = &xnew[225];
      int_T numNonZero = 183;
      *pxnew225 = (*pA10896++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew225 += (*pA10896++) * xd[*pAidx++];
      }
    }

    xnew[225] += (guidance_simulink_P.DiscreteZeroPole_B[113])*rtb_Sum1[0];
    xnew[226] = (guidance_simulink_P.DiscreteZeroPole_A[11080])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[225];

    {
      static const int_T colAidxRow227[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow227[0];
      const real32_T *pA11081 = &guidance_simulink_P.DiscreteZeroPole_A[11081];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew227 = &xnew[227];
      int_T numNonZero = 183;
      *pxnew227 = (*pA11081++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew227 += (*pA11081++) * xd[*pAidx++];
      }
    }

    xnew[227] += (guidance_simulink_P.DiscreteZeroPole_B[114])*rtb_Sum1[0];
    xnew[228] = (guidance_simulink_P.DiscreteZeroPole_A[11265])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[227];

    {
      static const int_T colAidxRow229[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow229[0];
      const real32_T *pA11266 = &guidance_simulink_P.DiscreteZeroPole_A[11266];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew229 = &xnew[229];
      int_T numNonZero = 183;
      *pxnew229 = (*pA11266++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew229 += (*pA11266++) * xd[*pAidx++];
      }
    }

    xnew[229] += (guidance_simulink_P.DiscreteZeroPole_B[115])*rtb_Sum1[0];
    xnew[230] = (guidance_simulink_P.DiscreteZeroPole_A[11450])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[229];

    {
      static const int_T colAidxRow231[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow231[0];
      const real32_T *pA11451 = &guidance_simulink_P.DiscreteZeroPole_A[11451];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew231 = &xnew[231];
      int_T numNonZero = 183;
      *pxnew231 = (*pA11451++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew231 += (*pA11451++) * xd[*pAidx++];
      }
    }

    xnew[231] += (guidance_simulink_P.DiscreteZeroPole_B[116])*rtb_Sum1[0];
    xnew[232] = (guidance_simulink_P.DiscreteZeroPole_A[11635])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[231];

    {
      static const int_T colAidxRow233[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow233[0];
      const real32_T *pA11636 = &guidance_simulink_P.DiscreteZeroPole_A[11636];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew233 = &xnew[233];
      int_T numNonZero = 183;
      *pxnew233 = (*pA11636++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew233 += (*pA11636++) * xd[*pAidx++];
      }
    }

    xnew[233] += (guidance_simulink_P.DiscreteZeroPole_B[117])*rtb_Sum1[0];
    xnew[234] = (guidance_simulink_P.DiscreteZeroPole_A[11820])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[233];

    {
      static const int_T colAidxRow235[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow235[0];
      const real32_T *pA11821 = &guidance_simulink_P.DiscreteZeroPole_A[11821];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew235 = &xnew[235];
      int_T numNonZero = 183;
      *pxnew235 = (*pA11821++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew235 += (*pA11821++) * xd[*pAidx++];
      }
    }

    xnew[235] += (guidance_simulink_P.DiscreteZeroPole_B[118])*rtb_Sum1[0];
    xnew[236] = (guidance_simulink_P.DiscreteZeroPole_A[12005])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[235];

    {
      static const int_T colAidxRow237[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow237[0];
      const real32_T *pA12006 = &guidance_simulink_P.DiscreteZeroPole_A[12006];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew237 = &xnew[237];
      int_T numNonZero = 183;
      *pxnew237 = (*pA12006++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew237 += (*pA12006++) * xd[*pAidx++];
      }
    }

    xnew[237] += (guidance_simulink_P.DiscreteZeroPole_B[119])*rtb_Sum1[0];
    xnew[238] = (guidance_simulink_P.DiscreteZeroPole_A[12190])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[237];

    {
      static const int_T colAidxRow239[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow239[0];
      const real32_T *pA12191 = &guidance_simulink_P.DiscreteZeroPole_A[12191];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew239 = &xnew[239];
      int_T numNonZero = 183;
      *pxnew239 = (*pA12191++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew239 += (*pA12191++) * xd[*pAidx++];
      }
    }

    xnew[239] += (guidance_simulink_P.DiscreteZeroPole_B[120])*rtb_Sum1[0];
    xnew[240] = (guidance_simulink_P.DiscreteZeroPole_A[12375])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[239];

    {
      static const int_T colAidxRow241[186] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241 };

      const int_T *pAidx = &colAidxRow241[0];
      const real32_T *pA12376 = &guidance_simulink_P.DiscreteZeroPole_A[12376];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew241 = &xnew[241];
      int_T numNonZero = 185;
      *pxnew241 = (*pA12376++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew241 += (*pA12376++) * xd[*pAidx++];
      }
    }

    xnew[241] += (guidance_simulink_P.DiscreteZeroPole_B[121])*rtb_Sum1[0];
    xnew[242] = (guidance_simulink_P.DiscreteZeroPole_A[12562])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[241];

    {
      static const int_T colAidxRow243[189] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244 };

      const int_T *pAidx = &colAidxRow243[0];
      const real32_T *pA12563 = &guidance_simulink_P.DiscreteZeroPole_A[12563];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew243 = &xnew[243];
      int_T numNonZero = 188;
      *pxnew243 = (*pA12563++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew243 += (*pA12563++) * xd[*pAidx++];
      }
    }

    xnew[243] += (guidance_simulink_P.DiscreteZeroPole_B[122])*rtb_Sum1[0];
    xnew[244] = (guidance_simulink_P.DiscreteZeroPole_A[12752])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[243];

    {
      static const int_T colAidxRow245[191] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246 };

      const int_T *pAidx = &colAidxRow245[0];
      const real32_T *pA12753 = &guidance_simulink_P.DiscreteZeroPole_A[12753];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew245 = &xnew[245];
      int_T numNonZero = 190;
      *pxnew245 = (*pA12753++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew245 += (*pA12753++) * xd[*pAidx++];
      }
    }

    xnew[245] += (guidance_simulink_P.DiscreteZeroPole_B[123])*rtb_Sum1[0];
    xnew[246] = (guidance_simulink_P.DiscreteZeroPole_A[12944])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[245];

    {
      static const int_T colAidxRow247[193] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248 };

      const int_T *pAidx = &colAidxRow247[0];
      const real32_T *pA12945 = &guidance_simulink_P.DiscreteZeroPole_A[12945];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew247 = &xnew[247];
      int_T numNonZero = 192;
      *pxnew247 = (*pA12945++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew247 += (*pA12945++) * xd[*pAidx++];
      }
    }

    xnew[247] += (guidance_simulink_P.DiscreteZeroPole_B[124])*rtb_Sum1[0];
    xnew[248] = (guidance_simulink_P.DiscreteZeroPole_A[13138])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[247];

    {
      static const int_T colAidxRow249[195] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249,
        250 };

      const int_T *pAidx = &colAidxRow249[0];
      const real32_T *pA13139 = &guidance_simulink_P.DiscreteZeroPole_A[13139];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE[0];
      real32_T *pxnew249 = &xnew[249];
      int_T numNonZero = 194;
      *pxnew249 = (*pA13139++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew249 += (*pA13139++) * xd[*pAidx++];
      }
    }

    xnew[249] += (guidance_simulink_P.DiscreteZeroPole_B[125])*rtb_Sum1[0];
    xnew[250] = (guidance_simulink_P.DiscreteZeroPole_A[13334])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE[249];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE[0], xnew,
                  sizeof(real32_T)*251);
  }

  /* Update for DiscreteZeroPole: '<S2>/Discrete Zero-Pole' */
  {
    real32_T xnew[251];
    xnew[0] = (guidance_simulink_P.DiscreteZeroPole_A_a[0])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
    xnew[0] += (guidance_simulink_P.DiscreteZeroPole_B_b[0])*rtb_Sum1[1];
    xnew[1] = (guidance_simulink_P.DiscreteZeroPole_A_a[1])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[2])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[1]
      + (guidance_simulink_P.DiscreteZeroPole_A_a[3])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[2];
    xnew[1] += (guidance_simulink_P.DiscreteZeroPole_B_b[1])*rtb_Sum1[1];
    xnew[2] = (guidance_simulink_P.DiscreteZeroPole_A_a[4])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[1];

    {
      static const int_T colAidxRow3[5] = { 0, 1, 2, 3, 4 };

      const int_T *pAidx = &colAidxRow3[0];
      const real32_T *pA5 = &guidance_simulink_P.DiscreteZeroPole_A_a[5];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew3 = &xnew[3];
      int_T numNonZero = 4;
      *pxnew3 = (*pA5++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew3 += (*pA5++) * xd[*pAidx++];
      }
    }

    xnew[3] += (guidance_simulink_P.DiscreteZeroPole_B_b[2])*rtb_Sum1[1];
    xnew[4] = (guidance_simulink_P.DiscreteZeroPole_A_a[10])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[3];

    {
      static const int_T colAidxRow5[7] = { 0, 1, 2, 3, 4, 5, 6 };

      const int_T *pAidx = &colAidxRow5[0];
      const real32_T *pA11 = &guidance_simulink_P.DiscreteZeroPole_A_a[11];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew5 = &xnew[5];
      int_T numNonZero = 6;
      *pxnew5 = (*pA11++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew5 += (*pA11++) * xd[*pAidx++];
      }
    }

    xnew[5] += (guidance_simulink_P.DiscreteZeroPole_B_b[3])*rtb_Sum1[1];
    xnew[6] = (guidance_simulink_P.DiscreteZeroPole_A_a[18])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[5];

    {
      static const int_T colAidxRow7[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

      const int_T *pAidx = &colAidxRow7[0];
      const real32_T *pA19 = &guidance_simulink_P.DiscreteZeroPole_A_a[19];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew7 = &xnew[7];
      int_T numNonZero = 8;
      *pxnew7 = (*pA19++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew7 += (*pA19++) * xd[*pAidx++];
      }
    }

    xnew[7] += (guidance_simulink_P.DiscreteZeroPole_B_b[4])*rtb_Sum1[1];
    xnew[8] = (guidance_simulink_P.DiscreteZeroPole_A_a[28])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[7];

    {
      static const int_T colAidxRow9[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

      const int_T *pAidx = &colAidxRow9[0];
      const real32_T *pA29 = &guidance_simulink_P.DiscreteZeroPole_A_a[29];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew9 = &xnew[9];
      int_T numNonZero = 10;
      *pxnew9 = (*pA29++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew9 += (*pA29++) * xd[*pAidx++];
      }
    }

    xnew[9] += (guidance_simulink_P.DiscreteZeroPole_B_b[5])*rtb_Sum1[1];
    xnew[10] = (guidance_simulink_P.DiscreteZeroPole_A_a[40])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[9];

    {
      static const int_T colAidxRow11[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12 };

      const int_T *pAidx = &colAidxRow11[0];
      const real32_T *pA41 = &guidance_simulink_P.DiscreteZeroPole_A_a[41];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew11 = &xnew[11];
      int_T numNonZero = 12;
      *pxnew11 = (*pA41++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew11 += (*pA41++) * xd[*pAidx++];
      }
    }

    xnew[11] += (guidance_simulink_P.DiscreteZeroPole_B_b[6])*rtb_Sum1[1];
    xnew[12] = (guidance_simulink_P.DiscreteZeroPole_A_a[54])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[11];

    {
      static const int_T colAidxRow13[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14 };

      const int_T *pAidx = &colAidxRow13[0];
      const real32_T *pA55 = &guidance_simulink_P.DiscreteZeroPole_A_a[55];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew13 = &xnew[13];
      int_T numNonZero = 14;
      *pxnew13 = (*pA55++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew13 += (*pA55++) * xd[*pAidx++];
      }
    }

    xnew[13] += (guidance_simulink_P.DiscreteZeroPole_B_b[7])*rtb_Sum1[1];
    xnew[14] = (guidance_simulink_P.DiscreteZeroPole_A_a[70])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[13];

    {
      static const int_T colAidxRow15[17] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16 };

      const int_T *pAidx = &colAidxRow15[0];
      const real32_T *pA71 = &guidance_simulink_P.DiscreteZeroPole_A_a[71];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew15 = &xnew[15];
      int_T numNonZero = 16;
      *pxnew15 = (*pA71++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew15 += (*pA71++) * xd[*pAidx++];
      }
    }

    xnew[15] += (guidance_simulink_P.DiscreteZeroPole_B_b[8])*rtb_Sum1[1];
    xnew[16] = (guidance_simulink_P.DiscreteZeroPole_A_a[88])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[15];

    {
      static const int_T colAidxRow17[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18 };

      const int_T *pAidx = &colAidxRow17[0];
      const real32_T *pA89 = &guidance_simulink_P.DiscreteZeroPole_A_a[89];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew17 = &xnew[17];
      int_T numNonZero = 18;
      *pxnew17 = (*pA89++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew17 += (*pA89++) * xd[*pAidx++];
      }
    }

    xnew[17] += (guidance_simulink_P.DiscreteZeroPole_B_b[9])*rtb_Sum1[1];
    xnew[18] = (guidance_simulink_P.DiscreteZeroPole_A_a[108])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[17];

    {
      static const int_T colAidxRow19[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

      const int_T *pAidx = &colAidxRow19[0];
      const real32_T *pA109 = &guidance_simulink_P.DiscreteZeroPole_A_a[109];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew19 = &xnew[19];
      int_T numNonZero = 20;
      *pxnew19 = (*pA109++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew19 += (*pA109++) * xd[*pAidx++];
      }
    }

    xnew[19] += (guidance_simulink_P.DiscreteZeroPole_B_b[10])*rtb_Sum1[1];
    xnew[20] = (guidance_simulink_P.DiscreteZeroPole_A_a[130])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[19];

    {
      static const int_T colAidxRow21[23] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };

      const int_T *pAidx = &colAidxRow21[0];
      const real32_T *pA131 = &guidance_simulink_P.DiscreteZeroPole_A_a[131];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew21 = &xnew[21];
      int_T numNonZero = 22;
      *pxnew21 = (*pA131++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew21 += (*pA131++) * xd[*pAidx++];
      }
    }

    xnew[21] += (guidance_simulink_P.DiscreteZeroPole_B_b[11])*rtb_Sum1[1];
    xnew[22] = (guidance_simulink_P.DiscreteZeroPole_A_a[154])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[21];

    {
      static const int_T colAidxRow23[25] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

      const int_T *pAidx = &colAidxRow23[0];
      const real32_T *pA155 = &guidance_simulink_P.DiscreteZeroPole_A_a[155];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew23 = &xnew[23];
      int_T numNonZero = 24;
      *pxnew23 = (*pA155++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew23 += (*pA155++) * xd[*pAidx++];
      }
    }

    xnew[23] += (guidance_simulink_P.DiscreteZeroPole_B_b[12])*rtb_Sum1[1];
    xnew[24] = (guidance_simulink_P.DiscreteZeroPole_A_a[180])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[23];

    {
      static const int_T colAidxRow25[27] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };

      const int_T *pAidx = &colAidxRow25[0];
      const real32_T *pA181 = &guidance_simulink_P.DiscreteZeroPole_A_a[181];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew25 = &xnew[25];
      int_T numNonZero = 26;
      *pxnew25 = (*pA181++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew25 += (*pA181++) * xd[*pAidx++];
      }
    }

    xnew[25] += (guidance_simulink_P.DiscreteZeroPole_B_b[13])*rtb_Sum1[1];
    xnew[26] = (guidance_simulink_P.DiscreteZeroPole_A_a[208])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[25];

    {
      static const int_T colAidxRow27[29] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 };

      const int_T *pAidx = &colAidxRow27[0];
      const real32_T *pA209 = &guidance_simulink_P.DiscreteZeroPole_A_a[209];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew27 = &xnew[27];
      int_T numNonZero = 28;
      *pxnew27 = (*pA209++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew27 += (*pA209++) * xd[*pAidx++];
      }
    }

    xnew[27] += (guidance_simulink_P.DiscreteZeroPole_B_b[14])*rtb_Sum1[1];
    xnew[28] = (guidance_simulink_P.DiscreteZeroPole_A_a[238])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[27];

    {
      static const int_T colAidxRow29[31] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30 };

      const int_T *pAidx = &colAidxRow29[0];
      const real32_T *pA239 = &guidance_simulink_P.DiscreteZeroPole_A_a[239];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew29 = &xnew[29];
      int_T numNonZero = 30;
      *pxnew29 = (*pA239++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew29 += (*pA239++) * xd[*pAidx++];
      }
    }

    xnew[29] += (guidance_simulink_P.DiscreteZeroPole_B_b[15])*rtb_Sum1[1];
    xnew[30] = (guidance_simulink_P.DiscreteZeroPole_A_a[270])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[29];

    {
      static const int_T colAidxRow31[33] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32 };

      const int_T *pAidx = &colAidxRow31[0];
      const real32_T *pA271 = &guidance_simulink_P.DiscreteZeroPole_A_a[271];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew31 = &xnew[31];
      int_T numNonZero = 32;
      *pxnew31 = (*pA271++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew31 += (*pA271++) * xd[*pAidx++];
      }
    }

    xnew[31] += (guidance_simulink_P.DiscreteZeroPole_B_b[16])*rtb_Sum1[1];
    xnew[32] = (guidance_simulink_P.DiscreteZeroPole_A_a[304])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[31];

    {
      static const int_T colAidxRow33[35] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow33[0];
      const real32_T *pA305 = &guidance_simulink_P.DiscreteZeroPole_A_a[305];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew33 = &xnew[33];
      int_T numNonZero = 34;
      *pxnew33 = (*pA305++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew33 += (*pA305++) * xd[*pAidx++];
      }
    }

    xnew[33] += (guidance_simulink_P.DiscreteZeroPole_B_b[17])*rtb_Sum1[1];
    xnew[34] = (guidance_simulink_P.DiscreteZeroPole_A_a[340])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[33];

    {
      static const int_T colAidxRow35[35] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34 };

      const int_T *pAidx = &colAidxRow35[0];
      const real32_T *pA341 = &guidance_simulink_P.DiscreteZeroPole_A_a[341];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew35 = &xnew[35];
      int_T numNonZero = 34;
      *pxnew35 = (*pA341++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew35 += (*pA341++) * xd[*pAidx++];
      }
    }

    xnew[35] += (guidance_simulink_P.DiscreteZeroPole_B_b[18])*rtb_Sum1[1];
    xnew[36] = 0.0;

    {
      static const int_T colAidxRow37[37] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36 };

      const int_T *pAidx = &colAidxRow37[0];
      const real32_T *pA376 = &guidance_simulink_P.DiscreteZeroPole_A_a[376];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew37 = &xnew[37];
      int_T numNonZero = 36;
      *pxnew37 = (*pA376++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew37 += (*pA376++) * xd[*pAidx++];
      }
    }

    xnew[37] += (guidance_simulink_P.DiscreteZeroPole_B_b[19])*rtb_Sum1[1];
    xnew[38] = 0.0;

    {
      static const int_T colAidxRow39[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow39[0];
      const real32_T *pA413 = &guidance_simulink_P.DiscreteZeroPole_A_a[413];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew39 = &xnew[39];
      int_T numNonZero = 37;
      *pxnew39 = (*pA413++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew39 += (*pA413++) * xd[*pAidx++];
      }
    }

    xnew[39] += (guidance_simulink_P.DiscreteZeroPole_B_b[20])*rtb_Sum1[1];
    xnew[40] = 0.0;

    {
      static const int_T colAidxRow41[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow41[0];
      const real32_T *pA451 = &guidance_simulink_P.DiscreteZeroPole_A_a[451];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew41 = &xnew[41];
      int_T numNonZero = 37;
      *pxnew41 = (*pA451++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew41 += (*pA451++) * xd[*pAidx++];
      }
    }

    xnew[41] += (guidance_simulink_P.DiscreteZeroPole_B_b[21])*rtb_Sum1[1];
    xnew[42] = 0.0;

    {
      static const int_T colAidxRow43[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow43[0];
      const real32_T *pA489 = &guidance_simulink_P.DiscreteZeroPole_A_a[489];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew43 = &xnew[43];
      int_T numNonZero = 37;
      *pxnew43 = (*pA489++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew43 += (*pA489++) * xd[*pAidx++];
      }
    }

    xnew[43] += (guidance_simulink_P.DiscreteZeroPole_B_b[22])*rtb_Sum1[1];
    xnew[44] = (guidance_simulink_P.DiscreteZeroPole_A_a[527])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[43];

    {
      static const int_T colAidxRow45[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow45[0];
      const real32_T *pA528 = &guidance_simulink_P.DiscreteZeroPole_A_a[528];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew45 = &xnew[45];
      int_T numNonZero = 37;
      *pxnew45 = (*pA528++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew45 += (*pA528++) * xd[*pAidx++];
      }
    }

    xnew[45] += (guidance_simulink_P.DiscreteZeroPole_B_b[23])*rtb_Sum1[1];
    xnew[46] = (guidance_simulink_P.DiscreteZeroPole_A_a[566])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[45];

    {
      static const int_T colAidxRow47[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow47[0];
      const real32_T *pA567 = &guidance_simulink_P.DiscreteZeroPole_A_a[567];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew47 = &xnew[47];
      int_T numNonZero = 37;
      *pxnew47 = (*pA567++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew47 += (*pA567++) * xd[*pAidx++];
      }
    }

    xnew[47] += (guidance_simulink_P.DiscreteZeroPole_B_b[24])*rtb_Sum1[1];
    xnew[48] = (guidance_simulink_P.DiscreteZeroPole_A_a[605])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[47];

    {
      static const int_T colAidxRow49[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow49[0];
      const real32_T *pA606 = &guidance_simulink_P.DiscreteZeroPole_A_a[606];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew49 = &xnew[49];
      int_T numNonZero = 37;
      *pxnew49 = (*pA606++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew49 += (*pA606++) * xd[*pAidx++];
      }
    }

    xnew[49] += (guidance_simulink_P.DiscreteZeroPole_B_b[25])*rtb_Sum1[1];
    xnew[50] = (guidance_simulink_P.DiscreteZeroPole_A_a[644])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[49];

    {
      static const int_T colAidxRow51[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow51[0];
      const real32_T *pA645 = &guidance_simulink_P.DiscreteZeroPole_A_a[645];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew51 = &xnew[51];
      int_T numNonZero = 37;
      *pxnew51 = (*pA645++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew51 += (*pA645++) * xd[*pAidx++];
      }
    }

    xnew[51] += (guidance_simulink_P.DiscreteZeroPole_B_b[26])*rtb_Sum1[1];
    xnew[52] = 0.0;

    {
      static const int_T colAidxRow53[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow53[0];
      const real32_T *pA683 = &guidance_simulink_P.DiscreteZeroPole_A_a[683];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew53 = &xnew[53];
      int_T numNonZero = 37;
      *pxnew53 = (*pA683++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew53 += (*pA683++) * xd[*pAidx++];
      }
    }

    xnew[53] += (guidance_simulink_P.DiscreteZeroPole_B_b[27])*rtb_Sum1[1];
    xnew[54] = 0.0;

    {
      static const int_T colAidxRow55[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow55[0];
      const real32_T *pA721 = &guidance_simulink_P.DiscreteZeroPole_A_a[721];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew55 = &xnew[55];
      int_T numNonZero = 37;
      *pxnew55 = (*pA721++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew55 += (*pA721++) * xd[*pAidx++];
      }
    }

    xnew[55] += (guidance_simulink_P.DiscreteZeroPole_B_b[28])*rtb_Sum1[1];
    xnew[56] = 0.0;

    {
      static const int_T colAidxRow57[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38 };

      const int_T *pAidx = &colAidxRow57[0];
      const real32_T *pA759 = &guidance_simulink_P.DiscreteZeroPole_A_a[759];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew57 = &xnew[57];
      int_T numNonZero = 37;
      *pxnew57 = (*pA759++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew57 += (*pA759++) * xd[*pAidx++];
      }
    }

    xnew[57] += (guidance_simulink_P.DiscreteZeroPole_B_b[29])*rtb_Sum1[1];
    xnew[58] = 0.0;

    {
      static const int_T colAidxRow59[40] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60 };

      const int_T *pAidx = &colAidxRow59[0];
      const real32_T *pA797 = &guidance_simulink_P.DiscreteZeroPole_A_a[797];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew59 = &xnew[59];
      int_T numNonZero = 39;
      *pxnew59 = (*pA797++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew59 += (*pA797++) * xd[*pAidx++];
      }
    }

    xnew[59] += (guidance_simulink_P.DiscreteZeroPole_B_b[30])*rtb_Sum1[1];
    xnew[60] = (guidance_simulink_P.DiscreteZeroPole_A_a[837])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[59];

    {
      static const int_T colAidxRow61[42] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62 };

      const int_T *pAidx = &colAidxRow61[0];
      const real32_T *pA838 = &guidance_simulink_P.DiscreteZeroPole_A_a[838];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew61 = &xnew[61];
      int_T numNonZero = 41;
      *pxnew61 = (*pA838++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew61 += (*pA838++) * xd[*pAidx++];
      }
    }

    xnew[61] += (guidance_simulink_P.DiscreteZeroPole_B_b[31])*rtb_Sum1[1];
    xnew[62] = (guidance_simulink_P.DiscreteZeroPole_A_a[880])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[61];

    {
      static const int_T colAidxRow63[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64 };

      const int_T *pAidx = &colAidxRow63[0];
      const real32_T *pA881 = &guidance_simulink_P.DiscreteZeroPole_A_a[881];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew63 = &xnew[63];
      int_T numNonZero = 43;
      *pxnew63 = (*pA881++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew63 += (*pA881++) * xd[*pAidx++];
      }
    }

    xnew[63] += (guidance_simulink_P.DiscreteZeroPole_B_b[32])*rtb_Sum1[1];
    xnew[64] = (guidance_simulink_P.DiscreteZeroPole_A_a[925])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[63];

    {
      static const int_T colAidxRow65[46] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66 };

      const int_T *pAidx = &colAidxRow65[0];
      const real32_T *pA926 = &guidance_simulink_P.DiscreteZeroPole_A_a[926];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew65 = &xnew[65];
      int_T numNonZero = 45;
      *pxnew65 = (*pA926++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew65 += (*pA926++) * xd[*pAidx++];
      }
    }

    xnew[65] += (guidance_simulink_P.DiscreteZeroPole_B_b[33])*rtb_Sum1[1];
    xnew[66] = (guidance_simulink_P.DiscreteZeroPole_A_a[972])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[65];

    {
      static const int_T colAidxRow67[48] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68 };

      const int_T *pAidx = &colAidxRow67[0];
      const real32_T *pA973 = &guidance_simulink_P.DiscreteZeroPole_A_a[973];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew67 = &xnew[67];
      int_T numNonZero = 47;
      *pxnew67 = (*pA973++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew67 += (*pA973++) * xd[*pAidx++];
      }
    }

    xnew[67] += (guidance_simulink_P.DiscreteZeroPole_B_b[34])*rtb_Sum1[1];
    xnew[68] = (guidance_simulink_P.DiscreteZeroPole_A_a[1021])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[67];

    {
      static const int_T colAidxRow69[50] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70 };

      const int_T *pAidx = &colAidxRow69[0];
      const real32_T *pA1022 = &guidance_simulink_P.DiscreteZeroPole_A_a[1022];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew69 = &xnew[69];
      int_T numNonZero = 49;
      *pxnew69 = (*pA1022++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew69 += (*pA1022++) * xd[*pAidx++];
      }
    }

    xnew[69] += (guidance_simulink_P.DiscreteZeroPole_B_b[35])*rtb_Sum1[1];
    xnew[70] = (guidance_simulink_P.DiscreteZeroPole_A_a[1072])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[69];

    {
      static const int_T colAidxRow71[52] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72 };

      const int_T *pAidx = &colAidxRow71[0];
      const real32_T *pA1073 = &guidance_simulink_P.DiscreteZeroPole_A_a[1073];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew71 = &xnew[71];
      int_T numNonZero = 51;
      *pxnew71 = (*pA1073++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew71 += (*pA1073++) * xd[*pAidx++];
      }
    }

    xnew[71] += (guidance_simulink_P.DiscreteZeroPole_B_b[36])*rtb_Sum1[1];
    xnew[72] = (guidance_simulink_P.DiscreteZeroPole_A_a[1125])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[71];

    {
      static const int_T colAidxRow73[54] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74 };

      const int_T *pAidx = &colAidxRow73[0];
      const real32_T *pA1126 = &guidance_simulink_P.DiscreteZeroPole_A_a[1126];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew73 = &xnew[73];
      int_T numNonZero = 53;
      *pxnew73 = (*pA1126++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew73 += (*pA1126++) * xd[*pAidx++];
      }
    }

    xnew[73] += (guidance_simulink_P.DiscreteZeroPole_B_b[37])*rtb_Sum1[1];
    xnew[74] = (guidance_simulink_P.DiscreteZeroPole_A_a[1180])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[73];

    {
      static const int_T colAidxRow75[56] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76 };

      const int_T *pAidx = &colAidxRow75[0];
      const real32_T *pA1181 = &guidance_simulink_P.DiscreteZeroPole_A_a[1181];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew75 = &xnew[75];
      int_T numNonZero = 55;
      *pxnew75 = (*pA1181++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew75 += (*pA1181++) * xd[*pAidx++];
      }
    }

    xnew[75] += (guidance_simulink_P.DiscreteZeroPole_B_b[38])*rtb_Sum1[1];
    xnew[76] = (guidance_simulink_P.DiscreteZeroPole_A_a[1237])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[75];

    {
      static const int_T colAidxRow77[58] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 };

      const int_T *pAidx = &colAidxRow77[0];
      const real32_T *pA1238 = &guidance_simulink_P.DiscreteZeroPole_A_a[1238];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew77 = &xnew[77];
      int_T numNonZero = 57;
      *pxnew77 = (*pA1238++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew77 += (*pA1238++) * xd[*pAidx++];
      }
    }

    xnew[77] += (guidance_simulink_P.DiscreteZeroPole_B_b[39])*rtb_Sum1[1];
    xnew[78] = (guidance_simulink_P.DiscreteZeroPole_A_a[1296])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[77];

    {
      static const int_T colAidxRow79[60] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };

      const int_T *pAidx = &colAidxRow79[0];
      const real32_T *pA1297 = &guidance_simulink_P.DiscreteZeroPole_A_a[1297];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew79 = &xnew[79];
      int_T numNonZero = 59;
      *pxnew79 = (*pA1297++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew79 += (*pA1297++) * xd[*pAidx++];
      }
    }

    xnew[79] += (guidance_simulink_P.DiscreteZeroPole_B_b[40])*rtb_Sum1[1];
    xnew[80] = (guidance_simulink_P.DiscreteZeroPole_A_a[1357])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[79];

    {
      static const int_T colAidxRow81[62] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82 };

      const int_T *pAidx = &colAidxRow81[0];
      const real32_T *pA1358 = &guidance_simulink_P.DiscreteZeroPole_A_a[1358];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew81 = &xnew[81];
      int_T numNonZero = 61;
      *pxnew81 = (*pA1358++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew81 += (*pA1358++) * xd[*pAidx++];
      }
    }

    xnew[81] += (guidance_simulink_P.DiscreteZeroPole_B_b[41])*rtb_Sum1[1];
    xnew[82] = (guidance_simulink_P.DiscreteZeroPole_A_a[1420])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[81];

    {
      static const int_T colAidxRow83[64] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84 };

      const int_T *pAidx = &colAidxRow83[0];
      const real32_T *pA1421 = &guidance_simulink_P.DiscreteZeroPole_A_a[1421];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew83 = &xnew[83];
      int_T numNonZero = 63;
      *pxnew83 = (*pA1421++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew83 += (*pA1421++) * xd[*pAidx++];
      }
    }

    xnew[83] += (guidance_simulink_P.DiscreteZeroPole_B_b[42])*rtb_Sum1[1];
    xnew[84] = (guidance_simulink_P.DiscreteZeroPole_A_a[1485])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[83];

    {
      static const int_T colAidxRow85[66] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86 };

      const int_T *pAidx = &colAidxRow85[0];
      const real32_T *pA1486 = &guidance_simulink_P.DiscreteZeroPole_A_a[1486];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew85 = &xnew[85];
      int_T numNonZero = 65;
      *pxnew85 = (*pA1486++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew85 += (*pA1486++) * xd[*pAidx++];
      }
    }

    xnew[85] += (guidance_simulink_P.DiscreteZeroPole_B_b[43])*rtb_Sum1[1];
    xnew[86] = (guidance_simulink_P.DiscreteZeroPole_A_a[1552])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[85];

    {
      static const int_T colAidxRow87[68] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88 };

      const int_T *pAidx = &colAidxRow87[0];
      const real32_T *pA1553 = &guidance_simulink_P.DiscreteZeroPole_A_a[1553];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew87 = &xnew[87];
      int_T numNonZero = 67;
      *pxnew87 = (*pA1553++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew87 += (*pA1553++) * xd[*pAidx++];
      }
    }

    xnew[87] += (guidance_simulink_P.DiscreteZeroPole_B_b[44])*rtb_Sum1[1];
    xnew[88] = (guidance_simulink_P.DiscreteZeroPole_A_a[1621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[87];

    {
      static const int_T colAidxRow89[70] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90 };

      const int_T *pAidx = &colAidxRow89[0];
      const real32_T *pA1622 = &guidance_simulink_P.DiscreteZeroPole_A_a[1622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew89 = &xnew[89];
      int_T numNonZero = 69;
      *pxnew89 = (*pA1622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew89 += (*pA1622++) * xd[*pAidx++];
      }
    }

    xnew[89] += (guidance_simulink_P.DiscreteZeroPole_B_b[45])*rtb_Sum1[1];
    xnew[90] = (guidance_simulink_P.DiscreteZeroPole_A_a[1692])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[89];

    {
      static const int_T colAidxRow91[72] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92 };

      const int_T *pAidx = &colAidxRow91[0];
      const real32_T *pA1693 = &guidance_simulink_P.DiscreteZeroPole_A_a[1693];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew91 = &xnew[91];
      int_T numNonZero = 71;
      *pxnew91 = (*pA1693++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew91 += (*pA1693++) * xd[*pAidx++];
      }
    }

    xnew[91] += (guidance_simulink_P.DiscreteZeroPole_B_b[46])*rtb_Sum1[1];
    xnew[92] = (guidance_simulink_P.DiscreteZeroPole_A_a[1765])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[91];

    {
      static const int_T colAidxRow93[74] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94 };

      const int_T *pAidx = &colAidxRow93[0];
      const real32_T *pA1766 = &guidance_simulink_P.DiscreteZeroPole_A_a[1766];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew93 = &xnew[93];
      int_T numNonZero = 73;
      *pxnew93 = (*pA1766++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew93 += (*pA1766++) * xd[*pAidx++];
      }
    }

    xnew[93] += (guidance_simulink_P.DiscreteZeroPole_B_b[47])*rtb_Sum1[1];
    xnew[94] = (guidance_simulink_P.DiscreteZeroPole_A_a[1840])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[93];

    {
      static const int_T colAidxRow95[76] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96 };

      const int_T *pAidx = &colAidxRow95[0];
      const real32_T *pA1841 = &guidance_simulink_P.DiscreteZeroPole_A_a[1841];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew95 = &xnew[95];
      int_T numNonZero = 75;
      *pxnew95 = (*pA1841++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew95 += (*pA1841++) * xd[*pAidx++];
      }
    }

    xnew[95] += (guidance_simulink_P.DiscreteZeroPole_B_b[48])*rtb_Sum1[1];
    xnew[96] = (guidance_simulink_P.DiscreteZeroPole_A_a[1917])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[95];

    {
      static const int_T colAidxRow97[78] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98 };

      const int_T *pAidx = &colAidxRow97[0];
      const real32_T *pA1918 = &guidance_simulink_P.DiscreteZeroPole_A_a[1918];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew97 = &xnew[97];
      int_T numNonZero = 77;
      *pxnew97 = (*pA1918++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew97 += (*pA1918++) * xd[*pAidx++];
      }
    }

    xnew[97] += (guidance_simulink_P.DiscreteZeroPole_B_b[49])*rtb_Sum1[1];
    xnew[98] = (guidance_simulink_P.DiscreteZeroPole_A_a[1996])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[97];

    {
      static const int_T colAidxRow99[80] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 };

      const int_T *pAidx = &colAidxRow99[0];
      const real32_T *pA1997 = &guidance_simulink_P.DiscreteZeroPole_A_a[1997];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew99 = &xnew[99];
      int_T numNonZero = 79;
      *pxnew99 = (*pA1997++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew99 += (*pA1997++) * xd[*pAidx++];
      }
    }

    xnew[99] += (guidance_simulink_P.DiscreteZeroPole_B_b[50])*rtb_Sum1[1];
    xnew[100] = (guidance_simulink_P.DiscreteZeroPole_A_a[2077])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[99];

    {
      static const int_T colAidxRow101[82] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102 };

      const int_T *pAidx = &colAidxRow101[0];
      const real32_T *pA2078 = &guidance_simulink_P.DiscreteZeroPole_A_a[2078];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew101 = &xnew[101];
      int_T numNonZero = 81;
      *pxnew101 = (*pA2078++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew101 += (*pA2078++) * xd[*pAidx++];
      }
    }

    xnew[101] += (guidance_simulink_P.DiscreteZeroPole_B_b[51])*rtb_Sum1[1];
    xnew[102] = (guidance_simulink_P.DiscreteZeroPole_A_a[2160])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[101];

    {
      static const int_T colAidxRow103[84] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104 };

      const int_T *pAidx = &colAidxRow103[0];
      const real32_T *pA2161 = &guidance_simulink_P.DiscreteZeroPole_A_a[2161];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew103 = &xnew[103];
      int_T numNonZero = 83;
      *pxnew103 = (*pA2161++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew103 += (*pA2161++) * xd[*pAidx++];
      }
    }

    xnew[103] += (guidance_simulink_P.DiscreteZeroPole_B_b[52])*rtb_Sum1[1];
    xnew[104] = (guidance_simulink_P.DiscreteZeroPole_A_a[2245])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[103];

    {
      static const int_T colAidxRow105[86] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106 };

      const int_T *pAidx = &colAidxRow105[0];
      const real32_T *pA2246 = &guidance_simulink_P.DiscreteZeroPole_A_a[2246];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew105 = &xnew[105];
      int_T numNonZero = 85;
      *pxnew105 = (*pA2246++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew105 += (*pA2246++) * xd[*pAidx++];
      }
    }

    xnew[105] += (guidance_simulink_P.DiscreteZeroPole_B_b[53])*rtb_Sum1[1];
    xnew[106] = (guidance_simulink_P.DiscreteZeroPole_A_a[2332])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[105];

    {
      static const int_T colAidxRow107[88] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108 };

      const int_T *pAidx = &colAidxRow107[0];
      const real32_T *pA2333 = &guidance_simulink_P.DiscreteZeroPole_A_a[2333];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew107 = &xnew[107];
      int_T numNonZero = 87;
      *pxnew107 = (*pA2333++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew107 += (*pA2333++) * xd[*pAidx++];
      }
    }

    xnew[107] += (guidance_simulink_P.DiscreteZeroPole_B_b[54])*rtb_Sum1[1];
    xnew[108] = (guidance_simulink_P.DiscreteZeroPole_A_a[2421])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[107];

    {
      static const int_T colAidxRow109[90] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110 };

      const int_T *pAidx = &colAidxRow109[0];
      const real32_T *pA2422 = &guidance_simulink_P.DiscreteZeroPole_A_a[2422];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew109 = &xnew[109];
      int_T numNonZero = 89;
      *pxnew109 = (*pA2422++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew109 += (*pA2422++) * xd[*pAidx++];
      }
    }

    xnew[109] += (guidance_simulink_P.DiscreteZeroPole_B_b[55])*rtb_Sum1[1];
    xnew[110] = (guidance_simulink_P.DiscreteZeroPole_A_a[2512])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[109];

    {
      static const int_T colAidxRow111[92] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112 };

      const int_T *pAidx = &colAidxRow111[0];
      const real32_T *pA2513 = &guidance_simulink_P.DiscreteZeroPole_A_a[2513];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew111 = &xnew[111];
      int_T numNonZero = 91;
      *pxnew111 = (*pA2513++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew111 += (*pA2513++) * xd[*pAidx++];
      }
    }

    xnew[111] += (guidance_simulink_P.DiscreteZeroPole_B_b[56])*rtb_Sum1[1];
    xnew[112] = (guidance_simulink_P.DiscreteZeroPole_A_a[2605])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[111];

    {
      static const int_T colAidxRow113[94] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114 };

      const int_T *pAidx = &colAidxRow113[0];
      const real32_T *pA2606 = &guidance_simulink_P.DiscreteZeroPole_A_a[2606];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew113 = &xnew[113];
      int_T numNonZero = 93;
      *pxnew113 = (*pA2606++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew113 += (*pA2606++) * xd[*pAidx++];
      }
    }

    xnew[113] += (guidance_simulink_P.DiscreteZeroPole_B_b[57])*rtb_Sum1[1];
    xnew[114] = (guidance_simulink_P.DiscreteZeroPole_A_a[2700])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[113];

    {
      static const int_T colAidxRow115[96] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116 };

      const int_T *pAidx = &colAidxRow115[0];
      const real32_T *pA2701 = &guidance_simulink_P.DiscreteZeroPole_A_a[2701];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew115 = &xnew[115];
      int_T numNonZero = 95;
      *pxnew115 = (*pA2701++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew115 += (*pA2701++) * xd[*pAidx++];
      }
    }

    xnew[115] += (guidance_simulink_P.DiscreteZeroPole_B_b[58])*rtb_Sum1[1];
    xnew[116] = (guidance_simulink_P.DiscreteZeroPole_A_a[2797])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[115];

    {
      static const int_T colAidxRow117[98] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118 };

      const int_T *pAidx = &colAidxRow117[0];
      const real32_T *pA2798 = &guidance_simulink_P.DiscreteZeroPole_A_a[2798];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew117 = &xnew[117];
      int_T numNonZero = 97;
      *pxnew117 = (*pA2798++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew117 += (*pA2798++) * xd[*pAidx++];
      }
    }

    xnew[117] += (guidance_simulink_P.DiscreteZeroPole_B_b[59])*rtb_Sum1[1];
    xnew[118] = (guidance_simulink_P.DiscreteZeroPole_A_a[2896])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[117];

    {
      static const int_T colAidxRow119[100] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120 };

      const int_T *pAidx = &colAidxRow119[0];
      const real32_T *pA2897 = &guidance_simulink_P.DiscreteZeroPole_A_a[2897];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew119 = &xnew[119];
      int_T numNonZero = 99;
      *pxnew119 = (*pA2897++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew119 += (*pA2897++) * xd[*pAidx++];
      }
    }

    xnew[119] += (guidance_simulink_P.DiscreteZeroPole_B_b[60])*rtb_Sum1[1];
    xnew[120] = (guidance_simulink_P.DiscreteZeroPole_A_a[2997])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[119];

    {
      static const int_T colAidxRow121[102] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122 };

      const int_T *pAidx = &colAidxRow121[0];
      const real32_T *pA2998 = &guidance_simulink_P.DiscreteZeroPole_A_a[2998];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew121 = &xnew[121];
      int_T numNonZero = 101;
      *pxnew121 = (*pA2998++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew121 += (*pA2998++) * xd[*pAidx++];
      }
    }

    xnew[121] += (guidance_simulink_P.DiscreteZeroPole_B_b[61])*rtb_Sum1[1];
    xnew[122] = (guidance_simulink_P.DiscreteZeroPole_A_a[3100])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[121];

    {
      static const int_T colAidxRow123[104] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124 };

      const int_T *pAidx = &colAidxRow123[0];
      const real32_T *pA3101 = &guidance_simulink_P.DiscreteZeroPole_A_a[3101];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew123 = &xnew[123];
      int_T numNonZero = 103;
      *pxnew123 = (*pA3101++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew123 += (*pA3101++) * xd[*pAidx++];
      }
    }

    xnew[123] += (guidance_simulink_P.DiscreteZeroPole_B_b[62])*rtb_Sum1[1];
    xnew[124] = (guidance_simulink_P.DiscreteZeroPole_A_a[3205])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[123];

    {
      static const int_T colAidxRow125[106] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126 };

      const int_T *pAidx = &colAidxRow125[0];
      const real32_T *pA3206 = &guidance_simulink_P.DiscreteZeroPole_A_a[3206];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew125 = &xnew[125];
      int_T numNonZero = 105;
      *pxnew125 = (*pA3206++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew125 += (*pA3206++) * xd[*pAidx++];
      }
    }

    xnew[125] += (guidance_simulink_P.DiscreteZeroPole_B_b[63])*rtb_Sum1[1];
    xnew[126] = (guidance_simulink_P.DiscreteZeroPole_A_a[3312])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[125];

    {
      static const int_T colAidxRow127[108] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128 };

      const int_T *pAidx = &colAidxRow127[0];
      const real32_T *pA3313 = &guidance_simulink_P.DiscreteZeroPole_A_a[3313];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew127 = &xnew[127];
      int_T numNonZero = 107;
      *pxnew127 = (*pA3313++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew127 += (*pA3313++) * xd[*pAidx++];
      }
    }

    xnew[127] += (guidance_simulink_P.DiscreteZeroPole_B_b[64])*rtb_Sum1[1];
    xnew[128] = (guidance_simulink_P.DiscreteZeroPole_A_a[3421])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[127];

    {
      static const int_T colAidxRow129[110] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130 };

      const int_T *pAidx = &colAidxRow129[0];
      const real32_T *pA3422 = &guidance_simulink_P.DiscreteZeroPole_A_a[3422];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew129 = &xnew[129];
      int_T numNonZero = 109;
      *pxnew129 = (*pA3422++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew129 += (*pA3422++) * xd[*pAidx++];
      }
    }

    xnew[129] += (guidance_simulink_P.DiscreteZeroPole_B_b[65])*rtb_Sum1[1];
    xnew[130] = (guidance_simulink_P.DiscreteZeroPole_A_a[3532])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[129];

    {
      static const int_T colAidxRow131[112] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132 };

      const int_T *pAidx = &colAidxRow131[0];
      const real32_T *pA3533 = &guidance_simulink_P.DiscreteZeroPole_A_a[3533];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew131 = &xnew[131];
      int_T numNonZero = 111;
      *pxnew131 = (*pA3533++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew131 += (*pA3533++) * xd[*pAidx++];
      }
    }

    xnew[131] += (guidance_simulink_P.DiscreteZeroPole_B_b[66])*rtb_Sum1[1];
    xnew[132] = (guidance_simulink_P.DiscreteZeroPole_A_a[3645])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[131];

    {
      static const int_T colAidxRow133[114] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134 };

      const int_T *pAidx = &colAidxRow133[0];
      const real32_T *pA3646 = &guidance_simulink_P.DiscreteZeroPole_A_a[3646];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew133 = &xnew[133];
      int_T numNonZero = 113;
      *pxnew133 = (*pA3646++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew133 += (*pA3646++) * xd[*pAidx++];
      }
    }

    xnew[133] += (guidance_simulink_P.DiscreteZeroPole_B_b[67])*rtb_Sum1[1];
    xnew[134] = (guidance_simulink_P.DiscreteZeroPole_A_a[3760])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[133];

    {
      static const int_T colAidxRow135[116] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136 };

      const int_T *pAidx = &colAidxRow135[0];
      const real32_T *pA3761 = &guidance_simulink_P.DiscreteZeroPole_A_a[3761];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew135 = &xnew[135];
      int_T numNonZero = 115;
      *pxnew135 = (*pA3761++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew135 += (*pA3761++) * xd[*pAidx++];
      }
    }

    xnew[135] += (guidance_simulink_P.DiscreteZeroPole_B_b[68])*rtb_Sum1[1];
    xnew[136] = (guidance_simulink_P.DiscreteZeroPole_A_a[3877])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[135];

    {
      static const int_T colAidxRow137[118] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138 };

      const int_T *pAidx = &colAidxRow137[0];
      const real32_T *pA3878 = &guidance_simulink_P.DiscreteZeroPole_A_a[3878];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew137 = &xnew[137];
      int_T numNonZero = 117;
      *pxnew137 = (*pA3878++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew137 += (*pA3878++) * xd[*pAidx++];
      }
    }

    xnew[137] += (guidance_simulink_P.DiscreteZeroPole_B_b[69])*rtb_Sum1[1];
    xnew[138] = (guidance_simulink_P.DiscreteZeroPole_A_a[3996])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[137];

    {
      static const int_T colAidxRow139[120] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140 };

      const int_T *pAidx = &colAidxRow139[0];
      const real32_T *pA3997 = &guidance_simulink_P.DiscreteZeroPole_A_a[3997];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew139 = &xnew[139];
      int_T numNonZero = 119;
      *pxnew139 = (*pA3997++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew139 += (*pA3997++) * xd[*pAidx++];
      }
    }

    xnew[139] += (guidance_simulink_P.DiscreteZeroPole_B_b[70])*rtb_Sum1[1];
    xnew[140] = (guidance_simulink_P.DiscreteZeroPole_A_a[4117])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[139];

    {
      static const int_T colAidxRow141[122] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142 };

      const int_T *pAidx = &colAidxRow141[0];
      const real32_T *pA4118 = &guidance_simulink_P.DiscreteZeroPole_A_a[4118];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew141 = &xnew[141];
      int_T numNonZero = 121;
      *pxnew141 = (*pA4118++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew141 += (*pA4118++) * xd[*pAidx++];
      }
    }

    xnew[141] += (guidance_simulink_P.DiscreteZeroPole_B_b[71])*rtb_Sum1[1];
    xnew[142] = (guidance_simulink_P.DiscreteZeroPole_A_a[4240])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[141];

    {
      static const int_T colAidxRow143[124] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144 };

      const int_T *pAidx = &colAidxRow143[0];
      const real32_T *pA4241 = &guidance_simulink_P.DiscreteZeroPole_A_a[4241];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew143 = &xnew[143];
      int_T numNonZero = 123;
      *pxnew143 = (*pA4241++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew143 += (*pA4241++) * xd[*pAidx++];
      }
    }

    xnew[143] += (guidance_simulink_P.DiscreteZeroPole_B_b[72])*rtb_Sum1[1];
    xnew[144] = (guidance_simulink_P.DiscreteZeroPole_A_a[4365])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[143];

    {
      static const int_T colAidxRow145[126] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146 };

      const int_T *pAidx = &colAidxRow145[0];
      const real32_T *pA4366 = &guidance_simulink_P.DiscreteZeroPole_A_a[4366];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew145 = &xnew[145];
      int_T numNonZero = 125;
      *pxnew145 = (*pA4366++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew145 += (*pA4366++) * xd[*pAidx++];
      }
    }

    xnew[145] += (guidance_simulink_P.DiscreteZeroPole_B_b[73])*rtb_Sum1[1];
    xnew[146] = (guidance_simulink_P.DiscreteZeroPole_A_a[4492])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[145];

    {
      static const int_T colAidxRow147[128] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148 };

      const int_T *pAidx = &colAidxRow147[0];
      const real32_T *pA4493 = &guidance_simulink_P.DiscreteZeroPole_A_a[4493];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew147 = &xnew[147];
      int_T numNonZero = 127;
      *pxnew147 = (*pA4493++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew147 += (*pA4493++) * xd[*pAidx++];
      }
    }

    xnew[147] += (guidance_simulink_P.DiscreteZeroPole_B_b[74])*rtb_Sum1[1];
    xnew[148] = (guidance_simulink_P.DiscreteZeroPole_A_a[4621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[147];

    {
      static const int_T colAidxRow149[130] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150 };

      const int_T *pAidx = &colAidxRow149[0];
      const real32_T *pA4622 = &guidance_simulink_P.DiscreteZeroPole_A_a[4622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew149 = &xnew[149];
      int_T numNonZero = 129;
      *pxnew149 = (*pA4622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew149 += (*pA4622++) * xd[*pAidx++];
      }
    }

    xnew[149] += (guidance_simulink_P.DiscreteZeroPole_B_b[75])*rtb_Sum1[1];
    xnew[150] = (guidance_simulink_P.DiscreteZeroPole_A_a[4752])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[149];

    {
      static const int_T colAidxRow151[132] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152 };

      const int_T *pAidx = &colAidxRow151[0];
      const real32_T *pA4753 = &guidance_simulink_P.DiscreteZeroPole_A_a[4753];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew151 = &xnew[151];
      int_T numNonZero = 131;
      *pxnew151 = (*pA4753++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew151 += (*pA4753++) * xd[*pAidx++];
      }
    }

    xnew[151] += (guidance_simulink_P.DiscreteZeroPole_B_b[76])*rtb_Sum1[1];
    xnew[152] = (guidance_simulink_P.DiscreteZeroPole_A_a[4885])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[151];

    {
      static const int_T colAidxRow153[134] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154 };

      const int_T *pAidx = &colAidxRow153[0];
      const real32_T *pA4886 = &guidance_simulink_P.DiscreteZeroPole_A_a[4886];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew153 = &xnew[153];
      int_T numNonZero = 133;
      *pxnew153 = (*pA4886++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew153 += (*pA4886++) * xd[*pAidx++];
      }
    }

    xnew[153] += (guidance_simulink_P.DiscreteZeroPole_B_b[77])*rtb_Sum1[1];
    xnew[154] = (guidance_simulink_P.DiscreteZeroPole_A_a[5020])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[153];

    {
      static const int_T colAidxRow155[136] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156 };

      const int_T *pAidx = &colAidxRow155[0];
      const real32_T *pA5021 = &guidance_simulink_P.DiscreteZeroPole_A_a[5021];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew155 = &xnew[155];
      int_T numNonZero = 135;
      *pxnew155 = (*pA5021++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew155 += (*pA5021++) * xd[*pAidx++];
      }
    }

    xnew[155] += (guidance_simulink_P.DiscreteZeroPole_B_b[78])*rtb_Sum1[1];
    xnew[156] = (guidance_simulink_P.DiscreteZeroPole_A_a[5157])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[155];

    {
      static const int_T colAidxRow157[138] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158 };

      const int_T *pAidx = &colAidxRow157[0];
      const real32_T *pA5158 = &guidance_simulink_P.DiscreteZeroPole_A_a[5158];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew157 = &xnew[157];
      int_T numNonZero = 137;
      *pxnew157 = (*pA5158++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew157 += (*pA5158++) * xd[*pAidx++];
      }
    }

    xnew[157] += (guidance_simulink_P.DiscreteZeroPole_B_b[79])*rtb_Sum1[1];
    xnew[158] = (guidance_simulink_P.DiscreteZeroPole_A_a[5296])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[157];

    {
      static const int_T colAidxRow159[140] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160 };

      const int_T *pAidx = &colAidxRow159[0];
      const real32_T *pA5297 = &guidance_simulink_P.DiscreteZeroPole_A_a[5297];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew159 = &xnew[159];
      int_T numNonZero = 139;
      *pxnew159 = (*pA5297++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew159 += (*pA5297++) * xd[*pAidx++];
      }
    }

    xnew[159] += (guidance_simulink_P.DiscreteZeroPole_B_b[80])*rtb_Sum1[1];
    xnew[160] = (guidance_simulink_P.DiscreteZeroPole_A_a[5437])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[159];

    {
      static const int_T colAidxRow161[142] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162 };

      const int_T *pAidx = &colAidxRow161[0];
      const real32_T *pA5438 = &guidance_simulink_P.DiscreteZeroPole_A_a[5438];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew161 = &xnew[161];
      int_T numNonZero = 141;
      *pxnew161 = (*pA5438++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew161 += (*pA5438++) * xd[*pAidx++];
      }
    }

    xnew[161] += (guidance_simulink_P.DiscreteZeroPole_B_b[81])*rtb_Sum1[1];
    xnew[162] = (guidance_simulink_P.DiscreteZeroPole_A_a[5580])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[161];

    {
      static const int_T colAidxRow163[144] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164 };

      const int_T *pAidx = &colAidxRow163[0];
      const real32_T *pA5581 = &guidance_simulink_P.DiscreteZeroPole_A_a[5581];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew163 = &xnew[163];
      int_T numNonZero = 143;
      *pxnew163 = (*pA5581++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew163 += (*pA5581++) * xd[*pAidx++];
      }
    }

    xnew[163] += (guidance_simulink_P.DiscreteZeroPole_B_b[82])*rtb_Sum1[1];
    xnew[164] = (guidance_simulink_P.DiscreteZeroPole_A_a[5725])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[163];

    {
      static const int_T colAidxRow165[146] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166 };

      const int_T *pAidx = &colAidxRow165[0];
      const real32_T *pA5726 = &guidance_simulink_P.DiscreteZeroPole_A_a[5726];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew165 = &xnew[165];
      int_T numNonZero = 145;
      *pxnew165 = (*pA5726++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew165 += (*pA5726++) * xd[*pAidx++];
      }
    }

    xnew[165] += (guidance_simulink_P.DiscreteZeroPole_B_b[83])*rtb_Sum1[1];
    xnew[166] = (guidance_simulink_P.DiscreteZeroPole_A_a[5872])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[165];

    {
      static const int_T colAidxRow167[148] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168 };

      const int_T *pAidx = &colAidxRow167[0];
      const real32_T *pA5873 = &guidance_simulink_P.DiscreteZeroPole_A_a[5873];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew167 = &xnew[167];
      int_T numNonZero = 147;
      *pxnew167 = (*pA5873++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew167 += (*pA5873++) * xd[*pAidx++];
      }
    }

    xnew[167] += (guidance_simulink_P.DiscreteZeroPole_B_b[84])*rtb_Sum1[1];
    xnew[168] = (guidance_simulink_P.DiscreteZeroPole_A_a[6021])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[167];

    {
      static const int_T colAidxRow169[150] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170 };

      const int_T *pAidx = &colAidxRow169[0];
      const real32_T *pA6022 = &guidance_simulink_P.DiscreteZeroPole_A_a[6022];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew169 = &xnew[169];
      int_T numNonZero = 149;
      *pxnew169 = (*pA6022++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew169 += (*pA6022++) * xd[*pAidx++];
      }
    }

    xnew[169] += (guidance_simulink_P.DiscreteZeroPole_B_b[85])*rtb_Sum1[1];
    xnew[170] = (guidance_simulink_P.DiscreteZeroPole_A_a[6172])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[169];

    {
      static const int_T colAidxRow171[152] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172 };

      const int_T *pAidx = &colAidxRow171[0];
      const real32_T *pA6173 = &guidance_simulink_P.DiscreteZeroPole_A_a[6173];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew171 = &xnew[171];
      int_T numNonZero = 151;
      *pxnew171 = (*pA6173++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew171 += (*pA6173++) * xd[*pAidx++];
      }
    }

    xnew[171] += (guidance_simulink_P.DiscreteZeroPole_B_b[86])*rtb_Sum1[1];
    xnew[172] = (guidance_simulink_P.DiscreteZeroPole_A_a[6325])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[171];

    {
      static const int_T colAidxRow173[154] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174 };

      const int_T *pAidx = &colAidxRow173[0];
      const real32_T *pA6326 = &guidance_simulink_P.DiscreteZeroPole_A_a[6326];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew173 = &xnew[173];
      int_T numNonZero = 153;
      *pxnew173 = (*pA6326++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew173 += (*pA6326++) * xd[*pAidx++];
      }
    }

    xnew[173] += (guidance_simulink_P.DiscreteZeroPole_B_b[87])*rtb_Sum1[1];
    xnew[174] = (guidance_simulink_P.DiscreteZeroPole_A_a[6480])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[173];

    {
      static const int_T colAidxRow175[156] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176 };

      const int_T *pAidx = &colAidxRow175[0];
      const real32_T *pA6481 = &guidance_simulink_P.DiscreteZeroPole_A_a[6481];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew175 = &xnew[175];
      int_T numNonZero = 155;
      *pxnew175 = (*pA6481++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew175 += (*pA6481++) * xd[*pAidx++];
      }
    }

    xnew[175] += (guidance_simulink_P.DiscreteZeroPole_B_b[88])*rtb_Sum1[1];
    xnew[176] = (guidance_simulink_P.DiscreteZeroPole_A_a[6637])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[175];

    {
      static const int_T colAidxRow177[158] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178 };

      const int_T *pAidx = &colAidxRow177[0];
      const real32_T *pA6638 = &guidance_simulink_P.DiscreteZeroPole_A_a[6638];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew177 = &xnew[177];
      int_T numNonZero = 157;
      *pxnew177 = (*pA6638++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew177 += (*pA6638++) * xd[*pAidx++];
      }
    }

    xnew[177] += (guidance_simulink_P.DiscreteZeroPole_B_b[89])*rtb_Sum1[1];
    xnew[178] = (guidance_simulink_P.DiscreteZeroPole_A_a[6796])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[177];

    {
      static const int_T colAidxRow179[160] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180 };

      const int_T *pAidx = &colAidxRow179[0];
      const real32_T *pA6797 = &guidance_simulink_P.DiscreteZeroPole_A_a[6797];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew179 = &xnew[179];
      int_T numNonZero = 159;
      *pxnew179 = (*pA6797++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew179 += (*pA6797++) * xd[*pAidx++];
      }
    }

    xnew[179] += (guidance_simulink_P.DiscreteZeroPole_B_b[90])*rtb_Sum1[1];
    xnew[180] = (guidance_simulink_P.DiscreteZeroPole_A_a[6957])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[179];

    {
      static const int_T colAidxRow181[162] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182 };

      const int_T *pAidx = &colAidxRow181[0];
      const real32_T *pA6958 = &guidance_simulink_P.DiscreteZeroPole_A_a[6958];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew181 = &xnew[181];
      int_T numNonZero = 161;
      *pxnew181 = (*pA6958++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew181 += (*pA6958++) * xd[*pAidx++];
      }
    }

    xnew[181] += (guidance_simulink_P.DiscreteZeroPole_B_b[91])*rtb_Sum1[1];
    xnew[182] = (guidance_simulink_P.DiscreteZeroPole_A_a[7120])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[181];

    {
      static const int_T colAidxRow183[164] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184 };

      const int_T *pAidx = &colAidxRow183[0];
      const real32_T *pA7121 = &guidance_simulink_P.DiscreteZeroPole_A_a[7121];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew183 = &xnew[183];
      int_T numNonZero = 163;
      *pxnew183 = (*pA7121++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew183 += (*pA7121++) * xd[*pAidx++];
      }
    }

    xnew[183] += (guidance_simulink_P.DiscreteZeroPole_B_b[92])*rtb_Sum1[1];
    xnew[184] = (guidance_simulink_P.DiscreteZeroPole_A_a[7285])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[183];

    {
      static const int_T colAidxRow185[166] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186 };

      const int_T *pAidx = &colAidxRow185[0];
      const real32_T *pA7286 = &guidance_simulink_P.DiscreteZeroPole_A_a[7286];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew185 = &xnew[185];
      int_T numNonZero = 165;
      *pxnew185 = (*pA7286++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew185 += (*pA7286++) * xd[*pAidx++];
      }
    }

    xnew[185] += (guidance_simulink_P.DiscreteZeroPole_B_b[93])*rtb_Sum1[1];
    xnew[186] = (guidance_simulink_P.DiscreteZeroPole_A_a[7452])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[185];

    {
      static const int_T colAidxRow187[168] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188 };

      const int_T *pAidx = &colAidxRow187[0];
      const real32_T *pA7453 = &guidance_simulink_P.DiscreteZeroPole_A_a[7453];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew187 = &xnew[187];
      int_T numNonZero = 167;
      *pxnew187 = (*pA7453++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew187 += (*pA7453++) * xd[*pAidx++];
      }
    }

    xnew[187] += (guidance_simulink_P.DiscreteZeroPole_B_b[94])*rtb_Sum1[1];
    xnew[188] = (guidance_simulink_P.DiscreteZeroPole_A_a[7621])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[187];

    {
      static const int_T colAidxRow189[170] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190 };

      const int_T *pAidx = &colAidxRow189[0];
      const real32_T *pA7622 = &guidance_simulink_P.DiscreteZeroPole_A_a[7622];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew189 = &xnew[189];
      int_T numNonZero = 169;
      *pxnew189 = (*pA7622++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew189 += (*pA7622++) * xd[*pAidx++];
      }
    }

    xnew[189] += (guidance_simulink_P.DiscreteZeroPole_B_b[95])*rtb_Sum1[1];
    xnew[190] = (guidance_simulink_P.DiscreteZeroPole_A_a[7792])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[189];

    {
      static const int_T colAidxRow191[172] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192 };

      const int_T *pAidx = &colAidxRow191[0];
      const real32_T *pA7793 = &guidance_simulink_P.DiscreteZeroPole_A_a[7793];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew191 = &xnew[191];
      int_T numNonZero = 171;
      *pxnew191 = (*pA7793++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew191 += (*pA7793++) * xd[*pAidx++];
      }
    }

    xnew[191] += (guidance_simulink_P.DiscreteZeroPole_B_b[96])*rtb_Sum1[1];
    xnew[192] = (guidance_simulink_P.DiscreteZeroPole_A_a[7965])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[191];

    {
      static const int_T colAidxRow193[174] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194 };

      const int_T *pAidx = &colAidxRow193[0];
      const real32_T *pA7966 = &guidance_simulink_P.DiscreteZeroPole_A_a[7966];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew193 = &xnew[193];
      int_T numNonZero = 173;
      *pxnew193 = (*pA7966++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew193 += (*pA7966++) * xd[*pAidx++];
      }
    }

    xnew[193] += (guidance_simulink_P.DiscreteZeroPole_B_b[97])*rtb_Sum1[1];
    xnew[194] = (guidance_simulink_P.DiscreteZeroPole_A_a[8140])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[193];

    {
      static const int_T colAidxRow195[176] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196 };

      const int_T *pAidx = &colAidxRow195[0];
      const real32_T *pA8141 = &guidance_simulink_P.DiscreteZeroPole_A_a[8141];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew195 = &xnew[195];
      int_T numNonZero = 175;
      *pxnew195 = (*pA8141++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew195 += (*pA8141++) * xd[*pAidx++];
      }
    }

    xnew[195] += (guidance_simulink_P.DiscreteZeroPole_B_b[98])*rtb_Sum1[1];
    xnew[196] = (guidance_simulink_P.DiscreteZeroPole_A_a[8317])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[195];

    {
      static const int_T colAidxRow197[178] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198 };

      const int_T *pAidx = &colAidxRow197[0];
      const real32_T *pA8318 = &guidance_simulink_P.DiscreteZeroPole_A_a[8318];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew197 = &xnew[197];
      int_T numNonZero = 177;
      *pxnew197 = (*pA8318++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew197 += (*pA8318++) * xd[*pAidx++];
      }
    }

    xnew[197] += (guidance_simulink_P.DiscreteZeroPole_B_b[99])*rtb_Sum1[1];
    xnew[198] = (guidance_simulink_P.DiscreteZeroPole_A_a[8496])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[197];

    {
      static const int_T colAidxRow199[180] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200 };

      const int_T *pAidx = &colAidxRow199[0];
      const real32_T *pA8497 = &guidance_simulink_P.DiscreteZeroPole_A_a[8497];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew199 = &xnew[199];
      int_T numNonZero = 179;
      *pxnew199 = (*pA8497++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew199 += (*pA8497++) * xd[*pAidx++];
      }
    }

    xnew[199] += (guidance_simulink_P.DiscreteZeroPole_B_b[100])*rtb_Sum1[1];
    xnew[200] = (guidance_simulink_P.DiscreteZeroPole_A_a[8677])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[199];

    {
      static const int_T colAidxRow201[182] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202 };

      const int_T *pAidx = &colAidxRow201[0];
      const real32_T *pA8678 = &guidance_simulink_P.DiscreteZeroPole_A_a[8678];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew201 = &xnew[201];
      int_T numNonZero = 181;
      *pxnew201 = (*pA8678++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew201 += (*pA8678++) * xd[*pAidx++];
      }
    }

    xnew[201] += (guidance_simulink_P.DiscreteZeroPole_B_b[101])*rtb_Sum1[1];
    xnew[202] = (guidance_simulink_P.DiscreteZeroPole_A_a[8860])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[201];

    {
      static const int_T colAidxRow203[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow203[0];
      const real32_T *pA8861 = &guidance_simulink_P.DiscreteZeroPole_A_a[8861];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew203 = &xnew[203];
      int_T numNonZero = 183;
      *pxnew203 = (*pA8861++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew203 += (*pA8861++) * xd[*pAidx++];
      }
    }

    xnew[203] += (guidance_simulink_P.DiscreteZeroPole_B_b[102])*rtb_Sum1[1];
    xnew[204] = (guidance_simulink_P.DiscreteZeroPole_A_a[9045])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[203];

    {
      static const int_T colAidxRow205[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow205[0];
      const real32_T *pA9046 = &guidance_simulink_P.DiscreteZeroPole_A_a[9046];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew205 = &xnew[205];
      int_T numNonZero = 183;
      *pxnew205 = (*pA9046++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew205 += (*pA9046++) * xd[*pAidx++];
      }
    }

    xnew[205] += (guidance_simulink_P.DiscreteZeroPole_B_b[103])*rtb_Sum1[1];
    xnew[206] = (guidance_simulink_P.DiscreteZeroPole_A_a[9230])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[205];

    {
      static const int_T colAidxRow207[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow207[0];
      const real32_T *pA9231 = &guidance_simulink_P.DiscreteZeroPole_A_a[9231];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew207 = &xnew[207];
      int_T numNonZero = 183;
      *pxnew207 = (*pA9231++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew207 += (*pA9231++) * xd[*pAidx++];
      }
    }

    xnew[207] += (guidance_simulink_P.DiscreteZeroPole_B_b[104])*rtb_Sum1[1];
    xnew[208] = (guidance_simulink_P.DiscreteZeroPole_A_a[9415])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[207];

    {
      static const int_T colAidxRow209[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow209[0];
      const real32_T *pA9416 = &guidance_simulink_P.DiscreteZeroPole_A_a[9416];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew209 = &xnew[209];
      int_T numNonZero = 183;
      *pxnew209 = (*pA9416++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew209 += (*pA9416++) * xd[*pAidx++];
      }
    }

    xnew[209] += (guidance_simulink_P.DiscreteZeroPole_B_b[105])*rtb_Sum1[1];
    xnew[210] = (guidance_simulink_P.DiscreteZeroPole_A_a[9600])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[209];

    {
      static const int_T colAidxRow211[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow211[0];
      const real32_T *pA9601 = &guidance_simulink_P.DiscreteZeroPole_A_a[9601];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew211 = &xnew[211];
      int_T numNonZero = 183;
      *pxnew211 = (*pA9601++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew211 += (*pA9601++) * xd[*pAidx++];
      }
    }

    xnew[211] += (guidance_simulink_P.DiscreteZeroPole_B_b[106])*rtb_Sum1[1];
    xnew[212] = (guidance_simulink_P.DiscreteZeroPole_A_a[9785])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[211];

    {
      static const int_T colAidxRow213[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow213[0];
      const real32_T *pA9786 = &guidance_simulink_P.DiscreteZeroPole_A_a[9786];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew213 = &xnew[213];
      int_T numNonZero = 183;
      *pxnew213 = (*pA9786++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew213 += (*pA9786++) * xd[*pAidx++];
      }
    }

    xnew[213] += (guidance_simulink_P.DiscreteZeroPole_B_b[107])*rtb_Sum1[1];
    xnew[214] = (guidance_simulink_P.DiscreteZeroPole_A_a[9970])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[213];

    {
      static const int_T colAidxRow215[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow215[0];
      const real32_T *pA9971 = &guidance_simulink_P.DiscreteZeroPole_A_a[9971];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew215 = &xnew[215];
      int_T numNonZero = 183;
      *pxnew215 = (*pA9971++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew215 += (*pA9971++) * xd[*pAidx++];
      }
    }

    xnew[215] += (guidance_simulink_P.DiscreteZeroPole_B_b[108])*rtb_Sum1[1];
    xnew[216] = (guidance_simulink_P.DiscreteZeroPole_A_a[10155])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[215];

    {
      static const int_T colAidxRow217[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow217[0];
      const real32_T *pA10156 = &guidance_simulink_P.DiscreteZeroPole_A_a[10156];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew217 = &xnew[217];
      int_T numNonZero = 183;
      *pxnew217 = (*pA10156++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew217 += (*pA10156++) * xd[*pAidx++];
      }
    }

    xnew[217] += (guidance_simulink_P.DiscreteZeroPole_B_b[109])*rtb_Sum1[1];
    xnew[218] = (guidance_simulink_P.DiscreteZeroPole_A_a[10340])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[217];

    {
      static const int_T colAidxRow219[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow219[0];
      const real32_T *pA10341 = &guidance_simulink_P.DiscreteZeroPole_A_a[10341];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew219 = &xnew[219];
      int_T numNonZero = 183;
      *pxnew219 = (*pA10341++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew219 += (*pA10341++) * xd[*pAidx++];
      }
    }

    xnew[219] += (guidance_simulink_P.DiscreteZeroPole_B_b[110])*rtb_Sum1[1];
    xnew[220] = (guidance_simulink_P.DiscreteZeroPole_A_a[10525])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[219];

    {
      static const int_T colAidxRow221[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow221[0];
      const real32_T *pA10526 = &guidance_simulink_P.DiscreteZeroPole_A_a[10526];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew221 = &xnew[221];
      int_T numNonZero = 183;
      *pxnew221 = (*pA10526++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew221 += (*pA10526++) * xd[*pAidx++];
      }
    }

    xnew[221] += (guidance_simulink_P.DiscreteZeroPole_B_b[111])*rtb_Sum1[1];
    xnew[222] = (guidance_simulink_P.DiscreteZeroPole_A_a[10710])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[221];

    {
      static const int_T colAidxRow223[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow223[0];
      const real32_T *pA10711 = &guidance_simulink_P.DiscreteZeroPole_A_a[10711];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew223 = &xnew[223];
      int_T numNonZero = 183;
      *pxnew223 = (*pA10711++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew223 += (*pA10711++) * xd[*pAidx++];
      }
    }

    xnew[223] += (guidance_simulink_P.DiscreteZeroPole_B_b[112])*rtb_Sum1[1];
    xnew[224] = (guidance_simulink_P.DiscreteZeroPole_A_a[10895])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[223];

    {
      static const int_T colAidxRow225[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow225[0];
      const real32_T *pA10896 = &guidance_simulink_P.DiscreteZeroPole_A_a[10896];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew225 = &xnew[225];
      int_T numNonZero = 183;
      *pxnew225 = (*pA10896++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew225 += (*pA10896++) * xd[*pAidx++];
      }
    }

    xnew[225] += (guidance_simulink_P.DiscreteZeroPole_B_b[113])*rtb_Sum1[1];
    xnew[226] = (guidance_simulink_P.DiscreteZeroPole_A_a[11080])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[225];

    {
      static const int_T colAidxRow227[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow227[0];
      const real32_T *pA11081 = &guidance_simulink_P.DiscreteZeroPole_A_a[11081];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew227 = &xnew[227];
      int_T numNonZero = 183;
      *pxnew227 = (*pA11081++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew227 += (*pA11081++) * xd[*pAidx++];
      }
    }

    xnew[227] += (guidance_simulink_P.DiscreteZeroPole_B_b[114])*rtb_Sum1[1];
    xnew[228] = (guidance_simulink_P.DiscreteZeroPole_A_a[11265])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[227];

    {
      static const int_T colAidxRow229[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow229[0];
      const real32_T *pA11266 = &guidance_simulink_P.DiscreteZeroPole_A_a[11266];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew229 = &xnew[229];
      int_T numNonZero = 183;
      *pxnew229 = (*pA11266++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew229 += (*pA11266++) * xd[*pAidx++];
      }
    }

    xnew[229] += (guidance_simulink_P.DiscreteZeroPole_B_b[115])*rtb_Sum1[1];
    xnew[230] = (guidance_simulink_P.DiscreteZeroPole_A_a[11450])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[229];

    {
      static const int_T colAidxRow231[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow231[0];
      const real32_T *pA11451 = &guidance_simulink_P.DiscreteZeroPole_A_a[11451];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew231 = &xnew[231];
      int_T numNonZero = 183;
      *pxnew231 = (*pA11451++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew231 += (*pA11451++) * xd[*pAidx++];
      }
    }

    xnew[231] += (guidance_simulink_P.DiscreteZeroPole_B_b[116])*rtb_Sum1[1];
    xnew[232] = (guidance_simulink_P.DiscreteZeroPole_A_a[11635])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[231];

    {
      static const int_T colAidxRow233[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow233[0];
      const real32_T *pA11636 = &guidance_simulink_P.DiscreteZeroPole_A_a[11636];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew233 = &xnew[233];
      int_T numNonZero = 183;
      *pxnew233 = (*pA11636++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew233 += (*pA11636++) * xd[*pAidx++];
      }
    }

    xnew[233] += (guidance_simulink_P.DiscreteZeroPole_B_b[117])*rtb_Sum1[1];
    xnew[234] = (guidance_simulink_P.DiscreteZeroPole_A_a[11820])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[233];

    {
      static const int_T colAidxRow235[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow235[0];
      const real32_T *pA11821 = &guidance_simulink_P.DiscreteZeroPole_A_a[11821];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew235 = &xnew[235];
      int_T numNonZero = 183;
      *pxnew235 = (*pA11821++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew235 += (*pA11821++) * xd[*pAidx++];
      }
    }

    xnew[235] += (guidance_simulink_P.DiscreteZeroPole_B_b[118])*rtb_Sum1[1];
    xnew[236] = (guidance_simulink_P.DiscreteZeroPole_A_a[12005])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[235];

    {
      static const int_T colAidxRow237[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow237[0];
      const real32_T *pA12006 = &guidance_simulink_P.DiscreteZeroPole_A_a[12006];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew237 = &xnew[237];
      int_T numNonZero = 183;
      *pxnew237 = (*pA12006++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew237 += (*pA12006++) * xd[*pAidx++];
      }
    }

    xnew[237] += (guidance_simulink_P.DiscreteZeroPole_B_b[119])*rtb_Sum1[1];
    xnew[238] = (guidance_simulink_P.DiscreteZeroPole_A_a[12190])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[237];

    {
      static const int_T colAidxRow239[184] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204 };

      const int_T *pAidx = &colAidxRow239[0];
      const real32_T *pA12191 = &guidance_simulink_P.DiscreteZeroPole_A_a[12191];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew239 = &xnew[239];
      int_T numNonZero = 183;
      *pxnew239 = (*pA12191++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew239 += (*pA12191++) * xd[*pAidx++];
      }
    }

    xnew[239] += (guidance_simulink_P.DiscreteZeroPole_B_b[120])*rtb_Sum1[1];
    xnew[240] = (guidance_simulink_P.DiscreteZeroPole_A_a[12375])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[239];

    {
      static const int_T colAidxRow241[186] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241 };

      const int_T *pAidx = &colAidxRow241[0];
      const real32_T *pA12376 = &guidance_simulink_P.DiscreteZeroPole_A_a[12376];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew241 = &xnew[241];
      int_T numNonZero = 185;
      *pxnew241 = (*pA12376++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew241 += (*pA12376++) * xd[*pAidx++];
      }
    }

    xnew[241] += (guidance_simulink_P.DiscreteZeroPole_B_b[121])*rtb_Sum1[1];
    xnew[242] = (guidance_simulink_P.DiscreteZeroPole_A_a[12562])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[241];

    {
      static const int_T colAidxRow243[189] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244 };

      const int_T *pAidx = &colAidxRow243[0];
      const real32_T *pA12563 = &guidance_simulink_P.DiscreteZeroPole_A_a[12563];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew243 = &xnew[243];
      int_T numNonZero = 188;
      *pxnew243 = (*pA12563++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew243 += (*pA12563++) * xd[*pAidx++];
      }
    }

    xnew[243] += (guidance_simulink_P.DiscreteZeroPole_B_b[122])*rtb_Sum1[1];
    xnew[244] = (guidance_simulink_P.DiscreteZeroPole_A_a[12752])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[243];

    {
      static const int_T colAidxRow245[191] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246 };

      const int_T *pAidx = &colAidxRow245[0];
      const real32_T *pA12753 = &guidance_simulink_P.DiscreteZeroPole_A_a[12753];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew245 = &xnew[245];
      int_T numNonZero = 190;
      *pxnew245 = (*pA12753++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew245 += (*pA12753++) * xd[*pAidx++];
      }
    }

    xnew[245] += (guidance_simulink_P.DiscreteZeroPole_B_b[123])*rtb_Sum1[1];
    xnew[246] = (guidance_simulink_P.DiscreteZeroPole_A_a[12944])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[245];

    {
      static const int_T colAidxRow247[193] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248 };

      const int_T *pAidx = &colAidxRow247[0];
      const real32_T *pA12945 = &guidance_simulink_P.DiscreteZeroPole_A_a[12945];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew247 = &xnew[247];
      int_T numNonZero = 192;
      *pxnew247 = (*pA12945++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew247 += (*pA12945++) * xd[*pAidx++];
      }
    }

    xnew[247] += (guidance_simulink_P.DiscreteZeroPole_B_b[124])*rtb_Sum1[1];
    xnew[248] = (guidance_simulink_P.DiscreteZeroPole_A_a[13138])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[247];

    {
      static const int_T colAidxRow249[195] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 38, 59, 60, 61, 62, 63, 64, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
        159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
        201, 202, 203, 204, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249,
        250 };

      const int_T *pAidx = &colAidxRow249[0];
      const real32_T *pA13139 = &guidance_simulink_P.DiscreteZeroPole_A_a[13139];
      const real32_T *xd = &guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0];
      real32_T *pxnew249 = &xnew[249];
      int_T numNonZero = 194;
      *pxnew249 = (*pA13139++) * xd[*pAidx++];
      while (numNonZero--) {
        *pxnew249 += (*pA13139++) * xd[*pAidx++];
      }
    }

    xnew[249] += (guidance_simulink_P.DiscreteZeroPole_B_b[125])*rtb_Sum1[1];
    xnew[250] = (guidance_simulink_P.DiscreteZeroPole_A_a[13334])*
      guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[249];
    (void) memcpy(&guidance_simulink_DW.DiscreteZeroPole_DSTATE_b[0], xnew,
                  sizeof(real32_T)*251);
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
