/*
 * GPIO_prog.c
 *
 *  Created on: Apr 1, 2021
 *      Author: REHAB
 */

#include "GPIO.h"

void GpioPinDirection(uint8 Port , uint8 PinNo ,uint8 Dir)
{

	switch(Port)
	{
		case PORT_A:
			if(PinNo<8)
			{
				NIBBLE_WRITE(GPIOA_CRL,PinNo,Dir);
			}
			else
			{
				PinNo-=8;
				NIBBLE_WRITE(GPIOA_CRH,PinNo,Dir);
			}
			break;
		case PORT_B:
			if(PinNo<8)
			{
				NIBBLE_WRITE(GPIOB_CRL,PinNo,Dir);
			}
			else
			{
				PinNo-=8;
				NIBBLE_WRITE(GPIOB_CRH,PinNo,Dir);
			}
			break;
		case PORT_C:
			if(PinNo<8)
			{
				NIBBLE_WRITE(GPIOC_CRL,PinNo,Dir);
			}
			else
			{
				PinNo-=8;
				NIBBLE_WRITE(GPIOC_CRH,PinNo,Dir);
			}
			break;
		default:
			break;			
	}
}
void GpioPinWrite(uint8 Port , uint8 PinNo ,uint8 Val)
{
	switch(Port)
	{
		case PORT_A:
			BIT_WRITE(GPIOA_ODR,PinNo,Val);
			break;
		case PORT_B:
			BIT_WRITE(GPIOB_ODR,PinNo,Val);
			break;
		case PORT_C:
			BIT_WRITE(GPIOC_ODR,PinNo,Val);
			break;
		default:
			break;			
	}	
}
uint8 GpioPinRead(uint8 Port,uint8 PinNo)
{
	uint8 Local_u8Date=0;
	switch(Port)
	{
		case PORT_A:
			Local_u8Date=BIT_GET(GPIOA_IDR,PinNo);
			break;
		case PORT_B:
			Local_u8Date=BIT_GET(GPIOB_IDR,PinNo);
			break;
		case PORT_C:
			Local_u8Date=BIT_GET(GPIOC_IDR,PinNo);
			break;
		default:
			break;	
	}	
	return Local_u8Date;
}

void GpioNibbleDirection(uint8 Port ,uint8 NibbleNo ,uint8 Dir )
{
	NibbleNo*=4;
	switch(Port)
	{
		case PORT_A:
			if(NibbleNo<8)
			{
				NIBBLE_WRITE(GPIOA_CRL,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOA_CRL,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOA_CRL,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOA_CRL,NibbleNo+3,Dir);
			}
			else
			{
				NibbleNo-=8;
				NIBBLE_WRITE(GPIOA_CRH,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOA_CRH,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOA_CRH,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOA_CRH,NibbleNo+3,Dir);
			}
			break;
		case PORT_B:
			if(NibbleNo<8)
			{
				NIBBLE_WRITE(GPIOB_CRL,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOB_CRL,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOB_CRL,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOB_CRL,NibbleNo+3,Dir);
			}                    
			else                 
			{                    
				NibbleNo-=8;     
				NIBBLE_WRITE(GPIOB_CRH,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOB_CRH,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOB_CRH,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOB_CRH,NibbleNo+3,Dir);
			}
			break;
		case PORT_C:
			if(NibbleNo<8)
			{
				NIBBLE_WRITE(GPIOC_CRL,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOC_CRL,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOC_CRL,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOC_CRL,NibbleNo+3,Dir);
			}
			else
			{
				NibbleNo-=8;
				NIBBLE_WRITE(GPIOC_CRH,NibbleNo,Dir);
				NIBBLE_WRITE(GPIOC_CRH,NibbleNo+1,Dir);
				NIBBLE_WRITE(GPIOC_CRH,NibbleNo+2,Dir);
				NIBBLE_WRITE(GPIOC_CRH,NibbleNo+3,Dir);
			}
			break;
		default:
			break;			
	}	
}

void GpioNibbleWrite(uint8 Port ,uint8 NibbleNo , uint8 Val )
{
	switch(Port)
	{
		case PORT_A:
			NIBBLE_WRITE(GPIOA_ODR,NibbleNo,Val);
			break;
		case PORT_B:
			NIBBLE_WRITE(GPIOB_ODR,NibbleNo,Val);
			break;
		case PORT_C:
			NIBBLE_WRITE(GPIOC_ODR,NibbleNo,Val);
			break;
		default:
			break;			
	}	
}

uint8 GpioNibbleRead(uint8 Port,uint8 NibbleNo )
{
	uint8 Local_u8Date=0;
	switch(Port)
	{
		case PORT_A:
			Local_u8Date=NIBBLE_GET(GPIOA_IDR,NibbleNo);
			break;
		case PORT_B:
			Local_u8Date=NIBBLE_GET(GPIOB_IDR,NibbleNo);
			break;
		case PORT_C:
			Local_u8Date=NIBBLE_GET(GPIOC_IDR,NibbleNo);
			break;
		default:
			break;	
	}	
	return Local_u8Date;	
}
