#ifndef __COMM_H__
#define __COMM_H__




#include "stm32f1xx_hal.h"
#include "generic_config.h"
#include "bsp_usart.h"

extern BspUsartType CommUsart;


bool AppComm_Init(UART_HandleTypeDef *huart);
void send_test(void);





#endif
