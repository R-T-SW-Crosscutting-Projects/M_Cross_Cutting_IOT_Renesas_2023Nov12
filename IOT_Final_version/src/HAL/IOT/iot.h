#ifndef IOT_H
#define IOT_H

#include "../../MCAL/UART/MCAL_R5F11BBC_UART.h"
#include "../PB/Component_PB.h"

void IOT_Init(void);
void IOT_Enable(void);
void IOT_PWR_Msg_Set(tword value);
void IOT_Disp_Msg_set(tbyte ID ,tword value);
void IOT_ERR_Msg_set(tbyte ID ,tword value);
void IOT_State_Msg_Set(tbyte value);
tword IOT_PWR_Msg_Get(void) ;
tbyte IOT_DISP_Msg_Get(tbyte  ID) ;
tbyte IOT_ERR_Msg_Get(tbyte ID) ;
tbyte IOT_State_Msg_Get (void ) ;
void IOT_ERR_Msg_CLR(void) ;
void IOT_PWR_Msg_CLR(void) ;
void IOT_State_Msg_CLR(void);
void IOT_DISP_Msg_CLR(void) ;
tbyte IOT_PWR_check_sum_Get(void) ;
tbyte IOT_ERR_check_sum_Get(void) ;
tbyte IOT_STATE_check_sum_Get(void) ;
tbyte IOT_DISP_check_sum_Get(void) ;
void IOT_update(void) ;
tbyte IOT_PWR_flag_Get(void);
tbyte  IOT_ERR_flag_Get(void) ;
tbyte IOT_STATE_flag_Get(void);
tbyte IOT_DISP_flag_Get(void);

#endif
