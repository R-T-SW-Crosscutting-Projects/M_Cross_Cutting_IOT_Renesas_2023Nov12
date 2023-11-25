#ifndef IOT_H
#define IOT_H

#include "../../MCAL/UART/MCAL_R5F11BBC_UART.h"
#include "../PB/Component_PB.h"

//#include "iot_user.h"

/*typedef struct {
    t_UART_Select UART_Num;
    t_Baud_Rate BAUD;
    t_Parity Parity;
    t_Transfer_Direction Direction;
    t_Stop_Bit STOP;
    t_Data_Lenght Length;
} UART_Config;

 UART_Config UART_Config_Array[3];
 UART_Config_Array[0]={ SAU0_UART1,B_9600,NONE_parity,LSB,NONE_stop,L8};

*/
/*extern tbyte buffer_uart1[SIZE_BUFFER_UART1] ;

extern tbyte buffer_uart2[SIZE_BUFFER_UART2] ;

extern tbyte buffer_uart0[SIZE_BUFFER_UART0] ;
*/

void iot_Init();


void iot_set();


void iot_update();

//void iot_Receive();
#endif
