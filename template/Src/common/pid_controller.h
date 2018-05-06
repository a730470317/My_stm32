#ifndef __PID_CONTROL_H__
#define __PID_CONTROL_H__
#define MAX_POS_INTEGRAL_TIME 200
#define PID_SPEED_SAMPLE_TIME 100

#define MAX_SPEED_INTEGRAL_TIME 20

#include "math.h"
#ifdef STM32H743xx
#include "stm32h7xx.h"
#endif
//#include "stm32f4xx.h"

#define PID_MAX_PWM_OUTPUT 990
#define PID_MAX_TARGET_SPEED 20
#define PID_SPEED_SAMPLE_TIME 10 
#define PID_ACCELERATE_SAMPLE_TIME 10

// outPut =  Kp(1*Err_now + Td * (Err_now[20] - 2*Err_[20-1] + Err_[18] ) + Ti*Inter )
typedef struct 
{
	double m_pos_p;
	double m_pos_d;
  double m_pos_i;

  double m_speed_p;
  double m_speed_d;
  double m_speed_i;

  // Speed
  float   m_target_speed;
  float	  m_current_speed;
  float   m_speed_delta;
  float   m_speed_err_integral_val;
  int     m_speed_intergral_time;
  float   m_speed_err_vec[MAX_SPEED_INTEGRAL_TIME];
  
  // POS:
	long 		m_target_pos;
	long 		m_current_pos;
	long 		m_output;
	long 		m_pos_err_integral_val;
  int  		m_pos_intergral_time;
  long 		m_pos_err_vec[MAX_POS_INTEGRAL_TIME];
  
  //
	int  		m_accelerate;
	char 		m_motor_enable;
  // Control bit
  int  		m_enable_PID_control;
  int	 		m_paulse_per_cir ;
  int     m_ctrl_max_pwm;
  float   m_ctrl_max_spd;


	__IO uint32_t * m_pwm_output;
	__IO uint32_t * m_timer_cnt;
#ifdef STM32H743xx
  TIM_TypeDef * m_pwm_output_timer;
#endif
}PID_controller;

void set_pos_pid_parameter(PID_controller *pid, double pos_p, double pos_d, double pos_i);
void set_spd_pid_parameter(PID_controller *pid, double spd_p, double spd_d, double spd_i);

void init_pid_parameter(PID_controller * pid, double pos_p, double pos_d, double pos_i,
  double spd_p, double spd_d, double spd_i,
  int intergral_time);

int 	pid_compute(PID_controller* pid);

#endif 
