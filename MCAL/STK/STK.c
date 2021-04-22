/*
 * STK_program.c
 *
 *  Created on: Apr 5, 2021
 *      Author: Boon
 */

#include "STK.h"

#ifndef				NULL
#define 			NULL			(void *)0
#endif

static	void (*STK_PFCallBack)(void) = NULL;
static uint8	STK_u8ModeOfOperation ;

void	STK_voidInit(void)
{
	/*	Disable STK , Disable Interrupt , Set Pre-secaller	*/
	#if				STK_PRESCALLER == STK_AHB_DIV_8
						STK -> CTRL = 0x0;
						//CLR_BIT(STK -> VAL , 3);

	#elif			STK_PRESCALLER == STK_AHB
						STK -> CTRL = 0x00000004;
	#else
						#error "Wrong choice of SysTick Prescaller"
	#endif

}
/****************************************************************/
/* Description    :  This function used as a delay_us Function	*/
/*					 Inputs : Copy_u32Ticks 					*/
/*					 return : void		 						*/
/****************************************************************/
void	STK_voidBusyWait(uint32 Copy_u32Ticks)
{
		/*	1-	Load Ticks to the LOAD Register			*/
			STK -> LOAD = Copy_u32Ticks;
		/*	2-	STRART the timer						*/
			BIT_WRITE(STK -> CTRL,0,HIGH);
			//SET_BIT(STK -> CTRL,0);
		/*	3-	Wait till the flag fired				*/
			while((BIT_GET(STK -> CTRL,16)) == 0 )
			{
				asm("NOP");
			}
		/*	4-	STOP the Timer							*/
			BIT_WRITE(STK -> CTRL,0,LOW);
			//CLR_BIT(STK -> CTRL,0);
			STK -> VAL = 0;
			STK -> LOAD = 0;
}
void	STK_voidSetIntervalSingle(uint32 Copy_u32Ticks , void (*Copy_pf)(void))
{
		/*	1-	STOP the Timer							*/
			BIT_WRITE(STK -> CTRL,0,LOW);
			//CLR_BIT(STK -> CTRL,0);
			STK -> VAL = 0;
		/*	2-	Load Ticks to the LOAD Register			*/
			STK -> LOAD = Copy_u32Ticks;
		/*	3-	STRART the timer						*/
			BIT_WRITE(STK -> CTRL,0,HIGH);
			//SET_BIT(STK -> CTRL,0);
		/*	4-	Save Call-Back Address					*/
			STK_PFCallBack = Copy_pf;
		/*	5-	Mode Of operation is Single				*/
			STK_u8ModeOfOperation = STK_U8_SINGLE_INTERVAL;
		/*	6-	Enable Interrupt						*/
			BIT_WRITE(STK -> CTRL,1,HIGH);
			//SET_BIT(STK -> CTRL,1);
}
void	STK_voidSetIntervalPeriodic(uint32 Copy_u32Ticks , void (*Copy_pf)(void))
{
		/*	1-	Load Ticks to the LOAD Register			*/
			STK -> LOAD = Copy_u32Ticks;
		/*	2-	STRART the timer						*/
			BIT_WRITE(STK -> CTRL,0,HIGH);
			//SET_BIT(STK -> CTRL,0);
		/*	3-	Save Call-Back Address					*/
			STK_PFCallBack = Copy_pf;
		/*	4-	Mode Of operation is Periodic			*/
			STK_u8ModeOfOperation = STK_U8_PERIODIC_INTERVAL;
		/*	5-	Enable Interrupt						*/
			BIT_WRITE(STK -> CTRL,1,HIGH);
			//SET_BIT(STK -> CTRL,1);
}
void	STK_voidStopInterval(void)
{
		/*	1-	Disable Interrupt						*/
			BIT_WRITE(STK -> CTRL,1,LOW);
			//CLR_BIT(STK -> CTRL,1);

		/*	2-	STOP the Timer							*/
			BIT_WRITE(STK -> CTRL,0,LOW);
			//CLR_BIT(STK -> CTRL,0);
			STK -> VAL = 0;
			STK -> LOAD = 0;
}
uint32		STK_u32GetElapsedTime(void)
{
	uint32 Local_u32Time;

			Local_u32Time = STK -> LOAD - STK -> VAL;

	return Local_u32Time;
}
uint32		STK_u32GetRemainingTime(void)
{
	uint32 Local_u32Time;

			Local_u32Time = STK -> VAL;

	return Local_u32Time;
}

void SysTick_Handler(void)
{
	uint8 Local_u8Temp;
	/*		Check if the Mode of Operation is  Single	*/
	if(STK_u8ModeOfOperation == STK_U8_SINGLE_INTERVAL)
	{
		/*	1-	Disable Interrupt						*/
			BIT_WRITE(STK -> CTRL,1,LOW);
			//CL_BIT(STK -> CTRL,1);

		/*	2-	STOP the Timer							*/
			BIT_WRITE(STK -> CTRL,0,LOW);
			//CLR_BIT(STK -> CTRL,0);
			STK -> VAL = 0;
			STK -> LOAD = 0;
	}
	/*		CallBack Notification						*/
	STK_PFCallBack();
	/*		Clear Interrupt Flag by reading				*/
	Local_u8Temp = BIT_GET(STK -> CTRL,16);
	//Local_u8Temp = GET_BIT(STK -> CTRL ,  16);
}
