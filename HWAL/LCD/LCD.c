/*
 * File Name: LCD.c
 * Creation Date: 07/24/2020
 * Author: Rehab
 * Description: C File for LCD...
 */ 

#include "LCD.h"

static void LCD8BitsModeReset(void)
{	

}

static void LCD4BitsModeReset(void)
{
	GpioNibbleDirection(LCD_DATA_PORT ,LCD_DATA_PINS ,DIO_OUTPUT_2MHZ_PUSH_PULL );
	STK_voidBusyWait(20000);
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS ,0X03 );
	LCDEnableSignal();
	STK_voidBusyWait(5000);
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS ,0X03 );
	LCDEnableSignal();
	STK_voidBusyWait(150);
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS ,0X03 );
	LCDEnableSignal();	
	STK_voidBusyWait(150);
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS ,0X02 );
	LCDEnableSignal();
	STK_voidBusyWait(150);
	LCDSendCommand(LCD_4BITS_2LINE_5X8);
}

static void LCDEnableSignal(void)
{
	GpioPinWrite(LCD_CONTROL_PORT,LCD_EN,HIGH);
	STK_voidBusyWait(1);
	GpioPinWrite(LCD_CONTROL_PORT,LCD_EN,LOW);
	STK_voidBusyWait(1);	
}

void LCDInit(void)
{
	#ifdef LCD_RW
		GpioPinDirection(LCD_CONTROL_PORT,LCD_RW,DIO_OUTPUT_2MHZ_PUSH_PULL);
		GpioPinWrite(LCD_CONTROL_PORT,LCD_RW,WRITE);
	#endif
	
	GpioPinDirection(LCD_CONTROL_PORT,LCD_RS,DIO_OUTPUT_2MHZ_PUSH_PULL);
	GpioPinDirection(LCD_CONTROL_PORT,LCD_EN,DIO_OUTPUT_2MHZ_PUSH_PULL);
	GpioPinWrite(LCD_CONTROL_PORT,LCD_EN,HIGH);
	
	#if LCD_MODE==LCD4BITSMODE
		LCD4BitsModeReset();
	#elif LCD_MODE==LCD8BITSMODE
		LCD8BitsModeReset();
	#endif
	
	LCDClear();
	LCDDisplayOn(CURSOR_ON,BLINK_OFF);
	LCDWriteEnglish();
}

static void LCDSendCmdOrData4BitsMode(uint8 CD)
{
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS , SEND_HIGHER_NIBBLE_PART(CD) );
	LCDEnableSignal();
	GpioNibbleWrite(LCD_DATA_PORT ,LCD_DATA_PINS , SEND_LOWER_NIBBLE_PART(CD) );
	LCDEnableSignal();
	STK_voidBusyWait(2000);	
}

static void LCDSendCmdOrData8BitsMode(uint8 CD)
{

}

void LCDSendCommand(uint8 Cmd)
{
	GpioPinWrite(LCD_CONTROL_PORT,LCD_RS,IR);
	#if LCD_MODE==LCD4BITSMODE
		LCDSendCmdOrData4BitsMode(Cmd);
	#elif LCD_MODE==LCD8BITSMODE
		LCDSendCmdOrData8BitsMode(Cmd);
	#endif
}

void LCDSendData(uint8 Data)
{
	GpioPinWrite(LCD_CONTROL_PORT,LCD_RS,DR);
	#if LCD_MODE==LCD4BITSMODE
		LCDSendCmdOrData4BitsMode(Data);
	#elif LCD_MODE==LCD8BITSMODE
		LCDSendCmdOrData8BitsMode(Data);
	#endif
}

void LCDSendString(uint8 *String)
{
	while(*String!='\0')
	{
		LCDSendData(*String);
		String++;
	} 	 	
}

void LCDSendNumber(uint32 Number)
{
	uint8 Numbers[10];
	int8 Count;
	if(Number==0)
	{
		LCDSendData(48);
		return;
	}
	for(Count=0;Number>0;Count++)
	{
		Numbers[Count]=(Number%10)+48;
		Number=Number/10;
	}
	for(Count--;Count>=0;Count--)
	{
		LCDSendData(Numbers[Count]);
	}	
}

void LCDClear(void)
{
	LCDSendCommand(LCD_CLEAR_DISPALY);
}

void LCDDisplayOff(void)
{
	LCDSendCommand(LCD_DISPLAYOFF_CURSOROFF);	
}

void LCDDisplayOn(uint8 CursorState,uint8 BlinkState)
{
	switch(CursorState)
	{
		case CURSOR_ON:
			switch(BlinkState)
			{
				case BLINK_ON:
					LCDSendCommand(LCD_DISPLAYON_CURSORON_BLINKING);
					break;
				case BLINK_OFF:
					LCDSendCommand(LCD_DISPLAYON_CURSORON_NOBLINKING);
					break;
				default:
					break;
			}
			break;
		case CURSOR_OFF:
			switch(BlinkState)
			{
				case BLINK_ON:
					LCDSendCommand(LCD_DISPLAYON_CURSOROFF_BLINKING);
					break;
				case BLINK_OFF:
					LCDSendCommand(LCD_DISPLAYON_CURSOROFF_NOBLINKING);
					break;
				default:
					break;					
			}
			break;
		default:
			break;
	} 	
}

void LCDWriteEnglish(void)
{
	LCDSendCommand(LCD_INC_AC);	
}

//ROWS AND COLUMNS START FROM 1
void LCDSetCursor(uint8 Row , uint8 column)
{
	column--;
	switch(Row)
	{
		case 1:
			LCDSendCommand(LCD_LINE1_DDRAM_ADDRESS(column));
			break;
		case 2:
			LCDSendCommand(LCD_LINE2_DDRAM_ADDRESS(column));
			break; 
		case 3:
			LCDSendCommand(LCD_LINE3_DDRAM_ADDRESS(column));
			break;	 
		case 4:
			LCDSendCommand(LCD_LINE4_DDRAM_ADDRESS(column));
			break;	
		default:
			break;
	}
}

//MUST SEND MY SINGLE CHAR WITH DOUBLE QUOTE "" (AS STRING)
void LCDDisplayString(uint8 Row , uint8 column , uint8 *String)
{
	LCDSetCursor(Row,column);
	LCDSendString(String);
}

//CAN SEND MY SINGLE CHAR WITH SINGLE QUOTE ''
void LCDDisplayChar(uint8 Row , uint8 column , uint8 Char)
{
	LCDSetCursor(Row,column);
	LCDSendData(Char);
}

void LCDDisplayNumber(uint8 Row , uint8 column , uint32 Number)
{
	LCDSetCursor(Row,column);
	LCDSendNumber(Number);
}
