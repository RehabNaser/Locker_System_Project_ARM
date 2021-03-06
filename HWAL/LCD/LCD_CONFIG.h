/*
 * File Name: LCD_CONFIG.h
 * Creation Date: 07/24/2020
 * Author: Rehab
 * Description: Header File for LCD connection...
 */ 
 
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//FILES INCLUDING
#include "GPIO.h"

//LCD MODES MACROS
#define LCD8BITSMODE 8
#define LCD4BITSMODE 4

//LCD MODE
#define LCD_MODE LCD4BITSMODE

//LCD CONNECTION
#define LCD_DATA_PORT PORT_A
#define LCD_CONTROL_PORT PORT_B 
#define LCD_DATA_PINS NIBBLE_TWO
#define LCD_RS PIN5
#define LCD_RW PIN6
#define LCD_EN PIN7

#endif