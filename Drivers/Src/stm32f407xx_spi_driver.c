/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: 10 Eyl 2021
 *      Author: samed
 */

#include "stm32f407xx_spi_driver.h"



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
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *TXBuffer,uint32_t len){

while(len>0){


	while(SPI_Get_Flag_Status(pSPIx,SPI_FLAG_TXE)==FLAG_RESET); //Wait until tx buffer be empty

	if(pSPIx->CR1 & (1<<SPI_CR1_DFF)){
		pSPIx->DR = *(uint16_t*)TXBuffer;
		len=len-2;
		(uint16_t *)TXBuffer++;
	}
	else{
		pSPIx->DR = *TXBuffer;
		len--;
		TXBuffer++;
	}

	}
}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *RXBuffer,uint32_t len){

}


/*
 * SPI Interrupt and config
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){

}
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority){

}
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle){

}
