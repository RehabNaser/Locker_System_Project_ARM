/*
 * GPIO_interface.h
 *
 *  Created on: Apr 1, 2021
 *      Author: REHAB
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "STD_MACROS.h"
#include "STM32F10xx_Registers.h"

#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'
#define PORT_E 'E'
#define PORT_F 'F'
#define PORT_G 'G'

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#define DIO_INPUT_ANALOG 0b0000
#define DIO_INPUT_FLOATING 0b0100
#define DIO_INPUT_PULL_UP_DOWN 0b1000

#define DIO_OUTPUT_2MHZ_PUSH_PULL 0b0001
#define DIO_OUTPUT_2MHZ_OPEN_DRAIN 0b0101
#define DIO_OUTPUT_2MHZ_AF_PUSH_PULL 0b1001
#define DIO_OUTPUT_2MHZ_AF_OPEN_DRAIN 0b1101

#define DIO_OUTPUT_10MHZ_PUSH_PULL 0b0010
#define DIO_OUTPUT_10MHZ_OPEN_DRAIN 0b0110
#define DIO_OUTPUT_10MHZ_AF_PUSH_PULL 0b1010
#define DIO_OUTPUT_10MHZ_AF_OPEN_DRAIN 0b1110

#define DIO_OUTPUT_50MHZ_PUSH_PULL 0b0011
#define DIO_OUTPUT_50MHZ_OPEN_DRAIN 0b0111
#define DIO_OUTPUT_50MHZ_AF_PUSH_PULL 0b1011
#define DIO_OUTPUT_50MHZ_AF_OPEN_DRAIN 0b1111


void GpioPinDirection(uint8 Port , uint8 PinNo ,uint8 Dir);
void GpioPinWrite(uint8 Port , uint8 PinNo ,uint8 Val);
uint8 GpioPinRead(uint8 Port,uint8 PinNo);

void GpioNibbleDirection(uint8 Port ,uint8 NibbleNo ,uint8 Dir );
void GpioNibbleWrite(uint8 Port ,uint8 NibbleNo , uint8 Val );
uint8 GpioNibbleRead(uint8 Port,uint8 NibbleNo );


#endif /* GPIO_INTERFACE_H_ */
