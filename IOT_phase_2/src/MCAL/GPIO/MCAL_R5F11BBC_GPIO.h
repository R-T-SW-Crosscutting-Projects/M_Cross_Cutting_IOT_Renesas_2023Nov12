/***********************************************************************************************************************
* File Name      : MCAL_R5F11BBC_GPIO.h
* Description    : This file implements device driver for (GPIO)
*  Author         : Sherif Elgiar
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 01/01/2024
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
#ifndef MCAL_R5F11BBC_GPIO_H_
#define MCAL_R5F11BBC_GPIO_H_
/**Includes =====================================================================================================================*/
#include "../MCAL_R5F11BBC_Config.h"
/**Definitions ===================================================================================================================*/

/**Selections ====================================================================================================================*/
typedef enum {
	                    Port_0,
	                    Port_1,
	                    Port_2,
	                    Port_3,
	                    Port_4,
	                    Port_5,
	                    Port_7,
	                    Port_12,
	                    Port_13,/*always used as Input*/
	                    Port_14
                       }tport;

 typedef enum
                     {
              	          Pin_0=0,
              	          Pin_1,
              	          Pin_2,
              	          Pin_3,
              	          Pin_4,
              	          Pin_5,
              	          Pin_6,
              	          Pin_7,
                        }tpin;

 typedef enum
                   {
                   normal_usage,
				   communication_usage //I2C ,SPI,UART
                   }t_usage;

 typedef enum {
                   	     output,
                   	      input
                        }t_direction;
/**Prototypes ===================================================================================================================*/
 /* @brief :AUTO Pull up */
 void GPIO_Output_Init(tport port,tpin pin,tbyte value,t_usage usage);
 void GPIO_Input_Init(tport port,tpin pin,t_usage usage);
 t_direction GPIO_Direction_get(tport port,tpin pin);

 /* @brief :values*/
 void GPIO_Value_Set(tport port,tpin pin,tbyte value);
 tbyte GPIO_Value_Get(tport port,tpin pin);
  void GPIO_Value_Tog(tport port,tpin pin);

/**END =======================================================================================================================*/
#endif
