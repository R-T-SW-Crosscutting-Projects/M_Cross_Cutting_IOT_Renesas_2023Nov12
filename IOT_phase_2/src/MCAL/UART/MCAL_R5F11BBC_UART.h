/******************************************************************************************************************************
 File Name      : MCAL_R5F11BBC_UART.h
 Description    : This file as Header for (UART)
 Author         : Ahmed Yasser
 Tester         : Ahmed Magdy
 Device(s)      : R5F11BBC
 Creation Date  : 15/10/2023
 Testing Date   :
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/

#ifndef MCAL_R5F11BBC_UART_H_
#define MCAL_R5F11BBC_UART_H_

/* Includes */
#include "../MCAL_General_Config.h"
#include "../MCAL_R5F11BBC_MAIN.h"


/*buffer size for recieve*/
#define SIZE_BUFFER_UART0   200 // buffer uart0

#define SIZE_BUFFER_UART1   13//buffer uart1

#define SIZE_BUFFER_UART2   200//buffer uart 2


extern tbyte buffer_uart1[SIZE_BUFFER_UART1] ;

extern tbyte buffer_uart2[SIZE_BUFFER_UART2] ;

extern tbyte buffer_uart0[SIZE_BUFFER_UART0] ;




/* Selection */
typedef enum{
	 SAU0_UART1 = 1  , //Serial_Array_Unit0_UART1
	 SAU1_UART2 ,  //Serial_Array_Unit1_UART2
	 SAU0_UART0    //Serial_Array_Unit0_UART0
}t_UART_Select ;


typedef enum{
    B_4800  =1,
    B_9600    ,
    B_19200
}t_Baud_Rate ;

typedef enum{
	NONE_parity =1 ,
    ZERO    ,
    ODD     ,
    EVEN
}t_Parity ;


typedef enum{
    LSB =1 ,
    MSB

}t_Transfer_Direction ;


typedef enum{
	NONE_stop =1 ,
    ONE_stop    ,
    TWO_stop

}t_Stop_Bit ;


typedef enum{
    L7 =1 ,
    L8    ,
    L9
}t_Data_Lenght ;


/* API */

void UARTX_Init(t_UART_Select UART_Num ,  t_Baud_Rate BAUD ,t_Parity Parity, t_Transfer_Direction Direction ,t_Stop_Bit STOP ,t_Data_Lenght Lenght);
void UARTX_Enable(t_UART_Select Uart_Num);
void UARTX_Disable(t_UART_Select UARTx) ;
void UARTX_Send(t_UART_Select UART_Num,tbyte * const tx_buf, tword tx_num);
//void UARTX_Receive(t_UART_Select UART_Num,tbyte * const rx_buf, tword rx_num);
void UARTX_Receive(tbyte *recieve_buffer );

static void UART1_CallBack_receiveend(tbyte rx_data);
static void UART1_CallBack_sendend(void);
static void UART2_CallBack_receiveend(tbyte rx_data);
static void UART2_CallBack_sendend(void);
static void UART0_CallBack_receiveend(tbyte rx_data);
static void UART0_CallBack_sendend(void);

/*==============================================================================================================================*/
/*END*/




#endif /* MCAL_R5F11BBC_UART_H_ */
