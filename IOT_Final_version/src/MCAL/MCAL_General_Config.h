/***********************************************************************************************************************
* File Name      : MCAL_General_Config.h
* Description    : This file to select required MCU Dvice
*  Author         : Sherif Elgiar
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 01/01/2024
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
#ifndef MCAL_General_Config_H_
#define MCAL_General_Config_H_
/**MCU List ====================================================================================================================*/
/*
Holtek
      MCU_HT66F489
Renesas
      MCU_R5F11BBC
*/
/**IDefine ======================================================================================================================*/
#define MCU_R5F11BBC (0)
/**Includes ======================================================================================================================*/
#ifdef MCU_R5F11BBC
	   #include "MCAL_R5F11BBC_MAIN.h"
       #include "GPIO/MCAL_R5F11BBC_GPIO.h"
       #include "UART/MCAL_R5F11BBC_UART.h"
	   
	   #define  F_CPU_Mhz          32
#endif
#ifdef MCU_HT66F489
       #include "MCAL_HT66F489_TIMER.h"
       #include "MCAL_HT66F489_GPIO.h"
       #include "MCAL_HT66F489_PWM.h"
#endif
/**END ========================================================================================================================*/
#endif
