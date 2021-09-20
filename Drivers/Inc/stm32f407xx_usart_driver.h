/*
 * stm32f407xx_uart_driver.h
 *
 *  Created on: 20 Eyl 2021
 *      Author: samed
 */
#include "stm32f407xx.h"

#ifndef INC_STM32F407XX_UART_DRIVER_H_
#define INC_STM32F407XX_UART_DRIVER_H_

/*
 **************************** UART STRUCTURES*************************
 */

/*
 * Configuration structure for USARTx peripheral
 */
typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;


/*
 * Handle structure for USARTx peripheral
 */
typedef struct
{
	USART_RegDef_t 	*pUSARTx;
	USART_Config_t   USART_Config;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxBusyState;
	uint8_t RxBusyState;
}USART_Handle_t;

/*
 **************************** USART FONCTIONS*************************
 */

/*
 * USART Clock Control
 */
void USART_Pclk_Ctrl(USART_RegDef_t *pUSARTx,uint8_t EnOrDi);
void USART_PENB(USART_RegDef_t *pUSARTx,uint8_t EnorDi);


/*
 * USART Interrupt and config
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);


/*
 * Other Peripheral Control APIs
 */
uint8_t USART_Get_Flag_Status(USART_RegDef_t *pUSARTx,uint16_t FlagName);
void USART_Clear_Flag(USART_RegDef_t *pUSARTx,uint16_t FlagName);



/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9

/*
 * USART FLAGS
 */
#define USART_FLAG_PE	 	 (1<<USART_SR_PE)
#define USART_FLAG_FE		 (1<<USART_SR_FE)
#define USART_FLAG_NF		 (1<<USART_SR_NE)
#define USART_FLAG_ORE		 (1<<USART_SR_ORE)
#define USART_FLAG_IDLE	 	 (1<<USART_SR_IDLE)
#define USART_FLAG_RXNE		 (1<<USART_SR_RXNE)
#define USART_FLAG_TC		 (1<<USART_SR_TC)
#define USART_FLAG_TXE		 (1<<USART_SR_TXE)
#define USART_FLAG_LBD		 (1<<USART_SR_LBD)
#define USART_FLAG_CTS		 (1<<USART_SR_CTS)


#endif /* INC_STM32F407XX_UART_DRIVER_H_ */
