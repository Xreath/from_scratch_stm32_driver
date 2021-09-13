/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: 10 Eyl 2021
 *      Author: samed
 */

#include "stm32f407xx.h"


#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

/*
 **************************** SPI MACROS*************************
 *
 *@SPI DEVICE MODE
 *@SPI BUS CONFIG
 *@SPI CLOCK SPEED
 *@SPI DFF
 *@SPI CPOL
 *@SPI CPHA
 *@SPI SSM
 */

//@SPI DEVICE MODE
#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE	0

//@SPI BUS CONFIG
#define SPI_BUS_CONFIG_FD				/*FULL DUPLEX*/			1
#define SPI_BUS_CONFIG_HD				/*HALF DUPLEX*/ 		2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	/*SIMPLEX RX ONYL*/ 	3

//@SPI CLOCK SPEED
#define SPI_CLCK_SPEED_PCKL_DIV_2		/*Baud rate fPCLK/2 */		0
#define SPI_CLCK_SPEED_PCKL_DIV_4		/*Baud rate fPCLK/4	*/		1
#define SPI_CLCK_SPEED_PCKL_DIV_8		/*Baud rate fPCLK/8 */		2
#define SPI_CLCK_SPEED_PCKL_DIV_16		/*Baud rate fPCLK/16 */		3
#define SPI_CLCK_SPEED_PCKL_DIV_32		/*Baud rate fPCLK/32 */		4
#define SPI_CLCK_SPEED_PCKL_DIV_64		/*Baud rate fPCLK/64 */		5
#define SPI_CLCK_SPEED_PCKL_DIV_128		/*Baud rate fPCLK/128 */	6
#define SPI_CLCK_SPEED_PCKL_DIV_256		/*Baud rate fPCLK/256 */	7

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS 	0
#define SPI_DFF_16BITS  1

/*
 * @CPOL
 */
#define SPI_CPOL_HIGH 1
#define SPI_CPOL_LOW 0

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH 1
#define SPI_CPHA_LOW 0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN     1
#define SPI_SSM_DI     0

/*
 **************************** SPI STRUCTURES*************************
 */
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;


typedef struct {

SPI_RegDef_t *pSPIx; //This holds the base adress of the SPI port which the pin belongs
SPI_Config_t SPIConfig;

}SPI_Handle_t;




/*
 **************************** SPI FONCTIONS*************************
 */


/*
 * SPI Other Functions
 */
uint8_t SPI_Get_Flag_Status(SPI_RegDef_t *pSPIx,uint8_t FlagName);

/*
 * SPI Clock Control
 */
void SPI_Pclk_Ctrl(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
void SPI_Enable(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
void SPI_SSI_Config(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
/*
 * SPI Initialize  and De initialize
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);



/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *TXBuffer,uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *RXBuffer,uint32_t len);


/*
 * SPI Interrupt and config
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);


/*
 *  Macros to reset GPIOx peripherals
 */

#define SPI1_REG_RESET()               do{(RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()               do{(RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()               do{(RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)

/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15


/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8
/*
 * *******************************************************************************************
 */


/******************************************************************************************
 *SPI peripheral Flag Name
 ******************************************************************************************/

#define SPI_FLAG_RXNE	 (1<<SPI_SR_RXNE)
#define SPI_FLAG_TXE	 (1<<SPI_SR_TXE)
#define SPI_FLAG_CHSIDE	 (1<<SPI_SR_CHSIDE)
#define SPI_FLAG_UDR	 (1<<SPI_SR_UDR)
#define SPI_FLAG_CRCERR	 (1<<SPI_SR_CRCERR)
#define SPI_FLAG_MODF	 (1<<SPI_SR_MODF)
#define SPI_FLAG_OVR	 (1<<SPI_SR_OVR)
#define SPI_FLAG_BSY	 (1<<SPI_SR_BSY)
#define SPI_FLAG_FRE	 (1<<SPI_SR_FRE)


/*
 * *******************************************************************************************
 */

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
