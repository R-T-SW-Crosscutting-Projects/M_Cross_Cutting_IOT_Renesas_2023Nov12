/***********************************************************************************************************************
* File Name      : MCAL_R5F11BBC_Config.h
* Description    : This file implements device driver for (WDT,CLK,LVR,Sys_Modes)
*  Author         : Sherif Elgiar
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 01/01/2024
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
#ifndef MCAL_R5F11BBC_Config_H_
#define MCAL_R5F11BBC_Config_H_
/**Includes =====================================================================================================================*/
#include "MCAL_R5F11BBC_MAIN.h"
/**Definitions ===================================================================================================================*/
#define WDT_Mode (*(volatile __near unsigned char  *)0x00C0)
/**Selections ====================================================================================================================*/
/*
 * Hirc : onchip Clock High Speed
 * all on Chip clk working volt : 3.3 Volt
 */
typedef enum
             {
	         Hirc_1MHz = 0,
			 Hirc_2MHz,
			 Hirc_4MHz,
			 Hirc_8MHz,
			 Hirc_16MHz,
			 Hirc_32MHz,
			 Exfreq_1Mhz = 11,
			 Exfreq_2Mhz,
			 Exfreq_4Mhz,
			 Exfreq_8Mhz,
			 Exfreq_16Mhz=15,
			 Exfreq_32Mhz,
	         }t_SYS_Freq;
typedef enum
            {
             halt,
			 stop
             }t_standby_mode;
/**Prototypes ===================================================================================================================*/
 /* @brief : Enable WDT Int */
 /* @brief : Enable LVR Int @ 2.75V */
void MCU_Config_Init(t_SYS_Freq Fsys);
/* @brief : Reset Counter of WDT */
void WDT_Reset();
void LVR_INT_Start(void);
//----------------------------------------------------------------------------------------------
/* @brief : */
void LVD_SetCallBackFun(void (* Pfun)(void));
/* @brief :Hlat Mode :stop main & ALL Int is working , wake up just int hapen so inside stop WDT Coint */
void Go_to_sleep(t_standby_mode mode);
/* @brief :use to Continuo WDT counter after wake up */
void Sys_wake_up();
void Global_interrupt_Enable();
void Global_interrupt_Disable();

/**END =======================================================================================================================*/
#endif
