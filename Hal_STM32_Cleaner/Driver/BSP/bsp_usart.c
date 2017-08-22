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
	
	/* 假定函数进入后DMA Buffer里面已经存了四个单元的数据，DMA单元个数总共设置为20*/
	/*
	__HAL_DMA_GET_COUNTER() 这个函数的功能是获得DMA 接收buffer里面剩余的数据单元
	也就是还没被填充的数据单元。
	下面一行代码：data_cnt 得到的是DMA Buffer里面已存的数据单元个数，这些已存的单
	元待取用。
	*/
	u16 data_cnt = hcomm->buffer_size - __HAL_DMA_GET_COUNTER(hcomm->huart->hdmarx);
	
	/* 获得数据单元的起始地址，因为其实地址可能不是DMA Buffer的首地址	*/
	*pbuf = &hcomm->dma_rx_buffer[hcomm->offset];
	
	/* 剩余单元个数与偏移量的判断，最初偏移量offset是0	*/
	if(data_cnt < hcomm->offset)
	{
		*plen = hcomm->buffer_size - hcomm->offset;		
		hcomm->offset = 0;
	}
	else
	{
		*plen = data_cnt - hcomm->offset;	/* plen获得的是DMA Buffer 里面还能够被填充的单元个数，假定已经存了*/	
		hcomm->offset = data_cnt;			/* 把偏移量重新定位置*/
	}
	
	if(*plen > 0)	return TRUE;
	
	return FALSE;
}

/* RX2	*/



