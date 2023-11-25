/******************************************************************************************************************************
 File Name      : MCAL_UART.C
 Description    : This file as Source Code for (UART)
 Author         : Ahmed Yasser
 Tester         : Ahmed Magdy
 Device(s)      : R5F11BBC
 Creation Date  : 15/10/2023
 Testing Date   :
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
 *********************************************************************************************************************************/
/* Includes */
#include "MCAL_R5F11BBC_UART.h"
/*==============================================================================================================================*/
/* extern Variables */

/*==============================================================================================================================*/
/*Global variables and functions*
 ***********************************************************************************************************************/
/* Bufeers that used to recieve*/
#define    MAX_STRING_LENGTH       13

volatile tbyte  recive_string[MAX_STRING_LENGTH] ;
volatile tword  string_index = 0 ;
volatile tbyte  recive_complete = 0 ;
tbyte buffer_uart0[SIZE_BUFFER_UART0] ;


tbyte buffer_uart1[SIZE_BUFFER_UART1] ;


tbyte buffer_uart2[SIZE_BUFFER_UART2] ;



volatile tbyte * gp_uart1_tx_address;        /* uart1 transmit buffer address */
volatile tword  g_uart1_tx_count;           /* uart1 transmit data number */
volatile tbyte * gp_uart1_rx_address;        /* uart1 receive buffer address */
volatile tword  g_uart1_rx_count  ;           /* uart1 receive data number */
volatile tword  g_uart1_rx_length;          /* uart1 receive data length */
volatile tbyte * gp_uart2_tx_address;        /* uart2 transmit buffer address */
volatile tword  g_uart2_tx_count;           /* uart2 transmit data number */
volatile tbyte * gp_uart2_rx_address;        /* uart2 receive buffer address */
volatile tword  g_uart2_rx_count;           /* uart2 receive data number */
volatile tword  g_uart2_rx_length;          /* uart2 receive data length */
volatile tbyte * gp_uart0_tx_address;        /* uart0 transmit buffer address */
volatile tword  g_uart0_tx_count;           /* uart0 transmit data number */
volatile tbyte * gp_uart0_rx_address;        /* uart0 receive buffer address */
volatile tword  g_uart0_rx_count;           /* uart0 receive data number */
volatile tword  g_uart0_rx_length;          /* uart0 receive data length */

/*Pragma directive
 ***********************************************************************************************************************/
#pragma interrupt r_uart1_interrupt_send(vect=INTST1)
#pragma interrupt r_uart1_interrupt_receive(vect=INTSR1)
#pragma interrupt r_uart2_interrupt_send(vect=INTST2)
#pragma interrupt r_uart2_interrupt_receive(vect=INTSR2)
#pragma interrupt r_uart0_interrupt_send(vect=INTST0)
#pragma interrupt r_uart0_interrupt_receive(vect=INTSR0)

/*******************************PRIVATE_SECTION******************************************************/
#define _0000_SAU_CK00_fCLK_0                   (0x0000U) /* ck00-fCLK */
#define _0001_SAU_CK00_fCLK_1                   (0x0001U) /* ck00-fCLK/2^1 */
#define _0002_SAU_CK00_fCLK_2                   (0x0002U) /* ck00-fCLK/2^2 */
#define _0003_SAU_CK00_fCLK_3                   (0x0003U) /* ck00-fCLK/2^3 */
#define _0004_SAU_CK00_fCLK_4                   (0x0004U) /* ck00-fCLK/2^4 */
#define _0005_SAU_CK00_fCLK_5                   (0x0005U) /* ck00-fCLK/2^5 */
#define _0006_SAU_CK00_fCLK_6                   (0x0006U) /* ck00-fCLK/2^6 */
#define _0007_SAU_CK00_fCLK_7                   (0x0007U) /* ck00-fCLK/2^7 */
#define _0008_SAU_CK00_fCLK_8                   (0x0008U) /* ck00-fCLK/2^8 */
#define _0009_SAU_CK00_fCLK_9                   (0x0009U) /* ck00-fCLK/2^9 */
#define _000A_SAU_CK00_fCLK_10                  (0x000AU) /* ck00-fCLK/2^10 */
#define _000B_SAU_CK00_fCLK_11                  (0x000BU) /* ck00-fCLK/2^11 */
#define _000C_SAU_CK00_fCLK_12                  (0x000CU) /* ck00-fCLK/2^12 */
#define _000D_SAU_CK00_fCLK_13                  (0x000DU) /* ck00-fCLK/2^13 */
#define _000E_SAU_CK00_fCLK_14                  (0x000EU) /* ck00-fCLK/2^14 */
#define _000F_SAU_CK00_fCLK_15                  (0x000FU) /* ck00-fCLK/2^15 */
/* Section of operation clock (CKm1) (PRSm10,PRSm11,PRSm12,PRSm13,) */
#define _0000_SAU_CK01_fCLK_0                   (0x0000U) /* ck01-fCLK */
#define _0010_SAU_CK01_fCLK_1                   (0x0010U) /* ck01-fCLK/2^1 */
#define _0020_SAU_CK01_fCLK_2                   (0x0020U) /* ck01-fCLK/2^2 */
#define _0030_SAU_CK01_fCLK_3                   (0x0030U) /* ck01-fCLK/2^3 */
#define _0040_SAU_CK01_fCLK_4                   (0x0040U) /* ck01-fCLK/2^4 */
#define _0050_SAU_CK01_fCLK_5                   (0x0050U) /* ck01-fCLK/2^5 */
#define _0060_SAU_CK01_fCLK_6                   (0x0060U) /* ck01-fCLK/2^6 */
#define _0070_SAU_CK01_fCLK_7                   (0x0070U) /* ck01-fCLK/2^7 */
#define _0080_SAU_CK01_fCLK_8                   (0x0080U) /* ck01-fCLK/2^8 */
#define _0090_SAU_CK01_fCLK_9                   (0x0090U) /* ck01-fCLK/2^9 */
#define _00A0_SAU_CK01_fCLK_10                  (0x00A0U) /* ck01-fCLK/2^10 */
#define _00B0_SAU_CK01_fCLK_11                  (0x00B0U) /* ck01-fCLK/2^11 */
#define _00C0_SAU_CK01_fCLK_12                  (0x00C0U) /* ck01-fCLK/2^12 */
#define _00D0_SAU_CK01_fCLK_13                  (0x00D0U) /* ck01-fCLK/2^13 */
#define _00E0_SAU_CK01_fCLK_14                  (0x00E0U) /* ck01-fCLK/2^14 */
#define _00F0_SAU_CK01_fCLK_15                  (0x00F0U) /* ck01-fCLK/2^15 */

/*
    Serial mode register mn (SMRmn)
 */
/* Selection of operation clock (fMCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CK00             (0x0000U) /* operation clock CKm0 set by the SPSm register */
#define _8000_SAU_CLOCK_SELECT_CK01             (0x8000U) /* operation clock CKm1 set by the SPSm register */
/* Selection of transfer clock (fTCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS                (0x0000U) /* divided operation clock fMCK specified by the CKSmn bit */
#define _4000_SAU_CLOCK_MODE_TI0N               (0x4000U) /* clock input fSCK from the SCKp pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE              (0x0000U) /* only software trigger is valid (selected for CSI, UART transmission, and simplified I2C) */
#define _0100_SAU_TRIGGER_RXD                   (0x0100U) /* valid edge of the RxDq pin (selected for UART reception) */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALL                     (0x0000U) /* falling edge is detected as the start bit.
The input communication data is captured as is */
#define _0040_SAU_EDGE_RISING                   (0x0040U) /* rising edge is detected as the start bit.
The input communication data is inverted and captured */
/* Setting of operation mode of channel n (MDmn2,MDmn1) */
#define _0000_SAU_MODE_CSI                      (0x0000U) /* CSI mode */
#define _0002_SAU_MODE_UART                     (0x0002U) /* UART mode */
#define _0004_SAU_MODE_IIC                      (0x0004U) /* simplified I2C mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END                  (0x0000U) /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY                  (0x0001U) /* buffer empty interrupt */

/*
    Serial communication operation setting register mn (SCRmn)
 */
/* Setting of operation mode of channel n (TXEmn,RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION             (0x0000U) /* disable communication */
#define _4000_SAU_RECEPTION                     (0x4000U) /* reception only */
#define _8000_SAU_TRANSMISSION                  (0x8000U) /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION        (0xC000U) /* transmission/reception */
/* Selection of data and clock phase in CSI mode (DAPmn,CKPmn) */
#define _0000_SAU_TIMING_1                      (0x0000U) /* type 1 */
#define _1000_SAU_TIMING_2                      (0x1000U) /* type 2 */
#define _2000_SAU_TIMING_3                      (0x2000U) /* type 3 */
#define _3000_SAU_TIMING_4                      (0x3000U) /* type 4 */
/* Mask control of error interrupt signal (INTSREx (x = 0 to 3)) (EOCmn) */
#define _0000_SAU_INTSRE_MASK                   (0x0000U) /* disables generation of error interrupt INTSREx (INTSRx is generated) */
#define _0400_SAU_INTSRE_ENABLE                 (0x0400U) /* enables generation of error interrupt INTSREx (INTSRx is not generated if an error occurs) */
/* Setting of parity bit in UART mode (PTCmn1,PTCmn0) */
#define _0000_SAU_PARITY_NONE                   (0x0000U) /* none parity */
#define _0100_SAU_PARITY_ZERO                   (0x0100U) /* zero parity */
#define _0200_SAU_PARITY_EVEN                   (0x0200U) /* even parity */
#define _0300_SAU_PARITY_ODD                    (0x0300U) /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB                           (0x0000U) /* inputs/outputs data with MSB first */
#define _0080_SAU_LSB                           (0x0080U) /* inputs/outputs data with LSB first */
/* Setting of stop bit in UART mode (SLCmn1,SLCmn0) */
#define _0000_SAU_STOP_NONE                     (0x0000U) /* no stop bit */
#define _0010_SAU_STOP_1                        (0x0010U) /* 1 Stop bit length = 1 bit */
#define _0020_SAU_STOP_2                        (0x0020U) /* stop bit length = 2 bits (mn = 00,02,10 only) */
/* Setting of data length in CSI and UART modes (DLSmn1,DLSmn0) */
#define _0001_SAU_LENGTH_9                      (0x0001U) /* 9-bit data length */
#define _0002_SAU_LENGTH_7                      (0x0002U) /* 7-bit data length */
#define _0003_SAU_LENGTH_8                      (0x0003U) /* 8-bit data length */

/*
    Serial flag clear trigger register mn (SIRmn)
 */
/* Clear trigger of framing error of channel n (FECTmn) */
#define _0004_SAU_SIRMN_FECTMN                  (0x0004U) /* clears the FEFmn bit of the SSRmn register to 0 */
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0002_SAU_SIRMN_PECTMN                  (0x0002U) /* clears the PEFmn bit of the SSRmn register to 0 */
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0001_SAU_SIRMN_OVCTMN                  (0x0001U) /* clears the OVFmn bit of the SSRmn register to 0 */

/*
    Serial status register mn (SSRmn)
 */
/* Communication status indication flag of channel n (TSFmn) */
#define _0040_SAU_UNDER_EXECUTE                 (0x0040U) /* communication is in progress */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0020_SAU_VALID_STORED                  (0x0020U) /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0004_SAU_FRAM_ERROR                    (0x0004U) /* an error occurs (during UART reception) */
/* Parity error detection flag of channel n (PEFmn) */
#define _0002_SAU_PARITY_ERROR                  (0x0002U) /* an error occurs (during UART reception) or ACK is not detected (during I2C transmission) */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0001_SAU_OVERRUN_ERROR                 (0x0001U) /* an overrun error occurs */

/*
    Serial channel start register m (SSm)
 */
/* Operation start trigger of channel 3 (SSm3) */
#define _0000_SAU_CH3_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0008_SAU_CH3_START_TRG_ON              (0x0008U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 2 (SSm2) */
#define _0000_SAU_CH2_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0004_SAU_CH2_START_TRG_ON              (0x0004U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SAU_CH1_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON              (0x0002U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SAU_CH0_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON              (0x0001U) /* sets the SEmn bit to 1 and enters the communication wait status */

/*
    Format of Serial channel stop register m (STm)
 */
/* Operation stop trigger of channel 3 (STm3) */
#define _0000_SAU_CH3_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_SAU_CH3_STOP_TRG_ON               (0x0008U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 2 (STm2) */
#define _0000_SAU_CH2_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_SAU_CH2_STOP_TRG_ON               (0x0004U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON               (0x0002U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON               (0x0001U) /* clears the SEmn bit to 0 and stops the communication operation */

/*
    Serial channel enable status register m (SEm)
 */
/* Indication of operation enable/stop status of channel 3 (SEm3) */
#define _0000_SAU_CH3_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0008_SAU_CH3_STATUS_ENABLE             (0x0008U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 2 (SEm2) */
#define _0000_SAU_CH2_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0004_SAU_CH2_STATUS_ENABLE             (0x0004U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 (SEm1) */
#define _0000_SAU_CH1_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0002_SAU_CH1_STATUS_ENABLE             (0x0002U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 0 (SEm0) */
#define _0000_SAU_CH0_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0001_SAU_CH0_STATUS_ENABLE             (0x0001U) /* operation is enabled */

/*
    Serial output enable register m (SOEm)
 */
/* Serial output enable/stop of channel 3 (SOEm3) */
#define _0000_SAU_CH3_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0008_SAU_CH3_OUTPUT_ENABLE             (0x0008U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 2 (SOEm2) */
#define _0000_SAU_CH2_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0004_SAU_CH2_OUTPUT_ENABLE             (0x0004U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 1 (SOEm1) */
#define _0000_SAU_CH1_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0002_SAU_CH1_OUTPUT_ENABLE             (0x0002U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 0 (SOEm0) */
#define _0000_SAU_CH0_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0001_SAU_CH0_OUTPUT_ENABLE             (0x0001U) /* enables output by serial communication operation */

/*
    Serial output register m (SOm)
 */
/* Serial clock output of channel 3 (CKOm3) */
#define _0000_SAU_CH3_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0800_SAU_CH3_CLOCK_OUTPUT_1            (0x0800U) /* serial clock output value is 1 */
/* Serial clock output of channel 2 (CKOm2) */
#define _0000_SAU_CH2_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0400_SAU_CH2_CLOCK_OUTPUT_1            (0x0400U) /* serial clock output value is 1 */
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1            (0x0200U) /* serial clock output value is 1 */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1            (0x0100U) /* serial clock output value is 1 */
/* Serial data output of channel 3 (SOm3) */
#define _0000_SAU_CH3_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0008_SAU_CH3_DATA_OUTPUT_1             (0x0008U) /* serial data output value is 1 */
/* Serial data output of channel 2 (SOm2) */
#define _0000_SAU_CH2_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0004_SAU_CH2_DATA_OUTPUT_1             (0x0004U) /* serial data output value is 1 */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0002_SAU_CH1_DATA_OUTPUT_1             (0x0002U) /* serial data output value is 1 */
/* Serial data output of channel 0 (SOm0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0001_SAU_CH0_DATA_OUTPUT_1             (0x0001U) /* serial data output value is 1 */

/*
    Serial output level register m (SOLm)
 */
/* Selects inversion of the level of the transmit data of channel n in UART mode (SOLm2) */
#define _0000_SAU_CHANNEL2_NORMAL               (0x0000U) /* communication data is output as is */
#define _0004_SAU_CHANNEL2_INVERTED             (0x0004U) /* communication data is inverted and output */
/* Selects inversion of the level of the transmit data of channel n in UART mode (SOLm0) */
#define _0000_SAU_CHANNEL0_NORMAL               (0x0000U) /* communication data is output as is */
#define _0001_SAU_CHANNEL0_INVERTED             (0x0001U) /* communication data is inverted and output */

/*
    Serial standby control register m (SSCm)
 */
/* Selection of whether to enable or disable the generation of communication error interrupts in the
SNOOZE mode (SSECm) */
#define _0000_SAU_INTSRE0_ENABLE                (0x0000U) /* enable the generation of error interrupts (INTSRE0/INTSRE2) */
#define _0002_SAU_INTSRE0_DISABLE               (0x0002U) /* disable the generation of error interrupts (INTSRE0/INTSRE2) */
/* Setting of the SNOOZE mode (SWCm) */
#define _0000_SAU_CH0_SNOOZE_OFF                (0x0000U) /* do not use the SNOOZE mode function */
#define _0001_SAU_CH0_SNOOZE_ON                 (0x0001U) /* use the SNOOZE mode function */

/*
    Input switch control register (ISC)
 */
/* Channel 0 SSI00 input setting in CSI communication and slave mode (SSIE00) */
#define _00_SAU_SSI00_UNUSED                    (0x00U) /* disables SSI00 pin input */
#define _80_SAU_SSI00_USED                      (0x80U) /* enables SSI00 pin input */
/* Switching channel 3 input of timer array unit 0 (ISC1) */
#define _00_SAU_TI03_INPUT                      (0x00U) /* uses the input signal of the TI03 pin as a timer input (normal operation) */
#define _02_SAU_RxD0_INPUT                      (0x02U) /* input signal of the RxD0 pin is used as timer input */
/* Switching external interrupt (INTP0) input (ISC0) */
#define _00_SAU_INTP0_INTERRUPT                 (0x00U) /* uses the input signal of the INTP0 pin as an external interrupt (normal operation) */
#define _01_SAU_RxD0_INTERRUPT                  (0x01U) /* uses the input signal of the RxD0 pin as an external interrupt (wakeup signal detection) */

/*
    Noise filter enable register 0 (NFEN0)
 */
/* Use of noise filter of RxD2 pin (SNFEN20) */
#define _00_SAU_RXD2_FILTER_OFF                 (0x00U) /* noise filter off */
#define _10_SAU_RXD2_FILTER_ON                  (0x10U) /* noise filter on */
/* Use of noise filter of RxD1 pin (SNFEN10) */
#define _00_SAU_RXD1_FILTER_OFF                 (0x00U) /* noise filter off */
#define _04_SAU_RXD1_FILTER_ON                  (0x04U) /* noise filter on */
/* Use of noise filter of RxD0 pin (SNFEN00) */
#define _00_SAU_RXD0_FILTER_OFF                 (0x00U) /* noise filter off */
#define _01_SAU_RXD0_FILTER_ON                  (0x01U) /* noise filter on */


/* SAU used flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR           (0x00U)
#define _01_SAU_IIC_SEND_FLAG                   (0x01U)
#define _02_SAU_IIC_RECEIVE_FLAG                (0x02U)
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG         (0x04U)

#define _CE00_SAU0_CH0_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _CE00_SAU0_CH2_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _CE00_SAU0_CH3_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _CE00_SAU0_CH1_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _0020_SMR00_DEFAULT_VALUE               (0x0020U) /* SMR00 default value */
#define _0020_SMR02_DEFAULT_VALUE               (0x0020U) /* SMR02 default value */
#define _0020_SMR03_DEFAULT_VALUE               (0x0020U) /* SMR03 default value */
#define _0004_SCR00_DEFAULT_VALUE               (0x0004U) /* SCR00 default value */
#define _0004_SCR02_DEFAULT_VALUE               (0x0004U) /* SCR02 default value */
#define _0004_SCR03_DEFAULT_VALUE               (0x0004U) /* SCR03 default value */
#define _CE00_SAU1_CH0_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _CE00_SAU1_CH1_BAUDRATE_DIVISOR         (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _0020_SMR10_DEFAULT_VALUE               (0x0020U) /* SMR10 default value */
#define _0020_SMR11_DEFAULT_VALUE               (0x0020U) /* SMR11 default value */
#define _0004_SCR10_DEFAULT_VALUE               (0x0004U) /* SCR10 default value */
#define _0004_SCR11_DEFAULT_VALUE               (0x0004U) /* SCR11 default value */
#define _0020_SMR01_DEFAULT_VALUE               (0x0020U) /* SMR01 default value */
#define _0004_SCR01_DEFAULT_VALUE               (0x0004U) /* SCR01 default value */
#define _0C0C_SO1_DEFAULT_VALUE                 (0x0C0CU) /* SO1 default value */




/*******************************END_PRIVATE_SECTION**************************************************/

/***********************************************************************************************************************
 * Function Name: SAUX_Init
 * Description  : This function initializes the SAUX module.
 * Arguments    : t_UART_Select UART_Num , t_Baud_Rate BAUD
 * Return Value : None
 ***********************************************************************************************************************/
void SAUX_Init(t_UART_Select UART_Num, t_Baud_Rate BAUD)
{
	WDT_Reset();
    switch (UART_Num)
    {
    case SAU0_UART1:
        SAU0EN = 1U; /* enables input clock supply */
        NOP();
        NOP();
        NOP();
        NOP();
        switch (F_CPU_Mhz)
        {
        case 32:
            switch (BAUD)
            {
            case B_4800:
                SPS0 = _0050_SAU_CK01_fCLK_5 | _0005_SAU_CK00_fCLK_5;
                break;
            case B_9600:
                SPS0 = _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                break;
            case B_19200:
                SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            }
            break;
        case 16:
            switch (BAUD)
            {
            case B_4800:
                SPS0 = _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                break;
            case B_9600:
                SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            case B_19200:
                SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            }
            break;
        case 8:
            switch (BAUD)
            {
            case B_4800:
                SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            case B_9600:
                SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            case B_19200:
                SPS0 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                break;
            }
            break;
        case 4:
            switch (BAUD)
            {
            case B_4800:
                SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            case B_9600:
                SPS0 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                break;
            case B_19200:
                SPS0 = _0000_SAU_CK01_fCLK_0 | _0000_SAU_CK00_fCLK_0;
                break;
            }
            break;
        }
        break;

    case SAU1_UART2:
        SAU1EN = 1U; /* enables input clock supply */
        NOP();
        NOP();
        NOP();
        NOP();
        switch (F_CPU_Mhz)
        {
        case 32:
            switch (BAUD)
            {
            case B_4800:
                SPS1 = _0050_SAU_CK01_fCLK_5 | _0005_SAU_CK00_fCLK_5;
                break;
            case B_9600:
                SPS1 = _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                break;
            case B_19200:
                SPS1 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            }
            break;
        case 16:
            switch (BAUD)
            {
            case B_4800:
                SPS1 = _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                break;
            case B_9600:
                SPS1 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            case B_19200:
                SPS1 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            }
            break;
        case 8:
            switch (BAUD)
            {
            case B_4800:
                SPS1 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                break;
            case B_9600:
                SPS1 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            case B_19200:
                SPS1 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                break;
            }
            break;
        case 4:
            switch (BAUD)
            {
            case B_4800:
                SPS1 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                break;
            case B_9600:
                SPS1 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                break;
            case B_19200:
                SPS1 = _0000_SAU_CK01_fCLK_0 | _0000_SAU_CK00_fCLK_0;
                break;
            }
            break;
        }
        break;

        case SAU0_UART0:
        	    SAU0EN = 1U; /* enables input clock supply */
                NOP();
                NOP();
                NOP();
                NOP();
                switch (F_CPU_Mhz)
                {
                case 32:
                    switch (BAUD)
                    {
                    case B_4800:
                        SPS0 = _0050_SAU_CK01_fCLK_5 | _0005_SAU_CK00_fCLK_5;
                        break;
                    case B_9600:
                        SPS0= _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                        break;
                    case B_19200:
                        SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                        break;
                    }
                    break;
                case 16:
                    switch (BAUD)
                    {
                    case B_4800:
                        SPS0 = _0040_SAU_CK01_fCLK_4 | _0004_SAU_CK00_fCLK_4;
                        break;
                    case B_9600:
                        SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                        break;
                    case B_19200:
                        SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                        break;
                    }
                    break;
                case 8:
                    switch (BAUD)
                    {
                    case B_4800:
                        SPS0 = _0030_SAU_CK01_fCLK_3 | _0003_SAU_CK00_fCLK_3;
                        break;
                    case B_9600:
                        SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                        break;
                    case B_19200:
                        SPS0 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                        break;
                    }
                    break;
                case 4:
                    switch (BAUD)
                    {
                    case B_4800:
                        SPS0 = _0020_SAU_CK01_fCLK_2 | _0002_SAU_CK00_fCLK_2;
                        break;
                    case B_9600:
                        SPS0 = _0010_SAU_CK01_fCLK_1 | _0001_SAU_CK00_fCLK_1;
                        break;
                    case B_19200:
                        SPS0 = _0000_SAU_CK01_fCLK_0 | _0000_SAU_CK00_fCLK_0;
                        break;
                    }
                    break;
                }
                break;
    }
}

/***********************************************************************************************************************
 * Function Name: UARTX_Init
 * Description  : This function initializes the UARTX module.
 * Arguments    : t_UART_Select UART_Num , t_UART_Status STATUS , t_Baud_Rate BAUD ,t_Parity Parity , t_Transfer_Direction Direction ,t_Stop_Bit STOP ,t_Data_Lenght Lenght
 * Return Value : None
 ***********************************************************************************************************************/
void UARTX_Init(t_UART_Select UART_Num , t_Baud_Rate BAUD ,t_Parity Parity , t_Transfer_Direction Direction ,t_Stop_Bit STOP ,t_Data_Lenght Lenght)
{
	WDT_Reset();
	SAUX_Init(UART_Num, BAUD) ;

	switch(UART_Num)
	{
	        case SAU0_UART1 :
		    ST0 |= _0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON;
			STMK1 = 1U;     /* disable INTST1 interrupt */
			STIF1 = 0U;     /* clear INTST1 interrupt flag */
			SRMK1 = 1U;     /* disable INTSR1 interrupt */
			SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
			SREMK1 = 1U;    /* disable INTSRE1 interrupt */
			SREIF1 = 0U;    /* clear INTSRE1 interrupt flag */
			/* Set INTSR1 low priority */
			SRPR11 = 1U;
			SRPR01 = 1U;
			/* Set INTST1 low priority */
			STPR11 = 1U;
			STPR01 = 1U;
			SMR02 = _0020_SMR02_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
					_0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

			SCR02 = _0004_SCR02_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
	        switch(Parity)
	        {
	        case NONE_parity: SCR02|=_0000_SAU_PARITY_NONE;break;
	        case ZERO:        SCR02|=_0100_SAU_PARITY_ZERO;break;
	        case ODD:         SCR02|=_0300_SAU_PARITY_ODD;break;
	        case EVEN:        SCR02|=_0200_SAU_PARITY_EVEN;break;
	        }

            switch(Direction)
            {
            case LSB :SCR02|=_0080_SAU_LSB;break;
            case MSB :SCR02|=_0000_SAU_MSB;break;
            }

			switch(STOP){
			case NONE_stop: SCR02|=_0000_SAU_STOP_NONE;     break;
			case ONE_stop  :     SCR02|=_0010_SAU_STOP_1;        break;
			case TWO_stop :     SCR02|=_0020_SAU_STOP_2;        break;
			}
			switch(Lenght){
			case L7: SCR02|=_0002_SAU_LENGTH_7;break;
			case L8: SCR02|=_0003_SAU_LENGTH_8;break;
			case L9: SCR02|=_0001_SAU_LENGTH_9;break;
			}
	SDR02 = _CE00_SAU0_CH2_BAUDRATE_DIVISOR;

	NFEN0 |= _04_SAU_RXD1_FILTER_ON;
	SIR03 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
	SMR03 = _0020_SMR03_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
			_0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

	SCR03 = _0004_SCR03_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
    switch(Parity)
	        {
	        case NONE_parity: SCR03|=_0000_SAU_PARITY_NONE;break;
	        case ZERO:        SCR03|=_0100_SAU_PARITY_ZERO;break;
	        case ODD:         SCR03|=_0300_SAU_PARITY_ODD;break;
	        case EVEN:        SCR03|=_0200_SAU_PARITY_EVEN;break;
	        }

            switch(Direction)
            {
            case LSB :SCR03|=_0080_SAU_LSB;break;
            case MSB :SCR03|=_0000_SAU_MSB;break;
            }

			switch(STOP){
			case NONE_stop: SCR03|=_0000_SAU_STOP_NONE;     break;
			case ONE_stop  :     SCR03|=_0010_SAU_STOP_1;        break;
			case TWO_stop  :     SCR03|=_0020_SAU_STOP_2;        break;
			}
			switch(Lenght){
			case L7: SCR03|=_0002_SAU_LENGTH_7;break;
			case L8: SCR03|=_0003_SAU_LENGTH_8;break;
			case L9: SCR03|=_0001_SAU_LENGTH_9;break;
			}

	SDR03 = _CE00_SAU0_CH3_BAUDRATE_DIVISOR;
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;
	SOL0 &= (tword)~_0004_SAU_CHANNEL2_INVERTED;
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;
	/* Set RxD1 pin */
	PMC0 &= 0xFDU;
	PM0 |= 0x02U;
	/* Set TxD1 pin */
	PMC0 &= 0xFEU;
	P0 |= 0x01U;
	PM0 &= 0xFEU;
break;

	case SAU1_UART2 :

    ST1 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
	STMK2 = 1U;     /* disable INTST2 interrupt */
	STIF2 = 0U;     /* clear INTST2 interrupt flag */
	SRMK2 = 1U;     /* disable INTSR2 interrupt */
	SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
	SREMK2 = 1U;    /* disable INTSRE2 interrupt */
	SREIF2 = 0U;    /* clear INTSRE2 interrupt flag */
	/* Set INTSR2 low priority */
	SRPR12 = 1U;
	SRPR02 = 1U;
	/* Set INTST2 low priority */
	STPR12 = 1U;
	STPR02 = 1U;

	SMR10 = _0020_SMR10_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
			_0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

	SCR10 = _0004_SCR10_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
	switch(Parity)
		        {
		        case NONE_parity: SCR10|=_0000_SAU_PARITY_NONE;break;
		        case ZERO:        SCR10|=_0100_SAU_PARITY_ZERO;break;
		        case ODD:         SCR10|=_0300_SAU_PARITY_ODD;break;
		        case EVEN:        SCR10|=_0200_SAU_PARITY_EVEN;break;
		        }

	            switch(Direction)
	            {
	            case LSB :SCR10|=_0080_SAU_LSB;break;
	            case MSB :SCR10|=_0000_SAU_MSB;break;
	            }

				switch(STOP){
				case NONE_stop: SCR10|=_0000_SAU_STOP_NONE;     break;
				case ONE_stop  :     SCR10|=_0010_SAU_STOP_1;        break;
				case TWO_stop  :     SCR10|=_0020_SAU_STOP_2;        break;
				}
				switch(Lenght){
				case L7: SCR10|=_0002_SAU_LENGTH_7;break;
				case L8: SCR10|=_0003_SAU_LENGTH_8;break;
				case L9: SCR10|=_0001_SAU_LENGTH_9;break;
				}
	SDR10 = _CE00_SAU1_CH0_BAUDRATE_DIVISOR;
	NFEN0 |= _10_SAU_RXD2_FILTER_ON;
	SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
	SMR11 = _0020_SMR11_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
			_0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

	SCR11 = _0004_SCR11_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
	switch(Parity)
	        {
	        case NONE_parity: SCR11|=_0000_SAU_PARITY_NONE;break;
	        case ZERO:        SCR11|=_0100_SAU_PARITY_ZERO;break;
	        case ODD:         SCR11|=_0300_SAU_PARITY_ODD;break;
	        case EVEN:        SCR11|=_0200_SAU_PARITY_EVEN;break;
	        }

            switch(Direction)
            {
            case LSB :SCR11|=_0080_SAU_LSB;break;
            case MSB :SCR11|=_0000_SAU_MSB;break;
            }

			switch(STOP){
			case NONE_stop: SCR11|=_0000_SAU_STOP_NONE;     break;
			case ONE_stop  :     SCR11|=_0010_SAU_STOP_1;        break;
			case TWO_stop :     SCR11|=_0020_SAU_STOP_2;        break;
			}
			switch(Lenght){
			case L7: SCR11|=_0002_SAU_LENGTH_7;break;
			case L8: SCR11|=_0003_SAU_LENGTH_8;break;
			case L9: SCR11|=_0001_SAU_LENGTH_9;break;
			}


	SDR11 = _CE00_SAU1_CH1_BAUDRATE_DIVISOR;
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
	SOL1 &= (tword)~_0001_SAU_CHANNEL0_INVERTED;
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;
	/* Set RxD2 pin */
	PMC1 &= 0xEFU;
	PM1 |= 0x10U;
	/* Set TxD2 pin */
	PMC1 &= 0xF7U;
	P1 |= 0x08U;
	PM1 &= 0xF7U;
	break;

	case SAU0_UART0 :
		    ST0 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
		    STMK0 = 1U;     /* disable INTST0 interrupt */
		    STIF0 = 0U;     /* clear INTST0 interrupt flag */
		    SRMK0 = 1U;     /* disable INTSR0 interrupt */
		    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
		    SREMK0 = 1U;    /* disable INTSRE0 interrupt */
		    SREIF0 = 0U;    /* clear INTSRE0 interrupt flag */
		    /* Set INTSR0 low priority */
		    SRPR10 = 1U;
		    SRPR00 = 1U;
		    /* Set INTST0 low priority */
		    STPR10 = 1U;
		    STPR00 = 1U;

		    SMR00 = _0020_SMR00_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
		            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

		    SCR00 = _0004_SCR00_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
		    switch(Parity)
		    		        {
		    		        case NONE_parity: SCR00|=_0000_SAU_PARITY_NONE;break;
		    		        case ZERO:        SCR00|=_0100_SAU_PARITY_ZERO;break;
		    		        case ODD:         SCR00|=_0300_SAU_PARITY_ODD;break;
		    		        case EVEN:        SCR00|=_0200_SAU_PARITY_EVEN;break;
		    		        }

		    	            switch(Direction)
		    	            {
		    	            case LSB :SCR00|=_0080_SAU_LSB;break;
		    	            case MSB :SCR00|=_0000_SAU_MSB;break;
		    	            }

		    				switch(STOP){
		    				case NONE_stop: SCR00|=_0000_SAU_STOP_NONE;     break;
		    				case ONE_stop  :     SCR00|=_0010_SAU_STOP_1;        break;
		    				case TWO_stop  :     SCR00|=_0020_SAU_STOP_2;        break;
		    				}
		    				switch(Lenght){
		    				case L7: SCR00|=_0002_SAU_LENGTH_7;break;
		    				case L8: SCR00|=_0003_SAU_LENGTH_8;break;
		    				case L9: SCR00|=_0001_SAU_LENGTH_9;break;//always 9 bit in uart 0
		    				//default ://SCR00|=_0001_SAU_LENGTH_9;break;
		    				}

		    SDR00 = _CE00_SAU0_CH0_BAUDRATE_DIVISOR;
		    NFEN0 |= _01_SAU_RXD0_FILTER_ON;
		    SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
		    SMR01 = _0020_SMR01_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
		            _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;

		    SCR01 = _0004_SCR01_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK ;
		    switch(Parity)
		    	        {
		    	        case NONE_parity: SCR01|=_0000_SAU_PARITY_NONE;break;
		    	        case ZERO:        SCR01|=_0100_SAU_PARITY_ZERO;break;
		    	        case ODD:         SCR01|=_0300_SAU_PARITY_ODD;break;
		    	        case EVEN:        SCR01|=_0200_SAU_PARITY_EVEN;break;
		    	        }

		                switch(Direction)
		                {
		                case LSB :SCR01|=_0080_SAU_LSB;break;
		                case MSB :SCR01|=_0000_SAU_MSB;break;
		                }

		    			switch(STOP){
		    			case NONE_stop: SCR01|=_0000_SAU_STOP_NONE;     break;
		    			case ONE_stop  :     SCR01|=_0010_SAU_STOP_1;        break;
		    			case TWO_stop  :     SCR01=_0020_SAU_STOP_2;        break;
		    			}
		    			switch(Lenght){
		    		    case L7: SCR01|=_0002_SAU_LENGTH_7;break;
		    			case L8: SCR01|=_0003_SAU_LENGTH_8;break;
		    			case L9: SCR01|=_0001_SAU_LENGTH_9;break;//always 9 bits in uart0
		    			//default :SCR00|=_0001_SAU_LENGTH_9;break;
		    			}

		    SDR01 = _CE00_SAU0_CH1_BAUDRATE_DIVISOR;
		    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
		    SOL0 &= (tword)~_0001_SAU_CHANNEL0_INVERTED;
		    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;
		    /* Set RxD0 pin */
		    PM5 |= 0x01U;
		    /* Set TxD0 pin */
		    P5 |= 0x02U;
		    PM5 &= 0xFDU;
		    break;
}
}
/***********************************************************************************************************************
 * Function Name: UARTX_Enable
 * Description  : This function starts the UARTX module operation.
 * Arguments    : t_UART_Select Uart_num
 * Return Value : None
 ***********************************************************************************************************************/

void UARTX_Enable(t_UART_Select Uart_Num)
{
	WDT_Reset();
	switch(Uart_Num)
	{
	case SAU0_UART1:
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;
	SS0 |= _0008_SAU_CH3_START_TRG_ON | _0004_SAU_CH2_START_TRG_ON;
	STIF1 = 0U;     /* clear INTST1 interrupt flag */
	SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
	STMK1 = 0U;     /* enable INTST1 interrupt */
	SRMK1 = 0U;     /* enable INTSR1 interrupt */
    break;

	case SAU1_UART2:
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;
	SS1 |= _0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON;
	STIF2 = 0U;     /* clear INTST2 interrupt flag */
	SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
	STMK2 = 0U;     /* enable INTST2 interrupt */
	SRMK2 = 0U;     /* enable INTSR2 interrupt */
    break;

	case SAU0_UART0:
		    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
		    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;
		    SS0 |= _0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON;
		    STIF0 = 0U;     /* clear INTST0 interrupt flag */
		    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
		    STMK0 = 0U;     /* enable INTST0 interrupt */
		    SRMK0 = 0U;     /* enable INTSR0 interrupt */
	break;
   }
}
/***********************************************************************************************************************
 * Function Name: UARTX_Disable
 * Description  : This function stops the UARTX module operation.
 * Arguments    : t_UART_Select Uart_Num
 * Return Value : None
 ***********************************************************************************************************************/
void UARTX_Disable(t_UART_Select Uart_Num)
{
	WDT_Reset();
	switch(Uart_Num)
	{

	case SAU0_UART1 :
	STMK1 = 1U;     /* disable INTST1 interrupt */
	SRMK1 = 1U;     /* disable INTSR1 interrupt */
	ST0 |= _0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON;
	SOE0 &= (tword)~_0004_SAU_CH2_OUTPUT_ENABLE;
	STIF1 = 0U;     /* clear INTST1 interrupt flag */
	SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
	break ;

	case SAU1_UART2 :
		STMK2 = 1U;     /* disable INTST2 interrupt */
		SRMK2 = 1U;     /* disable INTSR2 interrupt */
		ST1 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
		SOE1 &= (tword)~_0001_SAU_CH0_OUTPUT_ENABLE;
		STIF2 = 0U;     /* clear INTST2 interrupt flag */
		SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
		break ;

	case SAU0_UART0:
		    STMK0 = 1U;     /* disable INTST0 interrupt */
		    SRMK0 = 1U;     /* disable INTSR0 interrupt */
		    ST0 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
		    SOE0 &= (tword)~_0001_SAU_CH0_OUTPUT_ENABLE;
		    STIF0 = 0U;     /* clear INTST0 interrupt flag */
		    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
		   break;
	}
}



/***********************************************************************************************************************
 * Function Name: UARTX_Send
 * Description  : This function sends UARTX data.
 * Arguments    : tx_buf -
 *                    transfer buffer pointer
 *                tx_num -
 *                    buffer size
 *               t_UART_Select UART_Num
 * Return Value : status -
 *                    MD_OK or MD_ARGERROR
 ***********************************************************************************************************************/
void UARTX_Send(t_UART_Select UART_Num,tbyte * const tx_buf, tword tx_num)
{
	    WDT_Reset();
		switch (UART_Num){
		case SAU0_UART1 :
			gp_uart1_tx_address = tx_buf;
			g_uart1_tx_count = tx_num;
			STMK1 = 1U;    /* disable INTST1 interrupt */
			TXD1 = *gp_uart1_tx_address;
			gp_uart1_tx_address++;
			g_uart1_tx_count--;
			STMK1 = 0U;    /* enable INTST1 interrupt */
			break ;

		case SAU1_UART2 :
			gp_uart2_tx_address = tx_buf;
			g_uart2_tx_count = tx_num;
			STMK2 = 1U;    /* disable INTST2 interrupt */
			TXD2 = *gp_uart2_tx_address;
			gp_uart2_tx_address++;
			g_uart2_tx_count--;
			STMK2 = 0U;    /* enable INTST2 interrupt */
			break ;

		case SAU0_UART0:
			        gp_uart0_tx_address = tx_buf;
			        g_uart0_tx_count = tx_num;
			        STMK0 = 1U;    /* disable INTST0 interrupt */
			        TXD0 = *gp_uart0_tx_address;
			        gp_uart0_tx_address++;
			        g_uart0_tx_count--;
			        STMK0 = 0U;    /* enable INTST0 interrupt */
			        break;
		}
}

/***********************************************************************************************************************
 * Function Name: r_uart1_interrupt_receive
 * Description  : None
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
static void __near r_uart1_interrupt_receive(void)
{

	volatile tbyte recive_byte = RXD1 ;

		if ((recive_byte != '\0') &&( string_index < MAX_STRING_LENGTH -1)){

			recive_string[string_index++] =  recive_byte  ;
		}
		else if ((recive_byte == '\0' )||( string_index >= MAX_STRING_LENGTH -1) ) {
			recive_string[string_index] = '\0' ;
			string_index = 0 ;
			recive_complete = 1 ;
		}


}
/***********************************************************************************************************************
 * Function Name: r_uart1_interrupt_send
 * Description  : None
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
static void __near r_uart1_interrupt_send(void)
{
	if (g_uart1_tx_count > 0U)
	{
		TXD1 = *gp_uart1_tx_address;
		gp_uart1_tx_address++;
		g_uart1_tx_count--;
	}
	else
	{
		UART1_CallBack_sendend();
	}
}
/***********************************************************************************************************************
 * Function Name: r_uart1_UART1_CallBack_receiveend
 * Description  : This function is a callback function when UART1 finishes reception.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
static void UART1_CallBack_receiveend(tbyte rx_data)
{


}
/* Function Name: UARTX_Receive
 * Description  : This function receives UARTX data.
 * Arguments    : rx_buf -
 *                    receive buffer pointer
 *                rx_num -
 *                    buffer size
 *                t_UART_Select UART_Num
 * Return Value : void
 ***********************************************************************************************************************/
/*void UARTX_Receive(tbyte *recieve_buffer )
{
	    WDT_Reset();

			if((GET_BIT(SSR02,5))==0)
			{
          *recieve_buffer =  SDR02 ;
			}


}*/
static void UART1_CallBack_sendend(void)
{

}

