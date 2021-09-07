
#include <stdint.h>
#include <stdio.h>
#include "stm32f407xx.h"
#include "stm32f407fxx_gpio_driver.h"

void delay(void){

	for (uint32_t i = 0; i < 500000; ++i) {};

}

int main(void){
	GPIO_Handle_t gpio_led;

	gpio_led.pGPIOx=GPIOD;
	gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	gpio_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_NO_PUPD;
	gpio_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	gpio_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Pclk_Ctrl(GPIOD, ENABLE);
	GPIO_Init(&gpio_led);

	while(1){

		GPIO_Toggle_Output_Pin(GPIOD, GPIO_PIN_NO_14);
		delay();
	}


	return 0;
}


