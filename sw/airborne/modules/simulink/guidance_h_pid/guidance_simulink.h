/*
 * File: guidance_simulink.h
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 22:19:01 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_guidance_simulink_h_
#define RTW_HEADER_guidance_simulink_h_
#ifndef guidance_simulink_COMMON_INCLUDES_
# define guidance_simulink_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* guidance_simulink_COMMON_INCLUDES_ */

#include "guidance_simulink_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTimeIntegrator_DSTATE[2];/* '<Root>/Discrete-Time Integrator' */
} DW_guidance_simulink_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T positionNed_i[2];           /* '<Root>/positionNed_i' */
  real32_T speedNed_i[2];              /* '<Root>/speedNed_i' */
  real32_T ref_speed[2];               /* '<Root>/ref_speed' */
  boolean_T is_in_flight;              /* '<Root>/is_in_flight' */
  real32_T ref_accel[2];               /* '<Root>/ref_accel' */
  real32_T ref_pos[2];                 /* '<Root>/ref_pos' */
} ExtU_guidance_simulink_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T guidance_h_cmd_earth[2];    /* '<Root>/guidance_h_cmd_earth' */
  real32_T guidance_h_trim_att_integrator_[2];/* '<Root>/guidance_h_trim_att_integrator_f' */
  real32_T pos_err_f[2];               /* '<Root>/pos_err_f' */
  real32_T speed_err_f[2];             /* '<Root>/speed_err_f' */
} ExtY_guidance_simulink_T;

/* Parameters (auto storage) */
struct P_guidance_simulink_T_ {
  real32_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                           * Referenced by: '<Root>/Discrete-Time Integrator'
                                           */
  real32_T DiscreteTimeIntegrator_IC;  /* Computed Parameter: DiscreteTimeIntegrator_IC
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  real32_T I_Gain;                     /* Computed Parameter: I_Gain
                                        * Referenced by: '<Root>/I'
                                        */
  real32_T MAX_INTEGRATOR_UpperSat;    /* Computed Parameter: MAX_INTEGRATOR_UpperSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  real32_T MAX_INTEGRATOR_LowerSat;    /* Computed Parameter: MAX_INTEGRATOR_LowerSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  real32_T scale6_Gain;                /* Computed Parameter: scale6_Gain
                                        * Referenced by: '<Root>/scale6'
                                        */
  real32_T A_Gain;                     /* Computed Parameter: A_Gain
                                        * Referenced by: '<Root>/A'
                                        */
  real32_T scale5_Gain;                /* Computed Parameter: scale5_Gain
                                        * Referenced by: '<Root>/scale5'
                                        */
  real32_T MAX_POS_ERR_UpperSat;       /* Computed Parameter: MAX_POS_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  real32_T MAX_POS_ERR_LowerSat;       /* Computed Parameter: MAX_POS_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  real32_T P_Gain;                     /* Computed Parameter: P_Gain
                                        * Referenced by: '<Root>/P'
                                        */
  real32_T scale1_Gain;                /* Computed Parameter: scale1_Gain
                                        * Referenced by: '<Root>/scale1'
                                        */
  real32_T MAX_SPEED_ERR_UpperSat;     /* Computed Parameter: MAX_SPEED_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  real32_T MAX_SPEED_ERR_LowerSat;     /* Computed Parameter: MAX_SPEED_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  real32_T D_Gain;                     /* Computed Parameter: D_Gain
                                        * Referenced by: '<Root>/D'
                                        */
  real32_T scale2_Gain;                /* Computed Parameter: scale2_Gain
                                        * Referenced by: '<Root>/scale2'
                                        */
  real32_T scale3_Gain;                /* Computed Parameter: scale3_Gain
                                        * Referenced by: '<Root>/scale3'
                                        */
  real32_T V_Gain;                     /* Computed Parameter: V_Gain
                                        * Referenced by: '<Root>/V'
                                        */
  real32_T scale4_Gain;                /* Computed Parameter: scale4_Gain
                                        * Referenced by: '<Root>/scale4'
                                        */
  real32_T TRAJ_MAX_BANK_UpperSat;     /* Computed Parameter: TRAJ_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  real32_T TRAJ_MAX_BANK_LowerSat;     /* Computed Parameter: TRAJ_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  real32_T TOTAL_MAX_BANK_UpperSat;    /* Computed Parameter: TOTAL_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
  real32_T TOTAL_MAX_BANK_LowerSat;    /* Computed Parameter: TOTAL_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
  int32_T Constant_Value[2];           /* Computed Parameter: Constant_Value
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_guidance_simulink_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_guidance_simulink_T guidance_simulink_P;

/* Block states (auto storage) */
extern DW_guidance_simulink_T guidance_simulink_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_guidance_simulink_T guidance_simulink_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_guidance_simulink_T guidance_simulink_Y;

/* Model entry point functions */
extern void guidance_simulink_initialize(void);
extern void guidance_simulink_step(void);
extern void guidance_simulink_terminate(void);

/* Real-time Model object */
extern RT_MODEL_guidance_simulink_T *const guidance_simulink_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'guidance_simulink'
 */
#endif                                 /* RTW_HEADER_guidance_simulink_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
