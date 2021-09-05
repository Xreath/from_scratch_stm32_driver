/*
 * stm32f407fxx_gpio_driver.h
 *
 *  Created on: 5 Sept. 2021
 *      Author: Fazli
 */

#ifndef INC_STM32F407FXX_GPIO_DRIVER_H_
#define INC_STM32F407FXX_GPIO_DRIVER_H_

#include "stm32f407xx.h"



typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;			/*!< possible values from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;



/*
 * Structure of GPIO pin
 */

typedef struct{

	GPIO_RegDef_t *pGPIOx; //This holds the base adress of the GPIO port which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;



#endif /* INC_STM32F407FXX_GPIO_DRIVER_H_ */
