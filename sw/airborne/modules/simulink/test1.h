/*
 * File: test1.h
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

#ifndef RTW_HEADER_test1_h_
#define RTW_HEADER_test1_h_
#ifndef test1_COMMON_INCLUDES_
# define test1_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* test1_COMMON_INCLUDES_ */

#include "test1_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE[2];         /* '<S1>/Integrator' */
  real_T Filter_DSTATE[2];             /* '<S1>/Filter' */
} DW_test1_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T In1[2];                       /* '<Root>/In1' */
} ExtU_test1_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1[2];                      /* '<Root>/Out1' */
} ExtY_test1_T;

/* Parameters (auto storage) */
struct P_test1_T_ {
  real_T ProportionalGain_Gain;        /* Expression: P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T DerivativeGain_Gain;          /* Expression: D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T FilterCoefficient_Gain;       /* Expression: N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  real_T IntegralGain_Gain;            /* Expression: I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_test1_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_test1_T test1_P;

/* Block states (auto storage) */
extern DW_test1_T test1_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_test1_T test1_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_test1_T test1_Y;

/* Model entry point functions */
extern void test1_initialize(void);
extern void test1_step(void);

/* Real-time Model object */
extern RT_MODEL_test1_T *const test1_M;

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
 * '<Root>' : 'test1'
 * '<S1>'   : 'test1/Discrete PID Controller'
 */

/*-
 * Requirements for '<Root>': test1
 */
#endif                                 /* RTW_HEADER_test1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
