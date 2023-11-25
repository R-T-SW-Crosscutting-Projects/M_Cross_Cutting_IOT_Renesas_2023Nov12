#include "iot.h"

#include "../../MCAL/MCAL_R5F11BBC_MAIN.h"
#include "../../MIDDLEWARE/Middleware.h"
#include "iot_user.h"

tbyte iot_buffer[iot_buffer_size];
tbyte laststate[3] = {1}  ;
extern tbyte count ;
tbyte lastcount=0;
extern tbyte recive_complete ;
extern tbyte recive_string[13] ;
tbyte iterator=0;

tbyte flag=1 ;
void iot_Init()
{
	UARTX_Init(SAU0_UART1, B_9600, NONE_parity, LSB, ONE_stop, L8);
	UARTX_Enable( SAU0_UART1);

}


void iot_set()
{



	/*send_buffer[0] = '*' ;
	send_buffer[1]=  'P' ;
	send_buffer[2] =  Options[power]+'0' ;
	send_buffer[3]=  'D' ;
	send_buffer[4]= (count/10)+'0';
	send_buffer[5]= (count%10)+'0' ;
	send_buffer[6]=  'E' ;
	if(Options[error] == ERR1){
	send_buffer[7]=   Options[error]+'0' ;
	send_buffer[8]=  '0' ;
	}else if(Options[error] == ERR2){
		send_buffer[7] = '0'  ;
	    send_buffer[8]= '1'   ;
	}else {
		send_buffer[7] = '0'   ;
		send_buffer[8] = '0' ;
	}
	send_buffer[9]=  'S' ;
	send_buffer[10]=   Options[status]+'0' ;
	send_buffer[11]=  '#' ;

	 UARTX_Send( SAU0_UART1,send_buffer,send_buffer_size);*/
	send_buffer[0] = '*' ;
	send_buffer[1]=  'P' ;
	switch(Options[power]){
	case PWR1 :
		send_buffer[2] = '0';
		send_buffer[3] = '0';
		send_buffer[4] = '1';break ;
	case PWR2 :
		send_buffer[2] = '0';
		send_buffer[3] = '1';
		send_buffer[4] = '0';break ;
	case PWR3 :
		send_buffer[2] = '1';
		send_buffer[3] = '0';
		send_buffer[4] = '0';break ;
	case PWR0 :
		send_buffer[2] = '0';
		send_buffer[3] = '0';
		send_buffer[4] = '0';break ;
	}
	send_buffer[5]=  'D' ;
	send_buffer[6]= (count/10)+'0';
	send_buffer[7]= (count%10)+'0' ;
	send_buffer[8]=  'E' ;
	switch(Options[power]){
	case ERR1 :
		send_buffer[9] = '0';
		send_buffer[10] = '1'; break ;
	case ERR2 :
		send_buffer[9] = '1';
		send_buffer[10] = '0'; break ;
	case ERR0 :
			send_buffer[9] = '0';
			send_buffer[10] = '0';break ;
	}
	send_buffer[11]=  'S' ;
	switch(Options[status]){
		case state1 :
			send_buffer[12] = '0';
			send_buffer[13] = '0';
			send_buffer[14] = '1';break ;
		case state2 :
			send_buffer[12] = '0';
			send_buffer[13] = '1';
			send_buffer[14] = '0';break ;
		case state3 :
			send_buffer[12] = '1';
			send_buffer[13] = '0';
			send_buffer[14] = '0';break ;
		case state0 :
			send_buffer[12] = '0';
			send_buffer[13] = '0';
			send_buffer[14] = '0';break ;
		}
	send_buffer[15]=  '#' ;

	UARTX_Send( SAU0_UART1,send_buffer,send_buffer_size);
}

void iot_update()
{

	tbyte i=0;

	if ((laststate[0] != Options[status])&&(flag==1)) {
		laststate[0] = Options[status] ;

		iot_set();
		flag = 0 ;

	}
	if((lastcount != count)&&(flag==1))
	{
		lastcount = count;
		iot_set();
		flag=0;
	}
	if ((laststate[1] != Options[power])&&(flag==1)) {
		laststate[1] = Options[power] ;
		iot_set();
		flag = 0 ;
	}  if ((laststate[2] != Options[error])&&(flag==1)) {
		laststate[2] = Options[error] ;
		iot_set();
		flag=0;
	}


	/***********************************************************************/

	/* while (i < 13)
	{

        if (recive_string[i] == 'P') {

        	if(flag_powers < 255){
        		flag_powers++ ;
        	}else {
        		flag_powers = 2 ;
        	}
        	if(((laststate[1]+'0')!= recive_string[i+1])&&(flag_powers ==1 ))
        	{

        	if('1' == recive_string[i+1])
        		Options[power] = PWR1;

        	else if('1'==recive_string[i+2])
        		Options[power] = PWR2;

        	else if('1'==recive_string[i+3])
        	        		Options[power] = PWR3;
        	else
        	        		Options[power] = PWR0;

        	if(flag_powers < 255){
        		flag_powers ++ ;
        	        		     }else {
        	        		    	 flag_powers = 2 ;
        	        		     }
        	}
        }




         if (recive_string[i] == 'E') {
        	 if(flag_errors < 255){
        		 flag_errors ++ ;
        	         	}else {
        	         		flag_errors = 2 ;
        	         	}
        	 if(((laststate[2]+'0')!= recive_string[i+1])&&(flag_errors ==1 ))
        	 {
        		 if(flag_errors < 255){
        			 flag_errors ++ ;
        		         		     }else {
        		         		    	flag_errors = 2 ;
        		         		     }
        	if('1'==recive_string[i+1])
        	        	Options[error] = ERR1;

        	else if('1'==recive_string[i+2])
        	        		Options[error] = ERR2;
        	        	else
        	        	        		Options[error] = ERR0;
        }
         }
        if (recive_string[i] == 'S') {
        	if(flag_states < 255){
        		flag_states ++ ;
        	        	}else {
        	        		flag_states = 2 ;
        	        	}
        	if(((laststate[0]+'0')!= recive_string[i+1])&&(flag_states ==1 ))
        	{
        		if(flag_states < 255){
        			flag_states ++ ;
     		     }else {
     		    	flag_states = 2 ;
       		   }
        	if('1'==recive_string[i+1])
        	        	Options[status] = state1;

        	else if('1'==recive_string[i+2])
        	        	Options[status] = state2;

        	else if('1'==recive_string[i+3])
        	        	        		Options[status] = state3;
        	        	else
        	        	        	Options[status] = state0;
        }
        }
        i++;
    }*/
	if(recive_complete) {
		//
		//	   if(recive_string[2] == '1' ){
		//    	 Options[power] = PWR1 ;
		//     }else if(recive_string[3] == '1'){
		//    	 Options[power] = PWR2 ;
		//     }else if(recive_string[4] == '1'){
		//    	 Options[power] = PWR3 ;
		//     }else if (recive_string[2] == '0' && recive_string[3] == '0' &&recive_string[4] == '0'){
		//    	 Options[power] = PWR0  ;
		//     }
		//
		//     if(recive_string[6] == '1'){
		//         	 Options[error] = ERR1 ;
		//          }else if(recive_string[7] == '1'){
		//         	 Options[error] = ERR2 ;
		//          }else if (recive_string[6] == '0' && recive_string[7] == '0' ) {
		//         	 Options[power] = ERR0  ;
		//          }
		//
		//     if(recive_string[9] == '1'){
		//         	 Options[status] = state1 ;
		//          }else if(recive_string[10] == '1'){
		//        	  Options[status] = state2 ;
		//          }else if(recive_string[11] == '1'){
		//        	  Options[status] = state3 ;
		//          }else if (recive_string[11] == '0' && recive_string[10] == '0' &&recive_string[9] == '0') {
		//        	  Options[status] = state0 ; ;
		//          }
		while (i < 13)
		{


			if (recive_string[i] == 'P') {


				if('1' == recive_string[i+1])
					Options[power] = PWR1;

				if('1'==recive_string[i+2])
					Options[power] = PWR2;

				if('1'==recive_string[i+3])
					Options[power] = PWR3;
				if (recive_string[i+3 ] == '0' &&  recive_string[i+2] == '0' && recive_string[i+1] == '0')
					Options[power] = PWR0;
			}

			if (recive_string[i] == 'E') {

				if('1'==recive_string[i+1])
					Options[error] = ERR1;
				if('1'==recive_string[i+2])
					Options[error] = ERR2;
				if(recive_string[i+1] == '0' && recive_string[i+2]=='0')
					Options[error] = ERR0;

			}
			if (recive_string[i] == 'S') {


				if('1'==recive_string[i+1])
					Options[status] = state1;

				if('1'==recive_string[i+2])
					Options[status] = state2;

				if('1'==recive_string[i+3])
					Options[status] = state3;
				if(recive_string[i+1] == '0' && recive_string[i+2] =='0' && recive_string[i+3]=='0')
					Options[status] = state0;
			}

			i++;
		}



		recive_complete = 0 ;
	}
	//   for(iterator=0;iterator<13;iterator++)
	//   {
	//	  recive_string[iterator]=0;
	//  }
}



/*while (i < 20)
			   	{

			           if (buffer_uart1[i] == 'P')
			        	   Options[power]  =buffer_uart1[i+1];

			           else if (buffer_uart1[i] == 'E')
			            	Options[error]=buffer_uart1[i+1];

			           else if (buffer_uart1[i] == 'S')
			        	   Options[status] =buffer_uart1[i+1];
			        	   else{}


			           i++;
			       }*/






