#include "comm.h"


#define UART_BUFF_SIZE  128

BspUsartType CommUsart;
static u8 UartBuffer[UART_BUFF_SIZE] = {"ddddddddddddddddddddddd\n"};

bool AppComm_Init(UART_HandleTypeDef *huart)
{
	
	CommUsart.buffer_size = UART_BUFF_SIZE;
	CommUsart.dma_rx_buffer = UartBuffer;
	
	BspUsart_Init(&CommUsart,huart);

	return TRUE;
}

void send_test(void)
{
	UserUsart_SendData(&CommUsart, (u8 *)UartBuffer, sizeof(UartBuffer));
	HAL_Delay(500);
}

//UserUsart_SendData(&CommUsart, (uint8_t *)aTxBuffer, sizeof(aTxBuffer));


