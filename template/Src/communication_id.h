#ifndef __COMMUNICATION_ID_H__
#define __COMMUNICATION_ID_H__

#define  STM32_MCU_STATE_REPORT 0x10
#define  STM32_MCU_SET_PWM 0x11
typedef struct _MCU_STATE
{
    float m_adc_encoder_val;
    float m_pendulum_pos;
    float m_motor_pos;
}MCU_STATE;

typedef struct _Motor_control
{
    int if_manaul;
    int pwm_val[2];
}Motor_control;

#endif