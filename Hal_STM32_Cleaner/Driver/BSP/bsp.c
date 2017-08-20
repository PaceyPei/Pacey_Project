#ifndef __BSP_H__
#define __BSP_H__

#include "bsp.h"

#include "comm.h"


void Bsp_Init(void)
{
	AppComm_Init(&huart1);
	
}

#endif
