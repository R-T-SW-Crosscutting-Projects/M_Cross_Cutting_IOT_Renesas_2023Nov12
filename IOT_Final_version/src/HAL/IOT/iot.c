#include "math.h"
#include "iot.h"
#include "../../MCAL/MCAL_R5F11BBC_MAIN.h"
#include "../../MIDDLEWARE/Middleware.h"
#include "iot_user.h"


tword  PWR_value  =  0;
tbyte  ERR_value[MAX_ERR] = { 0};

tbyte IOT_data[DATA_MAX] = {0} ;
tbyte IOT_check[6]= {0} ;
tbyte Checksum_PWR_Flag=0;
tbyte Checksum_ERR_Flag=0;
tbyte Checksum_STATE_Flag=0;
tbyte Checksum_DISP_Flag=0;
tbyte counter = 0 ;


tbyte DISP_buffer[DISPLAY_MAX+6] = {0} ;
tbyte ERR_buffer[MAX_ERR+6]={0};
tbyte State_buffer[8] ={0} ;
tbyte PWR_buffer[10] = {0} ;

tword DISP_buffer_size = sizeof(DISP_buffer) / sizeof(DISP_buffer[0]);
tword PWR_buffer_size = sizeof(PWR_buffer) / sizeof(PWR_buffer[0]);
tword ERR_buffer_size =  sizeof(ERR_buffer) / sizeof(ERR_buffer[0]);
tword State_buffer_size =  sizeof(State_buffer) / sizeof(State_buffer[0]);

tbyte last_state_D = 1 ;
tbyte last_state_P = 1 ;
tbyte last_state_S = 1 ;
tbyte last_state_E = 1 ;

tbyte flag_D = 1 ;
tbyte flag_P = 1 ;
tbyte flag_S = 1 ;
tbyte flag_E = 1 ;

tbyte lastcount=0;
extern volatile tbyte recive_complete ;
extern tbyte recive_string[13] ;
tbyte iterator=0;

tbyte flag=1 ;
void IOT_Init(void)
{
	UARTX_Init(UARTx , BAUD , Parity ,  Direction , STOP_BITS ,Lenght);
	IOT_PWR_Msg_CLR();
	IOT_State_Msg_CLR();
	IOT_DISP_Msg_CLR();
	IOT_ERR_Msg_CLR();
}

void IOT_Enable(void)
{
	UARTX_Enable( UARTx);
}

void IOT_PWR_Msg_Set(tword value){
	tbyte sum = 0 ;
	PWR_buffer[0] = '*' ;
	PWR_buffer[1] = 'P' ;
	PWR_buffer[2] = (value/1000)+'0' ;
	PWR_buffer[3] = (((value%1000) -(value%100))/100) +'0' ;
	PWR_buffer[4] = (((value%100) -(value%10))/10)+'0' ;
	PWR_buffer[5] = (value%10)+'0' ;
	PWR_buffer[6] = 'C' ;
	sum =(PWR_buffer[2]-'0')+ (PWR_buffer[3]-'0')+( PWR_buffer[4]-'0')+ ( PWR_buffer[5] - '0' ) ;
	if(sum > 9){
		PWR_buffer[7] = (sum/10 ) +'0' ;
		PWR_buffer[8] = (sum%10)+'0' ;
	}else {
		PWR_buffer[7] = '0' ;
		PWR_buffer[8] = sum+ '0';
	}
	PWR_buffer[9] = '#'  ;

	flag_P = 1 ;
}
void IOT_Disp_Msg_set(tbyte ID ,tword value)
{
	tbyte  sum = 0 ;
	tbyte index =  0   ;

	DISP_buffer[0] = '*' ;
	DISP_buffer[1] = 'D' ;
	DISP_buffer[ID+1] = value+ '0' ;
	DISP_buffer[DISPLAY_MAX+2] = 'C' ;


	for (index = 2 ; index <(DISPLAY_MAX+2); index++){
		if(DISP_buffer[index] != 0 ){
			sum = sum + (DISP_buffer[index]-'0' ) ;
		}else {
			sum = sum + DISP_buffer[index] ;
		}
	}
	if(sum > 9){
		DISP_buffer[DISPLAY_MAX +3] = (sum/10 ) +'0' ;
		DISP_buffer[DISPLAY_MAX +4]  = (sum%10)+'0' ;
	}else {
		DISP_buffer[DISPLAY_MAX +3] = '0' ;
		DISP_buffer[DISPLAY_MAX +4] = sum+ '0';
	}

	DISP_buffer[DISPLAY_MAX +5] = '#' ;

	flag_D =1 ;

}
void IOT_ERR_Msg_set(tbyte ID ,tword value)
{
	tbyte  sum = 0 ;
	tbyte index =  0   ;

	ERR_buffer[0] = '*' ;
	ERR_buffer[1] = 'E' ;
	ERR_buffer[ID+1] = value+ '0' ;
	ERR_buffer[MAX_ERR+2] = 'C' ;


	for (index = 2 ; index <(MAX_ERR+2); index++){
		if(ERR_buffer[index] != 0 ){
			sum = sum + (ERR_buffer[index]-'0' ) ;
		}else {
			sum = sum + ERR_buffer[index] ;
		}
	}
	if(sum > 9){
		ERR_buffer[MAX_ERR +3] = (sum/10 ) +'0' ;
		ERR_buffer[MAX_ERR +4]  = (sum%10)+'0' ;
	}else {
		ERR_buffer[MAX_ERR +3] = '0' ;
		ERR_buffer[MAX_ERR +4] = sum+ '0';
	}

	ERR_buffer[MAX_ERR +5] = '#' ;

	flag_E =1 ;

}



void IOT_State_Msg_Set(tbyte value){
	tbyte sum = 0 ;
	State_buffer[0] = '*' ;
	State_buffer[1] = 'S' ;
	State_buffer[2] = ( value/10)+ '0' ;
	State_buffer[3] =  (value%10) + '0' ;
	State_buffer[4] = 'C'    ;
	sum =(State_buffer[2]-'0') + (State_buffer[3]-'0')  ;
	if(sum > 9){
		State_buffer[5] = (sum/10 ) +'0' ;
		State_buffer[6] = (sum%10)+'0' ;
	}else {
		State_buffer[5] = '0' ;
		State_buffer[6] = sum+ '0';
	}
	State_buffer[7] = '#'  ;

	flag_S=1 ;


}

tword IOT_PWR_Msg_Get(void) {
	tword value = 0 ;
	value = ((PWR_buffer[2]-'0') * 1000)+((PWR_buffer[3]-'0') * 100) + ((PWR_buffer[4]-'0') * 10)+ (PWR_buffer[5]-'0') ;

	return value ;
}

tbyte IOT_DISP_Msg_Get(tbyte  ID) {
	tbyte value = (DISP_buffer[ID+1]-'0') ;
	return value ;
}


tbyte IOT_ERR_Msg_Get(tbyte ID) {
	return (ERR_buffer[ID+1] - '0') ;
}

tbyte IOT_State_Msg_Get (void ) {
	tbyte  value  = 0 ;
	value = ((State_buffer[2]-'0') *10 )+(State_buffer[3]-'0');
	return  value   ;
}

void IOT_PWR_Msg_CLR(void) {

	tbyte i=0;
	for(i=0;i<10;i++)
	{
		PWR_buffer[i]='0';
	}

}
void IOT_State_Msg_CLR(void){
	tbyte i=0;
	for(i=0;i<8;i++)
	{
		State_buffer[i]='0';
	}

}

void IOT_DISP_Msg_CLR(void) {

	tbyte i=0;
	for(i=0;i<(DISPLAY_MAX+6);i++)
	{
		DISP_buffer[i]='0';
	}

}

void IOT_ERR_Msg_CLR(void) {
	tbyte i = 0 ;
	for( i = 0 ; i <(MAX_ERR+6) ; i++)
	{
		ERR_buffer[i]='0';
	}

}



tbyte IOT_PWR_check_sum_Get(void) {

	tbyte  result1  ,  result2  ;
	result1 = (PWR_buffer[7] -'0')*10 ;
	result2 = PWR_buffer[8] -'0'  ;

	result2  =result1 +  result2;

	return result2 ;
}

tbyte  IOT_ERR_check_sum_Get(void) {

	return ((ERR_buffer[MAX_ERR +3]-'0')*10) +(ERR_buffer[MAX_ERR + 4]-'0')  ;
}

tbyte IOT_STATE_check_sum_Get(void) {

	return (State_buffer[3]-'0') ;
}

tbyte IOT_DISP_check_sum_Get(void) {

	return (DISP_buffer[DISPLAY_MAX+3]-'0') +(DISP_buffer[DISPLAY_MAX +4]-'0');
}

static tlong IOT_ERROR_STATE_CHANGE(void){
	tword index = 0 ;
	tlong sum = 0 ;
	for (index = 2 ; index <(MAX_ERR+2); index++){
		if(ERR_buffer[index] != 0 ){
			sum = sum + ((ERR_buffer[index]-'0' ) * powf(10,(index-2)));
		}else {
			sum = sum + (ERR_buffer[index]* powf(10,(index-2))) ;
		}
	}
	return sum ;
}


void IOT_update(void)
{

	static tbyte Checksum_PWR = 0 ;
	static tbyte Checksum_ERR = 0 ;
	static tbyte Checksum_STATE= 0;
	static tbyte Checksum_DISP = 0;

	if(Checksum_PWR == IOT_PWR_check_sum_Get()){
		if(Checksum_PWR_Flag == EMPTY_TIME){
			Checksum_PWR_Flag = 0 ;
		}else{
			Checksum_PWR_Flag++ ;
		}
	}else {
		Checksum_PWR_Flag = 0 ;
		Checksum_PWR = IOT_PWR_check_sum_Get() ;
	}

	if(Checksum_ERR == IOT_ERR_check_sum_Get()){
		if(Checksum_ERR_Flag == EMPTY_TIME)
			Checksum_ERR_Flag = 0  ;
		else
			Checksum_ERR_Flag++ ;
	}else {
		Checksum_ERR_Flag = 0 ;
		Checksum_ERR = IOT_ERR_check_sum_Get() ;
	}

	if(Checksum_DISP == IOT_DISP_check_sum_Get()){
		if(Checksum_DISP_Flag == EMPTY_TIME)
			Checksum_DISP_Flag = 0  ;
		else
			Checksum_DISP_Flag++ ;
	}else {
		Checksum_DISP_Flag = 0 ;
		Checksum_DISP = IOT_DISP_check_sum_Get() ;
	}

	if(Checksum_STATE == IOT_STATE_check_sum_Get()){
		if(Checksum_STATE_Flag == EMPTY_TIME)
			Checksum_STATE_Flag = 0  ;
		else
			Checksum_STATE_Flag++ ;
	}else {
		Checksum_STATE_Flag = 0 ;
		Checksum_STATE = IOT_STATE_check_sum_Get() ;
	}
	if(((last_state_P != IOT_PWR_Msg_Get())&&(Checksum_PWR_Flag == EMPTY_TIME )&& (Checksum_PWR != 0))||((Checksum_PWR != 0)&& ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='p')))){
		tbyte i = 0 ;
		UARTX_Send( UARTx,PWR_buffer,PWR_buffer_size);
		last_state_P = IOT_PWR_Msg_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

	}else if ((IOT_check[0]=='c') && (IOT_check[1]=='f' )&&(IOT_check[2]=='m') &&(IOT_check[3]=='p'))
	{
		tbyte i = 0 ;
		IOT_PWR_Msg_CLR() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

		flag_P = 0 ;
	}

	if(((last_state_D != IOT_DISP_check_sum_Get() )&&(Checksum_DISP_Flag == EMPTY_TIME)&& (Checksum_DISP != 0))||((Checksum_DISP != 0)&& ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='d')))){
		tbyte i = 0 ;
		UARTX_Send( UARTx,DISP_buffer,DISP_buffer_size);
		last_state_D = IOT_DISP_check_sum_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
		flag_D = 0 ;

	}else if ((IOT_check[0]=='c') && (IOT_check[1]=='f' )&&(IOT_check[2]=='m')&&(IOT_check[3]=='d'))
	{
		tbyte i = 0 ;
		IOT_DISP_Msg_CLR() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
		flag_D = 0 ;
	}

	if(((last_state_S != IOT_State_Msg_Get())&&(Checksum_STATE_Flag == EMPTY_TIME)&& (Checksum_STATE != 0))||((Checksum_STATE != 0)&& ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='s')))) {
		tbyte i = 0 ;
		UARTX_Send( UARTx,State_buffer,State_buffer_size);
		last_state_S = IOT_State_Msg_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

	}else if ((IOT_check[0]=='c') && (IOT_check[1]=='f' )&&(IOT_check[2]=='m') &&(IOT_check[3]=='s'))
	{
		tbyte i = 0 ;
		IOT_State_Msg_CLR() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

		flag_S = 0 ;
	}

	if(((last_state_E != IOT_ERROR_STATE_CHANGE())&&(Checksum_ERR_Flag == EMPTY_TIME) && (Checksum_ERR != 0))||((Checksum_ERR != 0)&&((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='e')))){
		tbyte i = 0 ;
		UARTX_Send( UARTx,ERR_buffer,ERR_buffer_size);
		last_state_E = IOT_ERROR_STATE_CHANGE() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

	}else if ((IOT_check[0]=='c') && (IOT_check[1]=='f' )&&(IOT_check[2]=='m' &&(IOT_check[3]=='e')))
	{
		tbyte i = 0 ;
		IOT_ERR_Msg_CLR() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}

		flag_E = 0 ;
	}

	if(((last_state_D != IOT_DISP_check_sum_Get())&&(IOT_DISP_check_sum_Get() == 0)) || ( (IOT_DISP_check_sum_Get() == 0) && ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='d')))){
		tbyte i =0 ;
		UARTX_Send( UARTx,DISP_buffer,DISP_buffer_size);
		last_state_D = IOT_DISP_check_sum_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
	}
	if(((last_state_P != IOT_PWR_Msg_Get())&& (IOT_PWR_Msg_Get() == 0))||( (IOT_PWR_Msg_Get() == 0) && ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='p')))){
		tbyte i =0 ;
		UARTX_Send( UARTx,PWR_buffer,PWR_buffer_size);
		last_state_P = IOT_PWR_Msg_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
	}
	if(((last_state_S != IOT_State_Msg_Get())&& (IOT_State_Msg_Get() == 0))||( (IOT_State_Msg_Get() == 0) && ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='s')))){
		tbyte i =0 ;
		UARTX_Send( UARTx,State_buffer,State_buffer_size);
		last_state_S = IOT_State_Msg_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
	}
	if(((last_state_E !=IOT_ERR_check_sum_Get()) && (IOT_ERR_check_sum_Get() == 0))||( (IOT_ERR_check_sum_Get() == 0) && ((IOT_check[0]=='r') &&(IOT_check[1]=='p' )&&(IOT_check[2]=='t')&&(IOT_check[3]=='e')))){
		tbyte i =0 ;
		UARTX_Send( UARTx,ERR_buffer,ERR_buffer_size);
		last_state_E = IOT_ERR_check_sum_Get() ;
		for(i = 0 ; i < 6  ; i ++){
			IOT_check[i] = 0 ;
		}
	}

	/*recive Data            */


	if(recive_complete) {

		tbyte i = 0 ;
		while( i < 13){


			if(recive_string[i] == 'U'){
		        tword index = 0  , calc_index = 0 , string_index = i+1 ;
			  tbyte check_sum = 0  , check_calc = 0  ;
				for(index = 0 ; index <(DATA_MAX-3) ; index++){
				IOT_data[index] = (recive_string[string_index++] -'0')  ;

				}
				IOT_data[DATA_MAX-3] = 'C' ;
				IOT_data[DATA_MAX-2] = (recive_string[i+4] -'0')*10 ;
				IOT_data[DATA_MAX-1] = (recive_string[i+5] -'0')    ;

				for(calc_index = 0 ;calc_index<(DATA_MAX-3); calc_index++){
					check_calc = IOT_data[calc_index] + check_calc ;
				}

				check_sum = IOT_data[DATA_MAX-1] +IOT_data[DATA_MAX-2] ;

				if(check_sum == check_calc){
					UARTX_Send(UARTx,"*cfm#",6) ;
				}else {
					UARTX_Send(UARTx,"*rpt#",6) ;
				}


			}else if ((recive_string[i]=='c') && (recive_string[i+1]=='f' )&&(recive_string[i+2]=='m')&&((recive_string[i+3]=='d')||(recive_string[i+3]=='s')||(recive_string[i+3]=='p')||(recive_string[i+3]=='e'))){
				IOT_check[0] = 'c' ;
				IOT_check[1] = 'f' ;
				IOT_check[2] = 'm' ;
				IOT_check[3] = recive_string[i+3] ;

			}else if((recive_string[i]=='r') && (recive_string[i+1]=='p' )&&(recive_string[i+2]=='t')){
				IOT_check[0] = 'r' ;
				IOT_check[1] = 'p' ;
				IOT_check[2] = 't' ;
				IOT_check[3] = recive_string[i+3] ;
			}
			i++  ;
		}
		recive_complete = 0 ;
	}

}




tbyte IOT_PWR_flag_Get(void) {

	return flag_P;
}

tbyte  IOT_ERR_flag_Get(void) {
	return flag_E;
}

tbyte IOT_STATE_flag_Get(void) {
	return flag_S;
}

tbyte IOT_DISP_flag_Get(void) {
	return flag_D;
}




