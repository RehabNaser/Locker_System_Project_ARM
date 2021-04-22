/*
 * File Name: LOCKER_SYSTEM.c
 * Creation Date: 01/26/2021
 * Author: Rehab
 * Description: C File for Locker System Project....
 */ 

#include "LOCKER_SYSTEM.h"

volatile uint8 LCDStateFlag=CLEAR;

void LockerSystem(void)
{
	LCDInit();
	KeypadInit();
	
	volatile uint8 InputKey;
	volatile uint8 PasswordlengthChecker;
	volatile uint8 PasswordCorrectionChecker;
	volatile int8 WrongPasswordCounter=TRYING_NUMBER;
	
	volatile uint8 LockerStateFlag=CLOSE;
	volatile uint8 Key_B_StateFlag=NOT_PRESSED;
	volatile uint8 KeyPressingFlag=RELEASED;
	
    while(1)
    {
		InputKey=KeypadMustPressed();
		STK_voidBusyWait(20000);
		if((KeypadReadKey()==InputKey)&&(KeyPressingFlag==RELEASED))
		{
			KeyPressingFlag=PRESSED;
			LCDClean();
			if(LockerStateFlag==OPEN)
			{
				if(InputKey==Keypad[1][3])
				{

					if(Key_B_StateFlag==NOT_PRESSED)
					{
						Key_B_StateFlag=PRESSED;
						LCDClear();
						LCDDisplayString(1,1,"Enter New Pass..");
						LCDStateFlag=WRITTEN;
					}
					else
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							SetPassword(PASSWORD_DIGITS_NUMBER);
							Key_B_StateFlag=NOT_PRESSED;
							LCDClear();
							LCDDisplayString(1,1,"New Pass Saved..");
							LCDStateFlag=WRITTEN;
							ClearEnteredDigitsCounter();
						}
						else
						{
							ShortPassword();
							ClearEnteredDigitsCounter();
						}
					}
				}
				else if(InputKey==Keypad[2][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Locker is Closed");
					LCDStateFlag=WRITTEN;
					LockerStateFlag=CLOSE;
					ClearEnteredDigitsCounter();
				}
				else if(Key_B_StateFlag==PRESSED)
				{
					PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,InputKey);
					if(InputKey==Keypad[3][3])
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							LCDClear();
							LCDDisplayString(1,1,"Press B to Save");
							LCDStateFlag=WRITTEN;
						}
						else
						{
							ShortPassword();							
						}
					}
					else
					{
						IsPasswordLong(PasswordlengthChecker);
					}
				}
				else
				{
					LCDClear();
					LCDDisplayString(1,1,"Opened Already");
					LCDStateFlag=WRITTEN;
				}
			}
			else
			{
				if(InputKey==Keypad[1][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Must Open Locker");
					LCDStateFlag=WRITTEN;
					ClearEnteredDigitsCounter();
				}
				else if(InputKey==Keypad[2][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Closed Already");
					LCDStateFlag=WRITTEN;
					ClearEnteredDigitsCounter();
				}
				else
				{
					PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,InputKey);
					if(InputKey==Keypad[3][3])
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							PasswordCorrectionChecker=CheckPassword(PASSWORD_DIGITS_NUMBER);
							if(PasswordCorrectionChecker==CORRECT_PASSWORD)
							{
								LCDClear();
								LCDDisplayString(1,1,"Locker is Opened");
								LockerStateFlag=OPEN;
								LCDStateFlag=WRITTEN;
								WrongPasswordCounter=TRYING_NUMBER;
							}
							else
							{
								LCDClear();
								WrongPasswordCounter--;
								LCDDisplayString(1,1,"Wrong Password..");
								LCDDisplayString(2,1,"Remain   Tries");
								LCDDisplayNumber(2,8,WrongPasswordCounter);
								LCDStateFlag=WRITTEN;
								SystemHalt(WrongPasswordCounter);
							}
						}
						else
						{
							ShortPassword();							
						}
					}
					else
					{
						IsPasswordLong(PasswordlengthChecker);
					}
				}				
			}
					
		}
		if((KeypadReadKey()!=InputKey)&&(KeyPressingFlag==PRESSED))
		{
			
			KeyPressingFlag=RELEASED;
		}
    }
}


void LCDClean(void)
{	
	if(LCDStateFlag==WRITTEN)
	{
		LCDClear();
		LCDStateFlag=CLEAR;
	}
}

void LongPassword(void)
{
	LCDClear();
	LCDDisplayString(1,1,"Too Long Pass..");
	LCDStateFlag=WRITTEN;	
}

void ShortPassword(void)
{
	LCDClear();
	LCDDisplayString(1,1,"Too Short Pass..");
	LCDDisplayString(2,1,"Re-Enter Again");
	LCDStateFlag=WRITTEN;
}

void IsPasswordLong(uint8 PasswordlengthChecker)
{
	if(PasswordlengthChecker==LONG_LENGTH)
	{
		LongPassword();
	}
	else
	{
		LCDSendData('*');
	}	
}
	
void SystemHalt(int8 WrongPasswordCounter)
{
	if(WrongPasswordCounter<0)
	{
		LCDClear();
		LCDDisplayString(1,1,"System Halted..");
		LCDDisplayString(2,1,"More Than   Tries");
		LCDDisplayNumber(2,11,TRYING_NUMBER);
		LCDStateFlag=WRITTEN;
		STK_voidBusyWait(2000000);
		LCDDisplayOff();
		while(1);
	}
}
