#ifndef IOT_USER_H
#define IOT_USER_H
#include "../../MIDDLEWARE/Middleware.h"



#define  DISPLAY_MAX     2
#define  MAX_ERR         2
#define  EMPTY_TIME      8
extern tbyte Options[max_num];

#define recieve_buffer_size  23

tbyte recieve_buffer[recieve_buffer_size];


/*UART_Select :
SAU0_UART1  //Serial_Array_Unit0_UART1
SAU1_UART2  //Serial_Array_Unit1_UART2
SAU0_UART0  //Serial_Array_Unit0_UART0
*/
#define  UARTx SAU0_UART1


/*Baud_Rate :
   B_4800
   B_9600
   B_19200
*/
#define  BAUD B_9600
/*
Parity
	NONE_parity
   ZERO
   ODD
   EVEN
*/
#define Parity NONE_parity

/*Transfer_Direction
   LSB
   MSB
*/


#define Direction LSB
/* Stop_Bit
	NONE_stop
   ONE_stop
   TWO_stop
   */

#define STOP_BITS ONE_stop
/*Data_Lenght
   L7
   L8
   L9
*/
#define Lenght L8







/*buffer size for recieve*/
#define SIZE_BUFFER_UART0   200 // buffer uart0

#define SIZE_BUFFER_UART1   13//buffer uart1

#define SIZE_BUFFER_UART2   200//buffer uart 2


extern tbyte buffer_uart1[SIZE_BUFFER_UART1] ;

extern tbyte buffer_uart2[SIZE_BUFFER_UART2] ;

extern tbyte buffer_uart0[SIZE_BUFFER_UART0] ;


#endif
