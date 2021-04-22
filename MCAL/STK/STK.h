/*
 * STK_interface.h
 *
 *  Created on: Apr 5, 2021
 *      Author: Boon
 */

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_


#include "STD_TYPES.h"
#include "STD_MACROS.h"
#include "STM32F10xx_Registers.h"

/*
STK_PRESCALLER can be:
	1-STK_AHB_DIV_8
	2-STK_AHB
*/

#define 		STK_AHB_DIV_8						0
#define 		STK_AHB								1
#define 		STK_PRESCALLER				STK_AHB_DIV_8

#define 		STK_U8_SINGLE_INTERVAL				0
#define 		STK_U8_PERIODIC_INTERVAL			1

/*	RCC = 8MHZ 	*/
void	STK_voidInit(void);
void	STK_voidBusyWait(uint32 Copy_u32Ticks);
void	STK_voidSetIntervalSingle(uint32 Copy_u32Ticks , void (*Copy_pf)(void));
void	STK_voidSetIntervalPeriodic(uint32 Copy_u32Ticks , void (*Copy_pf)(void));
void	STK_voidStopInterval(void);
uint32	STK_u32GetElapsedTime(void);
uint32	STK_u32GetRemainingTime(void);




#endif /* STK_INTERFACE_H_ */
