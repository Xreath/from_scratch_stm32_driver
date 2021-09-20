/*
 * stm32f407xx_uart_driver.c
 *
 *  Created on: 20 Eyl 2021
 *      Author: samed
 */

#include "stm32f407xx_usart_driver.h"

/*
 **************************** USART FONCTIONS*************************
 */

/*
 * USART Clock Control
 */
void USART_Pclk_Ctrl(USART_RegDef_t  *pUSARTx,uint8_t EnOrDi){

	if(EnOrDi==ENABLE){

		if(pUSARTx==USART1){
			USART1_PCLK_EN();
		}
		else if(pUSARTx==USART2){
			USART2_PCLK_EN();}
		else if(pUSARTx==USART3){USART3_PCLK_EN();
		}
		else if(pUSARTx==UART4){
			UART4_PCLK_EN();
		}
		else if(pUSARTx==UART5){
			UART5_PCLK_EN();
		}
		else if(pUSARTx==USART6){
			USART6_PCLK_EN();
		}

	}
	else
	{
	}

}
void USART_PENB(USART_RegDef_t  *pUSARTx,uint8_t EnorDi){
	if(EnorDi==ENABLE){

		pUSARTx->CR1 |= (1<<13);
	}
	else{

		pUSARTx->CR1 &= ~(1 << 13);
		}

}



/*
 * USART Interrupt and config
 */

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}
}
void USART_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority){

	//1. first lets find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section  = IRQNumber %4 ;

	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );
}


/*
 *  Other Peripheral Control APIs
 */

uint8_t USART_Get_Flag_Status(USART_RegDef_t *pUSARTx,uint16_t FlagName){

	if(pUSARTx->SR & FlagName){

		return FLAG_SET;
	}
	else{

		return FLAG_RESET;
	}

}
void USART_Clear_Flag(USART_RegDef_t *pUSARTx,uint16_t FlagName){

		pUSARTx->SR &= ~( FlagName);


}
