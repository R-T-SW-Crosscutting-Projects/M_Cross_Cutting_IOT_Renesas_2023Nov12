/***********************************************************************************************************************
 * File Name      : MCAL_R5F11BBC_Config.c																			   *
 * Description    : This file implements device driver for (WDT,CLK,LVR,Sys_Modes)									   *	
 *  Author        : Sherif Elgiar																					   *
 *  Tester        :																									   *
 * Device(s)      : R5F11BBC																						   *	
 * Creation Date: 01/01/2024																						   *	
 * Testing Date  :																									   *
 * @COPYRIGHT 2016 El-ARABY Research and development center.														   *
 * all rights reserved																								   *
 ***********************************************************************************************************************/
/**Includes =====================================================================================================================*/
#include "MCAL_R5F11BBC_Config.h"
/**Static Variables =================================================================================================================*/
static void (* LVD_CallbackPTR)(void) = NULL ;

/**Functions =====================================================================================================================*/

void WDT_Init()
{
    WDTIMK = 1U;    /* disable INTWDTI interrupt */
    WDTIIF = 0U;    /* clear INTWDTI interrupt flag */
    WDTIMK = 0U;    /* enable INTWDTI interrupt */
}

void WDT_Reset()
{
	 WDTE = 0xACU;     /* restart watchdog timer */
}

void WDT_Counter_Stop()
{
	/*WDSTBYON = 0 ,Watchdog timer operation stops*/
	 CLR_BIT(WDT_Mode, 0);
}

void WDT_Counter_Continuo()
{
	/*WDSTBYON = 0 ,Watchdog timer operation stops*/
	SET_BIT(WDT_Mode, 0);
	 WDTE = 0xACU;
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
void onchip_clk_src()
{
	WDT_Reset();
	/* X1, X2 as I/O port */
	 CMC = 0x00U  ;
    /* Set fMX */
    MSTOP = 1U;     /* X1 oscillator/external clock stopped */
    OSMC = 0x10U ; /* low-speed on-chip oscillator clock  */
    /* Set fCLK */
   /* Set fMAIN */
    MCM0 = 0U;      /* selects the high-speed on-chip oscillator clock (fIH) as the main system clock (fMAIN) */
    /* Set fIH */
    HIOSTOP = 0U;   /* high-speed on-chip oscillator operating */
	/*FMain =High Speed On-chip Clock*/
	CKC=0b00000000;
}
void External_Crystal_clk_Frm_1_to_10_Mhz_src()
{
	WDT_Reset();
	/*X1, X2 as crystal/ceramic resonator connection */
	/* 1MHz <= fX <= 10MHz */
	CMC=0b01000000;
	/*FMain =High Speed Ext Crystal*/
	CKC=0b00110000;
}
void External_Crystal_clk_Frm_11_to_20_Mhz_src()
{
	WDT_Reset();
	/*X1, X2 as crystal/ceramic resonator connection */
	/* 10MHz < fX <= 20MHz */
	CMC=0b01000001;
	/*FMain =High Speed Ext Crystal*/
	CKC=0b00110000;
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
void wait_OSC_Clk_to_be_stable()
{
	tbyte stable_set;
	tbyte stable_wait;
	WDT_Reset();
	/* Set fMX */
	    MSTOP = 0U;     /* X1 oscillator/external clock operating */
	    stable_set=0b11111111;//max 260 msec @ 1mhz
	    do
	        {
	    	    stable_wait = OSTC;/*Oscillation stabilization time counter status*/
	    	    stable_wait &= stable_set;/*update stable wait value*/
	        }
	        while (stable_wait != stable_set);/*wait OSC Clk Stable done*/
	    /* Selection of operation clock for real-time clock, low-speed on-chip oscillator clock*/
	    OSMC =(0x10U);
	    /* Set fCLK */
	    /* Set fMAIN */
	    MCM0 = 0U;      /* selects the high-speed on-chip oscillator clock (fIH) as the main system clock (fMAIN) */
	    /* Set fIH */
	    HIOSTOP = 0U;   /* high-speed on-chip oscillator operating */
}
//----------------------------------------------------------------------------------------------
/* @brief : */
void MCU_CLK_Set(t_SYS_Freq Fsys)
{
	WDT_Reset();
	/**** Selection of high-speed on-chip oscillator clock frequency ****/
	
	HOCODIV =0x00 ;		   /* Clear all bits HOCODIV_RESET_VALUE  */
   switch(Fsys)
		{ 
			case Hirc_32MHz:
			
				//OPTION_BYTE |=(1<<FRQSEL3);	            /* set option byte according to freq selection*/
				HOCODIV = 0x00 ;		/* Frequency Set 	*/
				break;
			
			case Hirc_16MHz:
			
				//OPTION_BYTE |=(1<<FRQSEL3);	/* set option byte according to freq selection*/
				HOCODIV = 0b00000001;		/* Frequency Set 	*/
				break;
			
			case Hirc_8MHz:
		
				//OPTION_BYTE |=(1<<FRQSEL3);	/* set option byte according to freq selection*/
				HOCODIV = 0b00000010;		/* Frequency Set 	*/
				break;
			
			
			case Hirc_4MHz:
				//OPTION_BYTE |=(1<<FRQSEL3);	/* set option byte according to freq selection*/
				HOCODIV = 0b00000011;		/* Frequency Set 	*/
				break;
				
			case Hirc_2MHz:
			
				//OPTION_BYTE |=(1<<FRQSEL3);	/* set option byte according to freq selection*/
				HOCODIV= 0b00000100;		/* Frequency Set 	*/
				break;
				
			case Hirc_1MHz:
			
				//OPTION_BYTE |=(1<<FRQSEL3);	/* set option byte according to freq selection*/
				HOCODIV=0b00000101;		/* Frequency Set 	*/
				break;
		}
   onchip_clk_src();
}
//----------------------------------------------------------------------------------------------
/* @brief : */
void LVR_Init(void)
{
	WDT_Reset();
	//LVD_Mode=0b01111111;/*Reset Voltage  @2.75 Volt*/
	 LVIMK = 1U;     /* disable INTLVI interrupt */
     LVIIF = 0U;     /* clear INTLVI interrupt flag */
    /* Set INTLVI high priority */
    LVIPR1 = 0U;
    LVIPR0 = 0U; 
	
}
//----------------------------------------------------------------------------------------------
/* @brief : */
void LVR_INT_Start(void)
{
	LVIIF = 0U;     /* clear INTLVI interrupt flag */
    LVIMK = 0U;     /* enable INTLVI interrupt */
	
}

//----------------------------------------------------------------------------------------------
/* @brief : */
void LVD_SetCallBackFun(void (* Pfun)(void))
{
	LVD_CallbackPTR = Pfun ;
}
//----------------------------------------------------------------------------------------------
/* @brief : */
#pragma interrupt r_lvd_interrupt(vect=INTLVI)
static void __near r_lvd_interrupt(void)
{
    LVD_CallbackPTR() ;
}
//----------------------------------------------------------------------------------------------
/* @brief : */
void MCU_Config_Init(t_SYS_Freq Fsys)
{
	GPIO_SAFEGUARD_Init() ;
	Registers_SAFEGUARD_Init();
	if(Fsys < 10 ){
		MCU_CLK_Set(Fsys);
	}else if (Fsys > 10  && Fsys < 15 ){
		External_Crystal_clk_Frm_1_to_10_Mhz_src() ;
		wait_OSC_Clk_to_be_stable() ;
		
	}else{
		External_Crystal_clk_Frm_11_to_20_Mhz_src();
		wait_OSC_Clk_to_be_stable() ;
	}
	
	WDT_Init();
	LVR_Init();
	LVR_INT_Start() ;
}
//----------------------------------------------------------------------------------------------
/* @brief : */
void Go_to_sleep(t_standby_mode mode)
{
WDT_Reset();
WDT_Counter_Stop();
switch(mode)
          {
           case (halt):{HALT();}break;
           case (stop):{STOP();}break;
          }
}
//---------------------------------------------------------------------------------------------
/* @brief : */
void Sys_wake_up()
{
	WDT_Counter_Continuo();
	WDT_Reset();
}
//---------------------------------------------------------------------------------------------
/* @brief : */
void Global_interrupt_Enable()
{
	EI();
}
void Global_interrupt_Disable()
{
	DI();
}
/**END ========================================================================================================================*/
