#ifndef  __BOARD_IO_H__
#define __BOARD_IO_H__
#define  WITH_OLED
#include <stdio.h>
#include "stm32h7xx_hal.h"
#include "common/serial_protocal.h"
#include "common/pid_controller.h"

#ifdef WITH_OLED 
#include "oled/oled.h"
#endif
//Setting printf via usart1

#define USART_RX_SIZE 1024
#define ENCODE_DEFAULT_BIAS (0x7fff)
#define ENCODER_CNT_RESET TIM8->CNT = ENCODE_DEFAULT_BIAS;
#define ENCODER_INCREMENTAL (TIM8->CNT - ENCODE_DEFAULT_BIAS);

#define BLUE_LED_ON   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
#define BLUE_LED_OFF  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
// This is added LED
#define GREEN_LED_ON  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
#define GREEN_LED_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);

#define RED_LED_ON  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);
#define RED_LED_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET);


// IO definition
// Adc encoder:     PA6
// Opti_Eletronic:  PC6 PC7
// PWM_output:      PE5 PE6
// USART:           PB14(RX) PB15(TX)
/* OLED==================
      D0   接PG10（SCL）
      D1   接PG12（SDA）
      RES  接PG13
      DC   接PG11
      CS   接PD9   
*/
#endif