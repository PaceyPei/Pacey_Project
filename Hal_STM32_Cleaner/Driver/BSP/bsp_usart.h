#ifndef __BSP_USART__
#define __BSP_USART__

#include "generic_config.h"
#include "usart.h"


typedef struct{
	UART_HandleTypeDef *huart;		//Usart hal layer handle. have real handle in later.
	u32 tx_tc_flag;					//flag bit.
	u8* dma_rx_buffer;				//DMA RX Buffer.
	u16 buffer_size;				//buffer unit length.
	u32 offset;						//buffer real unit be used.
}BspUsartType;

void BspUsart_Init(BspUsartType *hcomm, UART_HandleTypeDef *huart);

u8 UserUsart_SendData(BspUsartType *hcomm, const u8 *data, u16 len);
bool BspUsart_RecvData(BspUsartType *hcomm, u8 **pbuf, u32* plen);

bool BspUsart_CanSendData(BspUsartType *hcomm);

#endif



