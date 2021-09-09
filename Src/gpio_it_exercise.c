/*
 * 002led_button.c
 *
 *  Created on: Feb 1, 2019
 *      Author: admin
 */

#include<string.h>
#include "stm32f407xx_gpio_driver.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW



int main(void)
{

	GPIO_Handle_t GpioLed, GpioLed1,GPIOBtn;

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GPIOBtn,0,sizeof(GpioLed));

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Pclk_Ctrl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed);

	GpioLed1.pGPIOx = GPIOD;
	GpioLed1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GpioLed1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Pclk_Ctrl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed1);


	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Pclk_Ctrl(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);


	//IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0,15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0,ENABLE);

    while(1){

    GPIO_Write_Output_Pin(GPIOD,GPIO_PIN_NO_15,GPIO_SET);
    };

}


void EXTI0_IRQHandler(void)
{

	GPIO_Write_Output_Pin(GPIOD,GPIO_PIN_NO_14,GPIO_SET);
	delay(); //200ms . wait till button de-bouncing gets over
	GPIO_Write_Output_Pin(GPIOD,GPIO_PIN_NO_14,GPIO_RESET);
	GPIO_IRQHandling(GPIO_PIN_NO_0); //clear the pending event from exti line
}
