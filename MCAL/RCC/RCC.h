/*
 * RCC_interface.h
 *
 *  Created on: Mar 31, 2021
 *      Author: REHAB
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_
/* RCC Configuration*/

#include "STD_TYPES.h"
#include "STD_MACROS.h"
#include "STM32F10xx_Registers.h"

#define RCC_HSE_CRYSTAL 0
#define	RCC_HSE_RC 		1
#define RCC_HSI 		2
#define RCC_PLL 		3

#define RCC_CLOCK_TYPE RCC_HSE_CRYSTAL

#if  RCC_CLOCK_TYPE == RCC_PLL
	#define RCC_PLL_SOURCE RCC_PLL_HSI_DIIV_2
	#define RCC_PLL_MUL_VAL 9
#endif


#define RCC_PLL_HSI_DIIV_2
#define RCC_PLL_HSE
#define RCC_PLL_HSE_DIIV_2

#define RCC_AHB  0
#define RCC_APB1 1
#define RCC_APB2 2

void RCC_VoidInit(void);
void RCC_VoidEnablePeripheralClk(uint8 Copy_u8Bus,uint8 Copy_u8Per);
void RCC_VoidDisablePeripheralClk(uint8 Copy_u8Bus,uint8 Copy_u8Per);

#endif /* RCC_INTERFACE_H_ */
