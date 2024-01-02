/***********************************************************************************************************************
* File Name      : MCAL_R5F11BBC_MAIN.h
* Description    : This file includes core ,Datatype ,Bitmath.
*  Author         : Sherif Elgiar
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 01/01/2024
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
#ifndef MCAL_R5F11BBC_MAIN_H_
#define MCAL_R5F11BBC_MAIN_H_
/**Includes ==================================================================================*/
#include<iodefine.h>
#include<builtin.h>
#include<_h_c_lib.h>
#include<assert.h>
#include<ctype.h>
#include<errno.h>
#include<float.h>
#include<inttypes.h>
#include<iso646.h>
#include<limits.h>
#include<math.h>
#include<setjmp.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**Data Types ================================================================================*/
#define tbyte uint8_t
#define tword uint16_t
#define tlong uint32_t
/**Definitions  ================================================================================*/
#define DI      __DI             //Disable Global inttrupt     
#define EI      __EI             //Enable  Global inttrupt 
#define HALT    __halt
#define NOP     __nop
#define STOP    __stop
#define BRK     __brk
/**BIT Math    ================================================================================*/
#define SET_BIT(reg, bit)   ((reg) |= (1 << (bit)))
#define CLR_BIT(reg, bit)   ((reg) &= ~(1 << (bit)))
#define GET_BIT(reg, bit)   (((reg) >> (bit)) & 0x01)
#define TOG_BIT(reg, bit)   ((reg) ^= (1 << (bit)))

/**Safe Guards ===============================================================================*/
//#define GPIO_SAFEGUARD_INIT()      do{\

#define GPIO_SAFEGUARD_Init()      do{\
	                                                           /*Set I/P Direction*/PM0=0xff;PM1=0xff;PM2=0xff;PM3=0xff;PM4=0xff;PM5=0xff;/*PM6=0xff;*/PM7=0xff;PM12=0xff;PM14=0xff;}while(0)

#define Registers_SAFEGUARD_Init()      do{/*Disable ADC Option*/\
	                                                                PMC0=0b11110000;\
                                                                    PMC1=0b11100000;\
                                                                    PMC2=0x0;\
                                                                    PMC12=0b11111110;\
                                                                    PMC14=0b01111111;\
	                                                                PER0=0;PER1=0;DI();}while(0)  /*Disable Clk for I2C,ADC,D/A*/\

/**END ==================================================================================*/
#endif
