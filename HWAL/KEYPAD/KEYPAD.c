/*
 * File Name: KEYPAD.c
 * Creation Date: 07/24/2020
 * Author: Rehab
 * Description: C File for keypad...
 */ 


#include "KEYPAD.h"

uint8 Keypad[4][4]=
{
	{'1','2','3','-'},
	{'4','5','6','*'},
	{'7','8','9','/'},
	{'c','0','=','+'}
};

void KeypadInit(void)
{
	//ROWS (INPUTS)
	GpioNibbleDirection(KEYPAD_PORT ,KEYPAD_ROWSPINS ,DIO_INPUT_PULL_UP_DOWN );
	
	#if KEYPAD_CONNECTION_MODE==PULLUP_SW
		GpioNibbleWrite(KEYPAD_PORT ,KEYPAD_ROWSPINS , NIBBLE_HIGH);
	#endif

	//COLUMNS (OUTPUTS)
	GpioNibbleDirection(KEYPAD_PORT ,KEYPAD_COLUMNPINS ,DIO_OUTPUT_2MHZ_PUSH_PULL );
	
	#if KEYPAD_CONNECTION_MODE==PULLDOWN
		GpioNibbleWrite(KEYPAD_PORT ,KEYPAD_COLUMNPINS , NIBBLE_LOW);
	#else
		GpioNibbleWrite(KEYPAD_PORT ,KEYPAD_COLUMNPINS , NIBBLE_HIGH);
	#endif	
} 

uint8 KeypadReadKey(void)
{
	uint8 Row=0,Col=0;

	#if KEYPAD_CONNECTION_MODE==PULLDOWN
		for(Col=0;Col<4;Col++)
		{
			GpioNibbleWrite(KEYPAD_PORT,KEYPAD_COLUMNPINS,NIBBLE_LOW);
			GpioPinWrite(KEYPAD_PORT,Col+(KEYPAD_COLUMNPINS*4),HIGH);
			Row=GpioNibbleRead(KEYPAD_PORT,KEYPAD_ROWSPINS);
			if(Row!=NIBBLE_LOW)
			{
				break;
			}
		}
		if(Col==4)
			return 0;
		else
			Row=KeypadWhichRow(Row);
		return Keypad[Row][Col];				
	#else
		for(Col=0;Col<4;Col++)
		{
			GpioNibbleWrite(KEYPAD_PORT,KEYPAD_COLUMNPINS,NIBBLE_HIGH);
			GpioPinWrite(KEYPAD_PORT,Col+(KEYPAD_COLUMNPINS*4),LOW);
			Row=GpioNibbleRead(KEYPAD_PORT,KEYPAD_ROWSPINS);
			if(Row!=NIBBLE_HIGH)
			{
				break;
			}
		}
		if(Col==4)
			return 0;
		else
			Row=KeypadWhichRow(Row);
		return Keypad[Row][Col];				
	#endif
		
}

static uint8 KeypadWhichRow(uint8 RowsVal)
{
	uint8 Row=4;
	#if KEYPAD_CONNECTION_MODE==PULLDOWN
		switch(RowsVal)
		{
			case 0X01:
				Row=0;			
				break;
			case 0X02:
				Row=1;		
				break;
			case 0X04:
				Row=2;
				break;
			case 0X08:
				Row=3;		
				break;
			default:
				break;
		}
		return Row;
	#else
		switch(RowsVal)
		{
			case 0X0E:
				Row=0;			
				break;
			case 0X0D:
				Row=1;		
				break;
			case 0X0B:
				Row=2;		
				break;
			case 0X07:
				Row=3;		
				break;
			default:
				break;
		}
		return Row;	
	#endif
}

uint8 KeypadMustPressed(void)
{
	uint8 Key;
	do 
	{
		Key=KeypadReadKey(); 	 
	}while (Key==0);
	return Key;	
}