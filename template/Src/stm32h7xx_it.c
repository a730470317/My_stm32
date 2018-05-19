/**
  ******************************************************************************
  * @file    Templates/Src/stm32h7xx_it.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    29-December-2017
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_it.h"
#include "main.h"
#include "motor_encoder/motor_encoder.h"
#include "board_io.h"
#include "common/serial_protocal.h"
#include "common/pid_controller.h"
/** @addtogroup STM32H7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

//#define TEST_REC
extern char g_usart1_tx_buffer[1024];
extern char g_usart1_rx_buffer[1024];
extern int g_usart1_rx_size;
extern TIM_HandleTypeDef htim8;
extern PID_controller pid_motor_0;
extern PID_controller pid_motor_1;
extern ADC_HandleTypeDef             AdcHandle;
int g_usart1_rx_head_bias = 0;

extern float g_adc_1_val;
float g_adc_bias = 0;
int g_bias_count = 0;
extern ALIGN_32BYTES(uint16_t   g_adc_val_raw[]);
char g_usart1_rec_char;

extern char g_printf_char[4][16];
int count_encoder = 0;
void on_get_packet(char* packet_data, int packet_id, int packet_size);
void refresh_bai_IO(float bai);
void refresh_motor_IO(PID_controller * pid);

extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim15;
extern UART_HandleTypeDef huart1;

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    HAL_IncTick();

}


/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
    /* USER CODE BEGIN TIM2_IRQn 0 */
    static int nbtime = 1;
    int t_start = HAL_GetTick();
    static char str_buffer[1024];
    int send_idx = 0;
    /* USER CODE END TIM2_IRQn 0 */
    HAL_TIM_IRQHandler(&htim2);
    /* USER CODE BEGIN TIM2_IRQn 1 */
    BLUE_LED_ON;
    if (1)
    {
#ifdef TEST_REC
        while (send_idx < g_usart1_rx_head_bias)
        {
            HAL_UART_Transmit(&huart1, (uint8_t *)&g_usart1_rx_buffer[send_idx], 1, 1);
            send_idx++;
        }
        g_usart1_rx_head_bias = 0;
#endif		
        printf("Get data cost time %f\r\n", HAL_GetTick() - t_start);
        printf("Adc interrupt, val2 = %f\r\n", g_adc_1_val);
    }
    else
    {

        //sprintf(str_buffer, "STM32CubeMX rocks %d times \r\n", ++nbtime);
        //HAL_UART_Transmit(&huart1, str_buffer, strlen(str_buffer), 1000);
        //sprintf(str_buffer, "Encoder cnt = %d \r\n", (uint32_t)(__HAL_TIM_GET_COUNTER(&htim8)));
        //HAL_UART_Transmit(&huart1, str_buffer, strlen(str_buffer), 1000);
    }
    BLUE_LED_OFF;
    //HAL_UART_Transmit(&huart1)
    /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */
    BLUE_LED_ON;
    static int current_index = 0;
    g_usart1_rec_char = (uint16_t)(USART1->RDR & (uint16_t)0x01FF);
    char packet_data[100];
    int packet_size = 0;
    int packet_id = 0;
#ifdef TEST_REC
    g_usart1_rx_buffer[g_usart1_rx_head_bias] = g_usart1_rec_char;
    g_usart1_rx_head_bias++;
    if (g_usart1_rx_head_bias > USART_RX_SIZE - 1)
        g_usart1_rx_head_bias = USART_RX_SIZE - 1;
#endif
    if (onRec(g_usart1_rec_char, g_usart1_rx_buffer, &current_index, &packet_id, &packet_size, packet_data))
    {
        current_index = 0;
        on_get_packet(packet_data, packet_id, packet_size);
    }
    if (current_index >= USART_RX_SIZE)
    {
        current_index = 0;
    }
    //return;
    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    BLUE_LED_OFF;
    /* USER CODE END USART1_IRQn 1 */
}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void)
{
    /* USER CODE BEGIN TIM7_IRQn 0 */
    GREEN_LED_ON
        HAL_TIM_IRQHandler(&htim7);
    g_adc_1_val = g_adc_val_raw[0] * 3.3f / 0xffff;
    int bias_sample_time = 2000;
    if (g_bias_count < bias_sample_time)
    {
        g_adc_bias += g_adc_1_val;
        g_bias_count++;
        GREEN_LED_OFF;
        return;
    }
    else if (g_bias_count == bias_sample_time)
    {
        g_bias_count++;
        g_adc_bias /= (float)bias_sample_time;
    }
    float angle = g_adc_1_val*360.0 / 3.3;
    angle -= (g_adc_bias*360.0 / 3.3);
    sprintf(g_printf_char[0], "a=%.2fV , e=%d", g_adc_1_val, (int)angle);
    //refresh_bai_IO(angle);
    refresh_motor_IO(&pid_motor_0);
    sprintf(g_printf_char[1], "pos= %d", pid_motor_0.m_current_pos);
    GREEN_LED_OFF
        /* USER CODE END TIM7_IRQn 1 */
}

void TIM15_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim15);
}

void EXTI9_5_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI9_5_IRQn 0 */

    /* USER CODE END EXTI9_5_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    /* USER CODE BEGIN EXTI9_5_IRQn 1 */
    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 1)
    {
        count_encoder++;
    }
    else
    {
        count_encoder--;
    }
    /* USER CODE END EXTI9_5_IRQn 1 */
}


/* USER CODE BEGIN 1 */
void on_get_packet(char* packet_data, int packet_id, int packet_size)
{
    int index;
    short temp_data;
    int i = 0;
    printf("Get packet, id = %d\n", packet_id);
    if (packet_id == 0) //For testing
    {
        printf("data = %d\n", packet_data[0]);
    }
}


//Refreshe motor's state and output
void refresh_motor_IO(PID_controller * pid)
{
    //pid->m_current_pos += (long)(*pid->m_timer_cnt - ENCODE_DEFAULT_BIAS)*360.0/pid->m_paulse_per_cir;
    //*(pid->m_timer_cnt) = ENCODE_DEFAULT_BIAS;
    pid->m_current_pos = (long)(*pid->m_timer_cnt - ENCODE_DEFAULT_BIAS)*360.0 / pid->m_paulse_per_cir;
    //if (enable_PID_control && 5 == index)
    if (pid->m_enable_PID_control)
    {
        pid_compute(pid);
    }
    if (pid->m_motor_enable == 0)
    {
        pid->m_output = 0;
    }
    if (pid->m_output > 0)
    {
        pid->m_pwm_output_timer->CCR1 = abs(pid->m_output);
        pid->m_pwm_output_timer->CCR2 = 0;
    }
    else
    {
        pid->m_pwm_output_timer->CCR2 = abs(pid->m_output);
        pid->m_pwm_output_timer->CCR1 = 0;
    }
    //*(pid->m_pwm_output) = (long)fabs((pid->m_output));
}

void refresh_bai_IO(float bai)
{
    long motor_pos = pid_motor_0.m_current_pos;
    if (abs(motor_pos) > 1800)
    {
        pid_motor_0.m_motor_enable = 0;
    }
    else
    {
        pid_motor_0.m_motor_enable = 1;
    }
    float x_abs = 1000 * sin(bai / 57.3);
    sprintf(g_printf_char[2], "%.2f,", x_abs);
    pid_motor_0.m_target_pos = (motor_pos - x_abs);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
