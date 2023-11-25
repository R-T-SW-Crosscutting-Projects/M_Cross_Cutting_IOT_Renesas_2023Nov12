/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include  "MCAL/MCAL_R5F11BBC_MAIN.h"
//#include  "MCAL/MCAL_General_Config.h"
//#include  "MCAL/MCAL_R5F11BBC_Config.h"
//#include  "MCAL/GPIO/MCAL_R5F11BBC_GPIO.h"
#include  "OS/tt_scheduler.h"
#include  "MIDDLEWARE/Middleware.h"

void main(void)
{


	MCU_Config_Init(Hirc_32MHz) ;// inside it GPIO_SAFEGUARD_Init() ;Registers_SAFEGUARD_Init();
	  Global_interrupt_Enable();
	  App_Init();
	  SSD_Init();
	    tt_init(Tick_1_ms);
	    tt_add_task(SSD_Update, 0, 5) ;
	    tt_add_task(Switch_update, 1, 100) ;
	    tt_add_task(Display_Update, 3, 2) ;
	    tt_add_task(PB_Update, 2, 5) ;
	    tt_add_task(iot_update,5,100) ;
	    tt_start();

	  while (1)
	      {
		   WDT_Reset();
		  tt_dispatch_task();


	      }
}
