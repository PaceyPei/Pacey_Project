/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
#define CKTIM_APB1 64000000
#define CKTIM_APB2 64000000
#define PWM_ALIGN_FACTOR 1
#define PWM_PRSC 0
#define PWM_CNT_FREQ (CKTIM_APB2 / PWM_ALIGN_FACTOR / (PWM_PRSC + 1))
#define PWM_FREQ 20000
#define PWM_PERIOD (PWM_CNT_FREQ / PWM_FREQ)
#define ENCODER_PERIOD 4096

#define WALL_DIST_Pin GPIO_PIN_0
#define WALL_DIST_GPIO_Port GPIOC
#define VBAT_ADC_Pin GPIO_PIN_1
#define VBAT_ADC_GPIO_Port GPIOC
#define MID_BROOM_I_Pin GPIO_PIN_0
#define MID_BROOM_I_GPIO_Port GPIOA
#define FAN_I_Pin GPIO_PIN_1
#define FAN_I_GPIO_Port GPIOA
#define SIDE_BROOM_I_Pin GPIO_PIN_2
#define SIDE_BROOM_I_GPIO_Port GPIOA
#define GROUND_R_Pin GPIO_PIN_3
#define GROUND_R_GPIO_Port GPIOA
#define GROUND_L_Pin GPIO_PIN_4
#define GROUND_L_GPIO_Port GPIOA
#define GROUND_M_Pin GPIO_PIN_5
#define GROUND_M_GPIO_Port GPIOA
#define L_WHEEL_I_Pin GPIO_PIN_0
#define L_WHEEL_I_GPIO_Port GPIOB
#define R_WHEEL_I_Pin GPIO_PIN_1
#define R_WHEEL_I_GPIO_Port GPIOB
#define GROUND_PWR_Pin GPIO_PIN_8
#define GROUND_PWR_GPIO_Port GPIOA
#define CHARGE_OK_Pin GPIO_PIN_11
#define CHARGE_OK_GPIO_Port GPIOA
#define MCU_PWR_Pin GPIO_PIN_12
#define MCU_PWR_GPIO_Port GPIOA
#define GARBAGE_PWR_Pin GPIO_PIN_4
#define GARBAGE_PWR_GPIO_Port GPIOB
#define TOP_PWR_Pin GPIO_PIN_5
#define TOP_PWR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
