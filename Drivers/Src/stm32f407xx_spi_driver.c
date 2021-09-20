/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: 10 Eyl 2021
 *      Author: samed
 */

#include "stm32f407xx_spi_driver.h"
#include <stddef.h>


/*********************************************************************
 * @fn      		  - SPI_PeriClockControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
/*
 * SPI Clock Control
 */
void SPI_Pclk_Ctrl(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==ENABLE){
		if(pSPIx==SPI1){
			SPI1_PCLK_EN();
		}
		else if(pSPIx==SPI2){
			SPI2_PCLK_EN();
		}
		else if(pSPIx==SPI3){
			SPI3_PCLK_EN();
		}
	}
}


void SPI_Enable(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==ENABLE){
		pSPIx->CR1 |= (1<< SPI_CR1_SPE);
	}
	else {
		pSPIx->CR1 &= ~(1<< SPI_CR1_SPE);
	}

}

void SPI_SSI_Config(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==ENABLE){
		pSPIx->CR1 |= (1<< SPI_CR1_SSI);
	}
	else {
		pSPIx->CR1 &= ~(1<< SPI_CR1_SSI);
	}

}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==ENABLE){
		pSPIx->CR2 |= (1<< SPI_CR2_SSOE);
	}
	else {
		pSPIx->CR2 &= ~(1<< SPI_CR2_SSOE);
	}




}

/*********************************************************************
 * @fn      		  - SPI_Get_Flag
 *
 * @brief             -
 *
 * @param[in]         pSPIHandle
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

/*
 * SPI Initialize  and De initialize
 */
uint8_t SPI_Get_Flag_Status(SPI_RegDef_t *pSPIx,uint8_t FlagName){

	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             -
 *
 * @param[in]         pSPIHandle
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
/*
 * SPI Initialize  and De initialize
 */
void SPI_Init(SPI_Handle_t *pSPIHandle){
	uint32_t tempreg=0;
	SPI_Pclk_Ctrl(pSPIHandle->pSPIx, ENABLE);

	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_FD){
		//Bidirectional should be line clear
		tempreg &= ~(1<< SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_HD){
		//Bidirectional should be line set
		tempreg |=(1<< SPI_CR1_BIDIMODE);
	}

	else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//Bidirectional should be line clear
		tempreg &= ~(1<< SPI_CR1_BIDIMODE);
		//RX only bit must set
		tempreg |=(1<< SPI_CR1_RXONLY);
	}

	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;


	pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx){

	if(pSPIx==SPI1){SPI1_REG_RESET();}
	else if(pSPIx==SPI2){SPI2_REG_RESET();}
	else if(pSPIx==SPI3){SPI3_REG_RESET();}
}

/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTXBuffer,uint32_t len){

	while(len > 0)
	{
		//1. wait until TXE is set
		while(SPI_Get_Flag_Status(pSPIx,SPI_FLAG_TXE)  == FLAG_RESET );

		//2. check the DFF bit in CR1
		if( (pSPIx->CR1 & ( 1 << SPI_CR1_DFF) ) )
		{
			//16 bit DFF
			//1. load the data in to the DR
			pSPIx->DR =   *((uint16_t*)pTXBuffer);
			len=len-2;
			(uint16_t*)pTXBuffer++;
		}else
		{
			//8 bit DFF
			pSPIx->DR =   *pTXBuffer;
			len--;
			pTXBuffer++;
		}
	}
}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRXBuffer,uint32_t len){
	while(len > 0)
	{
		//1. wait until TXE is set
		while(SPI_Get_Flag_Status(pSPIx,SPI_FLAG_RXNE)  == FLAG_RESET );

		//2. check the DFF bit in CR1
		if( (pSPIx->CR1 & ( 1 << SPI_CR1_DFF) ) )
		{
			//16 bit DFF
			//1. load the data in to the DR
			*((uint16_t*)pRXBuffer) = pSPIx->DR ;
			len=len-2;
			(uint16_t*)pRXBuffer++;
		}else
		{
			//8 bit DFF
			*pRXBuffer= pSPIx->DR;
			len--;
			pRXBuffer++;
		}
	}
}


/*
 * INTERRUPT FONCTION RX AND TX
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *TXBuffer,uint32_t len){
	uint8_t state = pSPIHandle->TXState;
	if (state != SPI_BUSY_IN_TX) {
		//1.Save the Tx buffer address and length information in some global variables
		pSPIHandle->pTXBuffer =TXBuffer;
		pSPIHandle->TXLenght=len;
		//2. Mark the SPI state as busy in transmission so that no other code can take over same SPI peripheral until transmission is over
		pSPIHandle->TXState =SPI_BUSY_IN_TX;
		//3.Enable TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->SR |= (1<<SPI_CR2_TXEIE);
		//4.Data transmission will handled by the ISR code

	}
	return state;
}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *RXBuffer,uint32_t len){
	uint8_t state = pSPIHandle->RXState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1 . Save the Rx buffer address and Len information in some global variables
		pSPIHandle->pRXBuffer = RXBuffer;
		pSPIHandle->RXLenght = len;
		//2.  Mark the SPI state as busy in reception so that
		//    no other code can take over same SPI peripheral until reception is over
		pSPIHandle->RXState = SPI_BUSY_IN_RX;

		//3. Enable the RXNEIE control bit to get interrupt whenever RXNEIE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE );

	}


	return state;

}


/*
 * SPI Interrupt and config
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
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
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority){
	//1. first lets find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section  = IRQNumber %4 ;

	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );
}


void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle){

	pSPIHandle->pSPIx->CR2 &= ~(1<< SPI_CR2_TXEIE);
	pSPIHandle->pTXBuffer= NULL;
	pSPIHandle->TXLenght=0;
	pSPIHandle->TXState=SPI_READY;

}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1<< SPI_CR2_RXNEIE);
	pSPIHandle->pRXBuffer= NULL;
	pSPIHandle->RXLenght=0;
	pSPIHandle->RXState=SPI_READY;



}

static void SPI__OVR_IT_Handle(SPI_Handle_t *pSPIHandle){

	uint8_t temp;
	//1. clear the ovr flag
	if(pSPIHandle->TXState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp; //to close unused variable warning
	//2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);



}
static void SPI_RXNE_IT_Handle(SPI_Handle_t *pSPIHandle){
	//do rxing as per the dff
	if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF))
	{
		//16 bit
		*((uint16_t*)pSPIHandle->pRXBuffer) = (uint16_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RXLenght -= 2;
		pSPIHandle->pRXBuffer++;
		pSPIHandle->pRXBuffer++;

	}else
	{
		//8 bit
		*(pSPIHandle->pRXBuffer) = (uint8_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RXLenght--;
		pSPIHandle->pRXBuffer++;
	}

	if(! pSPIHandle->RXLenght)
	{
		//reception is complete
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
	}

}
static void SPI_TXE_IT_Handle(SPI_Handle_t *pSPIHandle){


		//1. check the DFF bit in CR1
		if( (pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF) ) )
		{
			//16 bit DFF
			//1. load the data in to the DR
			pSPIHandle->pSPIx->DR =   *((uint16_t*)pSPIHandle->pTXBuffer);
			pSPIHandle->TXLenght=pSPIHandle->TXLenght-2;
			(uint16_t*)pSPIHandle->pTXBuffer++;
		}else
		{
			//8 bit DFF
			pSPIHandle->pSPIx->DR =   *pSPIHandle->pTXBuffer;
			pSPIHandle->TXLenght--;
			pSPIHandle->pTXBuffer++;
		}

		if(! pSPIHandle->TXLenght)
		{
			//TxLen is zero , so close the spi transmission and inform the application that
			//TX is over.

			//this prevents interrupts from setting up of TXE flag
			SPI_CloseTransmisson(pSPIHandle);
			SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
		}

}


void SPI_IRQHandling(SPI_Handle_t *pSPIHandle){

	uint8_t temp1,temp2;
	//first lets check for TXE
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_SR_TXE);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_TXEIE);

	if(temp1 && temp2){
		//handle TXE
		SPI_TXE_IT_Handle(pSPIHandle);
	}
	// check for RXNE
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_SR_RXNE);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_RXNEIE);
	if(temp1 && temp2){
		//handle TXE
		SPI_RXNE_IT_Handle(pSPIHandle);
	}

	// check for ovr flag
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_SR_OVR);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_ERRIE);
	if(temp1 && temp2){
		//handle ovr error
		SPI__OVR_IT_Handle(pSPIHandle);
	}
}


 __attribute__((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv){


}
