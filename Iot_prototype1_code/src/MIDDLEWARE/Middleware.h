/***********************************************************************************************************************
* File Name      : Middleware.h
* Description    : This file implements device driver for (middleware)
*  Author         : Ahmed Yasser
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 11/13/2023
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
#ifndef Middleware_H_
#define Middleware_H_

#include "../HAL/SSD/Component_SSD.h"
#include "../HAL/PB/Component_PB.h"
#include "../HAL/IOT/iot.h"
typedef enum {
	status=0,
	power,
	error ,
	max_num
}t_general_state;

typedef enum {
	state0,
	state1,
	state2,
	state3
}t_state ;

typedef enum {
	PWR0,
	PWR1,
	PWR2,
	PWR3
}t_PWR ;

typedef enum {
	ERR0,
	ERR1,
	ERR2
}t_ERROR ;
void Switch_update(void) ;
void Display_Update(void) ;
t_ERROR ERROR_get(void);
t_PWR   POWER_get(void) ;
t_state STATUS_get(void);
void App_Init(void);
#endif
