/*
 * spi_comm.c
 *
 *  Created on: 13 Eyl 2021
 *      Author: samed
 */
#include"stm32f407xx_gpio_driver.h"
#include"stm32f407xx_spi_driver.h"
#include <string.h>

void SPI2_GPIOInits(void);
void SPI2_Inits(void);

/*
 * PB14 ---------->MISO
 * PB15  --------->MOSI
 * PB13   --------->SCLK
 * PB12   --------->NSS
 *
 * ALT FUNC. MODE =5
 */

int main(){
	char user_data[] ="Merhaba Dunya" ;
	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();
	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();
	//SPI ENB
	SPI_Enable(SPI2, ENABLE);
	//to send data
	SPI_SendData(SPI2, (uint8_t *)user_data, sizeof(user_data));




	return 0;
}



void SPI2_GPIOInits(void){
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO  We did not use this pin
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);


	//NSS 	We did not use this pin
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	//GPIO_Init(&SPIPins);

}

void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;

	SPI2Handle.SPIConfig.SPI_BusConfig 	 = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_CPHA        = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_CPOL        = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_DFF         = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_DeviceMode  = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SSM         = SPI_SSM_EN;
	SPI2Handle.SPIConfig.SPI_SclkSpeed   = SPI_CLCK_SPEED_PCKL_DIV_2;

	SPI_Init(&SPI2Handle);

}























