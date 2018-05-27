#ifndef __COMMUNICATION_ID_H__
#define __COMMUNICATION_ID_H__

#define  STM32_MCU_STATE_REPORT 0x10
typedef struct _MCU_STATE
{
    float m_adc_encoder;
    float m_motor_pos;
}MCU_STATE
;
#endif