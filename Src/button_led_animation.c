#include <stdint.h>
#include <stdio.h>
#include <stm32f407xx_gpio_driver.h>
#include "stm32f407xx.h"

#define HIGH 1
#define BTN_PRESSED HIGH

#define LOW 0
#define BTN_UNPRESSED LOW
int main(void)
{

	GPIO_Handle_t GpioLed15,GpioLed14,GpioLed13,GpioLed12, GPIOBtn;

	//this is led gpio configuration
	GpioLed15.pGPIOx = GPIOD;
	GpioLed15.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GpioLed15.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed15.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed15.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed15.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Pclk_Ctrl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed15);

	GpioLed14.pGPIOx = GPIOD;
	GpioLed14.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GpioLed14.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed14.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed14.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed14.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed14);


	GpioLed13.pGPIOx = GPIOD;
	GpioLed13.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed13.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed13.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed13.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed13.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed13);


	GpioLed12.pGPIOx = GPIOD;
	GpioLed12.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed12.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed12.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed12.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed12.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed12);


	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Pclk_Ctrl(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);

	while(1)
	{

		if(GPIO_Read_Input_Pin(GPIOA,GPIO_PIN_NO_0) == BTN_PRESSED)
		{
			delay();
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_12, HIGH);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_13, HIGH);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_14, HIGH);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_15, HIGH);
			delay();
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_12, LOW);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_13, LOW);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_14, LOW);
			GPIO_Write_Output_Pin(GPIOD, GPIO_PIN_NO_15, LOW);
			delay();
		}

	}
	return 0;
}
