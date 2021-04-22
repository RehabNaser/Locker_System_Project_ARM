#include "RCC.h"

void RCC_VoidInit(void)
{
	#if 	RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		REG_WRITE(RCC_CR,0x00010000);
		REG_WRITE(RCC_CFGR,0x00000001);
		/*while() // waiting till be stable
		{
			asm("NOP");
		}*/
	#elif 	RCC_CLOCK_TYPE == RCC_HSE_RC

	#elif 	RCC_CLOCK_TYPE == RCC_HSI

	#elif 	RCC_CLOCK_TYPE == RCC_PLL

	//#else 	#error("Wrong choice of RCC clock type")
	#endif
}

void RCC_VoidEnablePeripheralClk(uint8 Copy_u8Bus,uint8 Copy_u8Per)
{
	if(Copy_u8Per<32) //check rang
	{
		switch(Copy_u8Bus)
		{
			case RCC_AHB:
				BIT_WRITE(RCC_AHBENR,Copy_u8Per,HIGH);
				//SET_BIT(RCC_AHBENR,Copy_u8Per);
				break;
			case RCC_APB1:
				BIT_WRITE(RCC_APB1ENR,Copy_u8Per,HIGH);
				//SET_BIT(RCC_APB1ENR,Copy_u8Per);
				break;
			case RCC_APB2:
				BIT_WRITE(RCC_APB2ENR,Copy_u8Per,HIGH);
				//SET_BIT(RCC_APB2ENR,Copy_u8Per);
				break;

		}
	}
	else
	{

	}
}

void RCC_VoidDisablePeripheralClk(uint8 Copy_u8Bus,uint8 Copy_u8Per)
{
	if(Copy_u8Per<32) //check rang
	{
		switch(Copy_u8Bus)
		{
			case RCC_AHB:
				BIT_WRITE(RCC_AHBENR,Copy_u8Per,LOW);
				//SET_BIT(RCC_AHBENR,Copy_u8Per);
				break;
			case RCC_APB1:
				BIT_WRITE(RCC_APB1ENR,Copy_u8Per,LOW);
				//SET_BIT(RCC_APB1ENR,Copy_u8Per);
				break;
			case RCC_APB2:
				BIT_WRITE(RCC_APB2ENR,Copy_u8Per,LOW);
				//SET_BIT(RCC_APB2ENR,Copy_u8Per);
				break;

		}
	}
	else
	{

	}
}
