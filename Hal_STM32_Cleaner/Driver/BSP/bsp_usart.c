#include "bsp_usart.h"


/*
*@brief		:communication usart init.
*@param hcomm:handle.
*@param huart:usart handle.
*@return 	:none.
*/
void BspUsart_Init(BspUsartType *hcomm, UART_HandleTypeDef *huart)
{
	hcomm->huart = huart;						//aim   ???
	hcomm->tx_tc_flag = __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmatx);		//Returns the current DMA Channel transfer complete flag. eg: DMA_FLAG_TC1 -> Channel1
	hcomm->offset = 0;							//set 0.
	__HAL_UART_CLEAR_OREFLAG(huart);			//Clears the UART ORE pending flag.
	HAL_DMA_Start(huart->hdmarx, (u32)&huart->Instance->DR, (u32)hcomm->dma_rx_buffer, hcomm->buffer_size);		//Starts the DMA Transfer.
	huart->Instance->CR3 |= USART_CR3_DMAR;		//USART_CR3_DMAR : DMA Enable Receiver. 
}


/* judge	*/
bool BspUsart_CanSendData(BspUsartType *hcomm)
{
	if(hcomm->huart->hdmatx->State != HAL_DMA_STATE_BUSY
		|| __HAL_DMA_GET_FLAG(hcomm->huart->hdmatx, hcomm->tx_tc_flag))
	{
		return TRUE;
	}
	return FALSE;
}


/* TX	*/

static HAL_StatusTypeDef BspUsart_SendData(UART_HandleTypeDef *huart, const u8 *pData, u16 size, u32 tx_tc_flag)
{
	if(__HAL_DMA_GET_FLAG(huart->hdmatx, tx_tc_flag))
	{
		if(huart->gState == HAL_UART_STATE_BUSY_TX_RX)
		{
			huart->gState = HAL_UART_STATE_BUSY_TX;
		}
		else
		{
			huart->gState = HAL_UART_STATE_READY;
		}
		
		__HAL_UNLOCK(huart->hdmatx);
		__HAL_DMA_CLEAR_FLAG(huart->hdmatx, tx_tc_flag);
	}
	return HAL_UART_Transmit_DMA(huart, (u8*)pData, size);
}

u8 UserUsart_SendData(BspUsartType *hcomm, const u8 *data, u16 len)
{
	return BspUsart_SendData(hcomm->huart, data, len, hcomm->tx_tc_flag);
}

/* RX	*/

bool BspUsart_RecvData(BspUsartType *hcomm, u8 **pbuf, u32* plen)
{
	if(hcomm->huart == NULL) return FALSE;
	
	u16 data_cnt = hcomm->buffer_size - __HAL_DMA_GET_COUNTER(hcomm->huart->hdmarx);
	*pbuf = &hcomm->dma_rx_buffer[hcomm->offset];
	if(data_cnt < hcomm->offset)
	{
		*plen = hcomm->buffer_size - hcomm->offset;
		hcomm->offset = 0;
	}
	else
	{
		*plen = data_cnt - hcomm->offset;
		hcomm->offset = data_cnt;
	}
	
	if(*plen > 0)	return TRUE;
	
	return FALSE;
}

/* RX2	*/



