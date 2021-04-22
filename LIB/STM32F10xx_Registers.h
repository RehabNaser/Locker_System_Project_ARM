#ifndef STM32F10XX_REGISTERS_H_
#define STM32F10XX_REGISTERS_H_

#include "STD_TYPES.h"

/*NVIC Registers*/
typedef struct
{
	volatile uint32 ISER[8];
	volatile uint32 Reserved1[24];
	volatile uint32 ICER[8];
	volatile uint32 Reserved2[24];
	volatile uint32 ISPR[8];
	volatile uint32 Reserved3[24];
	volatile uint32 ICPR[8];
	volatile uint32 Reserved4[24];
	volatile uint32 IABR[8];
	volatile uint32 Reserved5[56];
	volatile uint8 IPR[240];
}NVIC_Registers;

#define NVIC 		((NVIC_Registers*)0xE000E100)//no derefrancing
//////////////////////

/*SCB Registers*/
#define SCB_BASE_ADD 	(0xE000ED00)
#define SCB_AIRCR		*((volatile uint32*)(SCB_BASE_ADD+0x0C)
//////////////////////

/*RCC Registers*/
#define RCC_BASE_ADD	(0x40021000)
#define RCC_CR			*((volatile uint32*)(RCC_BASE_ADD+0x00))
#define RCC_CFGR		*((volatile uint32*)(RCC_BASE_ADD+0x04))
#define RCC_CIR			*((volatile uint32*)(RCC_BASE_ADD+0x08))
#define RCC_APB2RSTR	*((volatile uint32*)(RCC_BASE_ADD+0x0C))
#define RCC_APB1RSTR	*((volatile uint32*)(RCC_BASE_ADD+0x10))
#define RCC_AHBENR		*((volatile uint32*)(RCC_BASE_ADD+0x14))
#define RCC_APB2ENR		*((volatile uint32*)(RCC_BASE_ADD+0x18))
#define RCC_APB1ENR		*((volatile uint32*)(RCC_BASE_ADD+0x1C))
#define RCC_BDCR		*((volatile uint32*)(RCC_BASE_ADD+0x20))
#define RCC_CSR		    *((volatile uint32*)(RCC_BASE_ADD+0x24))
//////////////////////

/*GPIO Registers*/
#define GPIOA_BASE_ADD 	(0x40010800)
#define GPIOA_CRL 		*((volatile uint32*)(GPIOA_BASE_ADD+0x00))
#define GPIOA_CRH 		*((volatile uint32*)(GPIOA_BASE_ADD+0x04))
#define GPIOA_IDR		*((volatile uint32*)(GPIOA_BASE_ADD+0x08))
#define GPIOA_ODR		*((volatile uint32*)(GPIOA_BASE_ADD+0x0C))

#define GPIOB_BASE_ADD 	(0x40010C00)
#define GPIOB_CRL 		*((volatile uint32*)(GPIOB_BASE_ADD+0x00))
#define GPIOB_CRH 		*((volatile uint32*)(GPIOB_BASE_ADD+0x04))
#define GPIOB_IDR		*((volatile uint32*)(GPIOB_BASE_ADD+0x08))
#define GPIOB_ODR		*((volatile uint32*)(GPIOB_BASE_ADD+0x0C))

#define GPIOC_BASE_ADD 	(0x40011000)
#define GPIOC_CRL 		*((volatile uint32*)(GPIOC_BASE_ADD+0x00))
#define GPIOC_CRH 		*((volatile uint32*)(GPIOC_BASE_ADD+0x04))
#define GPIOC_IDR		*((volatile uint32*)(GPIOC_BASE_ADD+0x08))
#define GPIOC_ODR		*((volatile uint32*)(GPIOC_BASE_ADD+0x0C))
//////////////////////

/*AFIO Registers*/
typedef struct
{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 Reserved[2];
	volatile uint32 MAPR2;
}AFIO_Registers;

#define AFIO 		((AFIO_Registers*)0x40010000)//no derefrancing
/*
#define AFIO_BASE_ADD 		(0x40010000)
#define AFIO_EXTICR1 		*((volatile uint32*)(AFIO_BASE_ADD+0x08))
#define AFIO_EXTICR2 		*((volatile uint32*)(AFIO_BASE_ADD+0x0C))
#define AFIO_EXTICR3 		*((volatile uint32*)(AFIO_BASE_ADD+0x10))
#define AFIO_EXTICR4 		*((volatile uint32*)(AFIO_BASE_ADD+0x14))
*/
//////////////////////

/*External Intrrupt Registers*/
#define EXTI_BASE_ADD 	(0x40010400)
#define EXTI_IMR 		*((volatile uint32*)(EXTI_BASE_ADD+0x00))
#define EXTI_EMR 		*((volatile uint32*)(EXTI_BASE_ADD+0x04))
#define EXTI_RTSR 		*((volatile uint32*)(EXTI_BASE_ADD+0x08))
#define EXTI_FTSR 		*((volatile uint32*)(EXTI_BASE_ADD+0x0C))
#define EXTI_SWIER 		*((volatile uint32*)(EXTI_BASE_ADD+0x10))
#define EXTI_PR 		*((volatile uint32*)(EXTI_BASE_ADD+0x14))
//////////////////////

/*DMA Registers*/
//DMA->CHANNEL[0].CCR
typedef struct
{
	volatile uint32 CCR;
	volatile uint32 CNDTR;
	volatile uint32 CPAR;
	volatile uint32 CMAR;
	volatile uint32 RESERVED;
}Channel_Registers;
typedef struct
{
	volatile uint32 ISR;
	volatile uint32 IFCR;
	volatile Channel_Registers CHANNEL[7];
}DMA_Registers;

#define DMA 		((DMA_Registers*)0x40020000)
//////////////////////

/*USART1 Registers*/
typedef struct
{
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 BRR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 CR3;
	volatile uint32 GTPR;
}USART1_Registers;

#define USART1 		((USART1_Registers*)0x40013800)
//////////////////////

/*SPI1 Registers*/
typedef struct
{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 CRCPR;
	volatile uint32 RXCRCR;
	volatile uint32 TXCRCR;
	volatile uint32 I2SCFGR;
	volatile uint32 I2SPR;
}SPI1_Registers;

#define SPI1 		((SPI1_Registers*)0x40013000)
//////////////////////

/*STK Registers*/
typedef struct
{
	volatile uint32 CTRL;
	volatile uint32 LOAD;
	volatile uint32 VAL;
}STK_Registers;

#define STK			((STK_Registers *)0xE000E010)
//////////////////////


#endif /* STM32F10XX_REGISTERS_H_ */