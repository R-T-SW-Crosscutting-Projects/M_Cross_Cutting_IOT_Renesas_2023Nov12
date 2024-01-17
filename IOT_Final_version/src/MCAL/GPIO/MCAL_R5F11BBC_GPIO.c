/***********************************************************************************************************************
* File Name      : MCAL_R5F11BBC_GPIO.c
* Description    : This file implements device driver for (GPIO)
*  Author         : Sherif Elgiar
*  Tester          :
* Device(s)      : R5F11BBC
* Creation Date: 01/01/2024
* Testing Date  :
* @COPYRIGHT 2016 El-ARABY Research and development center.
* all rights reserved
***********************************************************************************************************************/
/**Includes =====================================================================================================================*/
#include "MCAL_R5F11BBC_GPIO.h"
/**Static Variables =================================================================================================================*/
/**Functions =====================================================================================================================*/
/* @brief :  */
//----------------------------------------------------------------------------------------------
/* @brief :  */
void GPIO_Value_Set(tport port,tpin pin,tbyte value)
{
WDT_Reset();
	switch(port)
	{
		case (Port_0):  { if(value){SET_BIT(P0, pin);}else{CLR_BIT(P0, pin);}}break;
		case (Port_1):  { if(value){SET_BIT(P1, pin);}else{CLR_BIT(P1, pin);}}break;
		case (Port_2):  { if(value){SET_BIT(P2, pin);}else{CLR_BIT(P2, pin);}}break;
		case (Port_3):  { if(value){SET_BIT(P3, pin);}else{CLR_BIT(P3, pin);}}break;
		case (Port_4):  { if(value){SET_BIT(P4, pin);}else{CLR_BIT(P4, pin);}}break;
		case (Port_5):  { if(value){SET_BIT(P5, pin);}else{CLR_BIT(P5, pin);}}break;
		case (Port_7):  { if(value){SET_BIT(P7, pin);}else{CLR_BIT(P7, pin);}}break;
		case (Port_12):{ if(value){SET_BIT(P12, pin);}else{CLR_BIT(P12, pin);}}break;
		case (Port_13):{ if(value){SET_BIT(P13, pin);}else{CLR_BIT(P13, pin);}}break;
		case (Port_14):{ if(value){SET_BIT(P14, pin);}else{CLR_BIT(P14, pin);}}break;

	}
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
tbyte GPIO_Value_Get(tport port,tpin pin)
{
	tbyte  pin_value;
	WDT_Reset();
	switch(port)
	{
		case (Port_0):  { pin_value=GET_BIT(P0,pin);}break;
		case (Port_1):  { pin_value=GET_BIT(P1,pin); }break;
		case (Port_2):  { pin_value=GET_BIT(P2,pin);}break;
		case (Port_3):  { pin_value=GET_BIT(P3,pin);}break;
		case (Port_4):  { pin_value=GET_BIT(P4,pin); }break;
		case (Port_5):  { pin_value=GET_BIT(P5,pin); }break;
		case (Port_7):  { pin_value=GET_BIT(P7,pin); }break;
		case (Port_12):{ pin_value=GET_BIT(P12,pin); }break;
		case (Port_13):{ pin_value=GET_BIT(P13,pin); }break;
		case (Port_14):{ pin_value=GET_BIT(P14,pin); }break;

	}return (pin_value);
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
void GPIO_Value_Tog(tport port,tpin pin)
{
	WDT_Reset();
	switch(port)
	{
   case (Port_0):  { TOG_BIT(P0, pin);}break;
   case (Port_1):  { TOG_BIT(P1, pin); }break;
   case (Port_2):  { TOG_BIT(P2, pin); }break;
   case (Port_3):  { TOG_BIT(P3, pin); }break;
   case (Port_4):  { TOG_BIT(P4, pin); }break;
   case (Port_5):  { TOG_BIT(P5, pin); }break;
   case (Port_7):  { TOG_BIT(P7, pin); }break;
   case (Port_12):{ TOG_BIT(P12, pin); }break;
   case (Port_13):{ TOG_BIT(P13, pin); }break;
   case (Port_14):{ TOG_BIT(P14, pin); }break;
	}
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
t_direction GPIO_Direction_get(tport port,tpin pin)
{
	tbyte pin_direction;
	WDT_Reset();
  	switch(port)
  	{
  		case (Port_0):  {pin_direction=GET_BIT(PM0,pin);}break;
  		case (Port_1):  {pin_direction=GET_BIT(PM1,pin);}break;
  		case (Port_2):  {pin_direction=GET_BIT(PM2,pin);}break;
  		case (Port_3):  {pin_direction=GET_BIT(PM3,pin);}break;
  		case (Port_4):  {pin_direction=GET_BIT(PM4,pin);}break;
  		case (Port_5):  {pin_direction=GET_BIT(PM5,pin);}break;
  		case (Port_7):  {pin_direction=GET_BIT(PM7,pin);}break;
  		case (Port_12):{pin_direction=GET_BIT(PM12,pin);}break;
  		case (Port_14):{pin_direction=GET_BIT(PM14,pin);}break;

  	}
  	return (pin_direction);
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
void GPIO_Output_Init(tport port,tpin pin,tbyte value,t_usage usage)
{
	do
  	   {
      WDT_Reset();
       switch(port)
         {
          case (Port_0):{
        	                   /* Disable pull up Resistor*/CLR_BIT(PU0, pin);
        	                   /*set velue*/ if(value){SET_BIT(P0, pin);}else{CLR_BIT(P0, pin);}
        	                   /*Set Usage*/if(usage==communication_usage){SET_BIT(POM0, pin);}else{CLR_BIT(POM0, pin);}
                                /*set Pin is Output*/CLR_BIT(PM0, pin);
                                }break;
          case (Port_1):{
        	                   /* Disable pull up Resistor*/CLR_BIT(PU1, pin);
        	                   /*set velue*/ if(value){SET_BIT(P1, pin);}else{CLR_BIT(P1, pin);}
        	                   /*Set Usage*/if(usage==communication_usage){SET_BIT(POM1, pin);}else{CLR_BIT(POM1, pin);}
                                /*set Pin is Output*/CLR_BIT(PM1, pin);
                                }break;
          case (Port_2):{
        	                   /* no pull up Resistor*/
        	                   /*set velue*/ if(value){SET_BIT(P2, pin);}else{CLR_BIT(P2, pin);}
        	                   /*just Normal Usage*
        	                     /*set Pin is Output*/CLR_BIT(PM2, pin);
                                }break;
          case (Port_3):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU3, pin);
        	                   /*set velue*/ if(value){SET_BIT(P3, pin);}else{CLR_BIT(P3, pin);}
        	                   /*Set Usage*/if(usage==communication_usage){SET_BIT(POM3, pin);}else{CLR_BIT(POM3, pin);}
                                /*set Pin is Output*/CLR_BIT(PM3, pin);
                                }break;
          case (Port_4):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU4, pin);
        	                   /*set velue*/ if(value){SET_BIT(P4, pin);}else{CLR_BIT(P4, pin);}
        	                    /*just Normal Usage*
        	                     */ /*set Pin is Output*/CLR_BIT(PM4, pin);
                                }break;
          case (Port_5):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU5, pin);
        	                   /*set velue*/ if(value){SET_BIT(P5, pin);}else{CLR_BIT(P5, pin);}
        	                   /*Set Usage*/if(usage==communication_usage){SET_BIT(POM5, pin);}else{CLR_BIT(POM5, pin);}
                                /*set Pin is Output*/CLR_BIT(PM5, pin);
                                }break;
          case (Port_7):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU7, pin);
        	                   /*set velue*/ if(value){SET_BIT(P7, pin);}else{CLR_BIT(P7, pin);}
        	                   /*Set Usage*/if(usage==communication_usage){SET_BIT(POM7, pin);}else{CLR_BIT(POM7, pin);}
                                /*set Pin is Output*/CLR_BIT(PM7, pin);
                                }break;
          case (Port_12):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU12, pin);
        	                   /*set velue*/ if(value){SET_BIT(P12, pin);}else{CLR_BIT(P12, pin);}
        	                   /*just Normal Usage*
                                /*set Pin is Output*/CLR_BIT(PM12, pin);
                                }break;
          case (Port_13):{/*only input case*/}break;
          case (Port_14):{
        	                    /* Disable pull up Resistor*/CLR_BIT(PU14, pin);
        	                   /*set velue*/ if(value){SET_BIT(P14, pin);}else{CLR_BIT(P14, pin);}
        	                   /*just Normal Usage*
                                /*set Pin is Output*/CLR_BIT(PM14, pin);
                                }break;
         }

          }while(GPIO_Direction_get(port,pin)!=output);
}
//----------------------------------------------------------------------------------------------
/* @brief :  */
void GPIO_Input_Init(tport port,tpin pin,t_usage usage)
{
	do
	     {
	WDT_Reset();
	switch(port)
	         {
              case (Port_0):{
	                                /* Enable pull up Resistor*/SET_BIT(PU0, pin);
	                                /*Set Usage*/if(usage==communication_usage){SET_BIT(POM0, pin);}else{CLR_BIT(POM0, pin);}
                                    /*set Pin is Input*/SET_BIT(PM0, pin);
                                   }break;
              case (Port_1):{
	                                /* Enable pull up Resistor*/SET_BIT(PU1, pin);
	                                /*Set Usage*/if(usage==communication_usage){SET_BIT(POM1, pin);}else{CLR_BIT(POM1, pin);}
                                    /*set Pin is Input*/SET_BIT(PM1, pin);
                                   }break;
              case (Port_2):{
            	                    /* no pull up Resistor*/
            	                     /*just Normal Usage*
            	                     /*set Pin is Input*/SET_BIT(PM2, pin);
                                   }break;
              case (Port_3):{
	                                /* Enable pull up Resistor*/SET_BIT(PU3, pin);
	                                /*Set Usage*/if(usage==communication_usage){SET_BIT(POM3, pin);}else{CLR_BIT(POM3, pin);}
                                    /*set Pin is Input*/SET_BIT(PM3, pin);
                                   }break;
              case (Port_4):{
	                                /* Enable pull up Resistor*/SET_BIT(PU4, pin);
	                                /*just Normal Usage*
                                    /*set Pin is Input*/SET_BIT(PM4, pin);
                                   }break;
              case (Port_5):{
	                                /* Enable pull up Resistor*/SET_BIT(PU5, pin);
	                                /*Set Usage*/if(usage==communication_usage){SET_BIT(POM5, pin);}else{CLR_BIT(POM5, pin);}
                                    /*set Pin is Input*/SET_BIT(PM5, pin);
                                   }break;
              case (Port_7):{
	                                /* Enable pull up Resistor*/SET_BIT(PU7, pin);
	                                /*Set Usage*/if(usage==communication_usage){SET_BIT(POM7, pin);}else{CLR_BIT(POM7, pin);}
                                    /*set Pin is Input*/SET_BIT(PM7, pin);
                                   }break;
              case (Port_12):{
	                                /* Enable pull up Resistor*/SET_BIT(PU12, pin);
	                                /*just Normal Usage*
                                    /*set Pin is Input*/SET_BIT(PM12, pin);
                                   }break;
                case (Port_13):{
                                       /* no pull up Resistor*/
                                       /*just Normal Usage*
                                       /*Already is Input*/
                                       }break;
                case (Port_14):{
  	                                /* Enable pull up Resistor*/SET_BIT(PU14, pin);
  	                                /*just Normal Usage*
                                      /*set Pin is Input*/SET_BIT(PM14, pin);
                                     }break;
	         }

	         }while(GPIO_Direction_get(port,pin)!=input);
}
//----------------------------------------------------------------------------------------------


/**END ========================================================================================================================*/
