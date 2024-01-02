/***********************************************************************************************************************
 * File Name      : Middleware.c
 * Description    : This file implements device driver for (middleware)
 *  Author         : Ahmed Yasser
 *  Tester          :
 * Device(s)      : R5F11BBC
 * Creation Date: 11/13/2023
 * Testing Date  :
 * @COPYRIGHT 2016 El-ARABY Research and development center.
 * all rights reserved
 ***********************************************************************************************************************/
/**Includes =====================================================================================================================*/
#include "Middleware.h"
#include "Middleware_user.h"


tbyte count = SSD_DEFAULT ;
extern tbyte flag ;
tbyte Options[max_num] = {STATUS_DEFAULT,PWR_DEFAULT,ERR_DEFAULT} ;
extern tbyte IOT_data[9]  ;

void Switch_update(void)
{

	if(PB_Get(0))
	{
		if(count == 0){
			count= 99 ;
			IOT_Disp_Msg_set(1, 9) ;
			IOT_Disp_Msg_set(2, 9) ;
		}
		else
		{
			count-- ;
			IOT_Disp_Msg_set(1,count/10) ;
			IOT_Disp_Msg_set(2,count%10) ;
		}
		flag=1;
	}
	else if(PB_Get(1))
	{
		if(count == 99)
		{
			count= 0 ;
			IOT_Disp_Msg_set(1, 0) ;
			IOT_Disp_Msg_set(2, 0) ;
		}
		else
		{
			count++ ;
			IOT_Disp_Msg_set(1,count/10) ;
			IOT_Disp_Msg_set(2,count%10) ;
		}
		flag=1;
	}
	if(PB_Get(2)){
		if(Options[status] == state3){
			Options[status] = state0 ;
			IOT_State_Msg_Set(state0) ;

		}else{
			Options[status]++ ;
			IOT_State_Msg_Set(Options[status]) ;
		}
		flag = 1 ;
	}
	if(PB_Get(3)){
		if(Options[error] == ERR2){
			Options[error] = ERR0 ;
			IOT_ERR_Msg_set(1, ERR0) ;
			IOT_ERR_Msg_set(2,ERR0 ) ;
		}else{

			Options[error] ++ ;
			if(Options[error] == ERR1 ){
				IOT_ERR_Msg_set(1, ERR1) ;
				IOT_ERR_Msg_set(2,ERR0 ) ;
			}else if (Options[error] == ERR2){
				IOT_ERR_Msg_set(1, ERR0) ;
			    IOT_ERR_Msg_set(2,ERR1 ) ;
			}
		}
		flag = 1 ;
	}
	if(PB_Get(4)){
		if(Options[power] == PWR3){
			Options[power] = PWR0 ;
			IOT_PWR_Msg_Set(0) ;
		}else{
			Options[power]++ ;
			IOT_PWR_Msg_Set(Options[power]) ;
		}
		flag = 1 ;
	}

}


void Display_Update(void){
	tbyte i = 0 ;
	tbyte c = 0 ;
	for(i = 0 ; i < IOT_data[0] ; i++){
		if(count == 99)
				{
					count= 0 ;
				}
				else
				{
					count++ ;
								}
	}

	for(c = 0 ; c < IOT_data[1] ; c++){
			if(count == 0)
					{
						count= 99 ;
					}
					else
					{
						count--;
									}
		}

	SSD_2Digits_Set(count/10, count%10) ;

	GPIO_Value_Set(Port_1, Pin_7,1) ;
	GPIO_Value_Set(Port_1, Pin_6 ,1) ;
	switch(ERROR_get())
	{
	case ERR0 : GPIO_Value_Set(Port_1, Pin_7,1) ;
	GPIO_Value_Set(Port_1, Pin_6 ,1) ;break ;

	case ERR2 :GPIO_Value_Set(Port_1, Pin_7,0) ;break ;

	case ERR1 :GPIO_Value_Set(Port_1, Pin_6 ,0) ;break ;
	}


	GPIO_Value_Set(Port_5, Pin_1,1) ;//3
	GPIO_Value_Set(Port_2, Pin_0 ,1) ;//2
	GPIO_Value_Set(Port_1, Pin_4 ,1) ;//1

	switch(POWER_get()){
	case PWR0 : GPIO_Value_Set(Port_5, Pin_1,1) ;//3
	GPIO_Value_Set(Port_2, Pin_0 ,1) ;//2
	GPIO_Value_Set(Port_1, Pin_4 ,1) ;//1
	break ;

	case PWR3 : GPIO_Value_Set(Port_1, Pin_4 ,0) ;break ;
	case PWR2 :GPIO_Value_Set(Port_2, Pin_0 ,0) ;break  ;
	case PWR1 :GPIO_Value_Set(Port_5, Pin_1 ,0) ;break ;
	}
	GPIO_Value_Set(Port_7, Pin_2,1) ;//1
	GPIO_Value_Set(Port_7, Pin_0 ,1) ;//2
	GPIO_Value_Set(Port_3, Pin_0 ,1) ;//3

	switch(STATUS_get()){
	case state0: GPIO_Value_Set(Port_7, Pin_2,1) ;//1
	GPIO_Value_Set(Port_7, Pin_0 ,1) ;//2
	GPIO_Value_Set(Port_3, Pin_0 ,1) ;//3
	break ;

	case state1 : GPIO_Value_Set(Port_7, Pin_2,0)  ;break ;

	case state2 :GPIO_Value_Set(Port_7, Pin_0 ,0) ;break  ;

	case state3 :GPIO_Value_Set(Port_3, Pin_0 ,0)  ;break ;
	}

}

t_ERROR ERROR_get(void){
	return Options[error] ;
}
t_PWR   POWER_get(void) {
	return Options[power] ;
}
t_state STATUS_get(void){
	return  Options[status] ;
}

void App_Init(void)
{
	IOT_Init();
	IOT_Enable() ;
	PB_Init(0, Port_12, Pin_1, falling_edge) ;
	PB_Init(1, Port_13, Pin_7, falling_edge) ;

	PB_Init(2, Port_7, Pin_3, falling_edge) ;//STATE_SW
	PB_Init(3, Port_1, Pin_5, falling_edge) ;//ERR_SW
	PB_Init(4, Port_5, Pin_0, falling_edge) ;//PWR_SW

	GPIO_Output_Init(Port_1, Pin_6,1, normal_usage) ;
	GPIO_Output_Init(Port_1, Pin_7,1, normal_usage) ;
	GPIO_Output_Init(Port_1, Pin_4,1, normal_usage) ;
	GPIO_Output_Init(Port_2, Pin_0,1, normal_usage) ;
	GPIO_Output_Init(Port_5, Pin_1,1, normal_usage) ;
	GPIO_Output_Init(Port_3, Pin_0,1, normal_usage) ;
	GPIO_Output_Init(Port_7, Pin_0,1, normal_usage) ;
	GPIO_Output_Init(Port_7, Pin_2,1, normal_usage) ;
}

