#include "pid_controller.h"
#include "numeric_alg.h"
#include "math.h"

//PID control period = 1/(5KHz*2) = 100us
void set_pos_pid_parameter(PID_controller *pid, double pos_p, double pos_d, double pos_i)
{
  pid->m_pos_p = pos_p;
  pid->m_pos_d = pos_d;
  pid->m_pos_i = pos_i;
}

void set_spd_pid_parameter(PID_controller *pid, double spd_p, double spd_d, double spd_i)
{
  pid->m_speed_p = spd_p;
  pid->m_speed_d = spd_d;
  pid->m_speed_i = spd_i;
}

void init_pid_parameter(PID_controller * pid, double pos_p, double pos_d, double pos_i, 
  double spd_p, double spd_d, double spd_i,
  int intergral_time)
{
	int i = 0;
  set_pos_pid_parameter(pid,pos_p, pos_i, pos_d);
  set_spd_pid_parameter(pid,spd_p, spd_i, spd_d);

	pid->m_ctrl_max_spd = 20;
	pid->m_pos_err_integral_val = 0;
  pid->m_speed_intergral_time = 10;
	
  pid->m_ctrl_max_pwm = PID_MAX_PWM_OUTPUT;
  pid->m_ctrl_max_spd = PID_MAX_TARGET_SPEED;


  if (intergral_time > PID_SPEED_SAMPLE_TIME)
  {
    pid->m_pos_intergral_time = intergral_time;
  }
  else
  {
    pid->m_pos_intergral_time = PID_SPEED_SAMPLE_TIME;
  }
	for (i = pid->m_pos_intergral_time - 1; i >= 0; i--)
	{
		pid->m_pos_err_vec[i] = 0;
	}
}

int pid_compute(PID_controller* pid)
{
	int out_put;
	int i = 0;
	pid->m_current_speed = -(pid->m_pos_err_vec[0] - pid->m_pos_err_vec[PID_SPEED_SAMPLE_TIME-1]);  //Since it is computed from errs,so it should be minus at last.

	/****************Position circuit****************/
	//Refresh buffer
  pid->m_pos_err_integral_val = 0;
	for (i = pid->m_pos_intergral_time-1; i >=1; i--)
	{
		pid->m_pos_err_vec[i] = pid->m_pos_err_vec[i - 1];
    pid->m_pos_err_integral_val += pid->m_pos_err_vec[i];
	}
	
	pid->m_pos_err_vec[0] = pid->m_target_pos - pid->m_current_pos;
	pid->m_pos_err_integral_val += pid->m_pos_err_vec[0];

	pid->m_target_speed = pid->m_pos_p*(pid->m_pos_err_vec[0] +
		pid->m_pos_d*pid->m_current_speed +
		pid->m_pos_i*(pid->m_pos_err_integral_val));

	//Limit the output speed
  //pid->m_target_speed = alg_limit(pid->m_target_speed, pid->m_max_taget_speed, -pid->m_max_taget_speed );
	pid->m_target_speed = alg_limit_abs(pid->m_target_speed, pid->m_ctrl_max_spd );

	if (pid->m_target_speed >= pid->m_ctrl_max_spd)
	{
		pid->m_target_speed = pid->m_ctrl_max_spd;
	}
	else if (pid->m_target_speed <= -pid->m_ctrl_max_spd)
	{
		pid->m_target_speed = -pid->m_ctrl_max_spd;
	}

	/****************Speed circuit****************/
  //Refresh speed buffer
  pid->m_speed_err_integral_val = 0;
	for (i = pid->m_speed_intergral_time - 1; i >= 1; i--)
	{
		pid->m_speed_err_vec[i] = pid->m_speed_err_vec[i - 1];
    pid->m_speed_err_integral_val += pid->m_speed_err_vec[i];
	}
	pid->m_speed_err_vec[0] = pid->m_target_speed - pid->m_current_speed;
	pid->m_speed_err_integral_val += pid->m_speed_err_vec[0];

	pid->m_accelerate = -(pid->m_speed_err_vec[0] - pid->m_speed_err_vec[PID_ACCELERATE_SAMPLE_TIME-1]);  //Since it is computed from errs,so it should be minus at last.

	pid->m_speed_delta = pid->m_speed_p*(pid->m_speed_err_vec[0] +
		pid->m_speed_d*pid->m_accelerate +
		pid->m_speed_i*(pid->m_speed_err_integral_val));

	pid->m_output += pid->m_speed_delta;

  //pid->m_output = alg_limit(pid->m_output, pid->m_ctrl_max_pwm, -pid->m_ctrl_max_pwm);
  pid->m_output = alg_limit_abs(pid->m_output, pid->m_ctrl_max_pwm);
	if( abs(pid->m_pos_err_vec[0]) <= 2)
		pid->m_output *= 0.5;
	else if(( abs(pid->m_pos_err_vec[0]) <= 4))
		pid->m_output = alg_limit_abs(pid->m_output, (pid->m_ctrl_max_pwm*0.5) );
	out_put = fabs((int)(pid->m_output));
	return out_put;
}


