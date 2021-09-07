/*
 * stm32f407fxx_gpio_driver.c
 *
 *  Created on: 5 Sept. 2021
 *      Author: Fazli
 */


#include "stm32f407fxx_gpio_driver.h"


/*********************************************************************
 * @fn      		  - GPIO_Pclk_Ctrl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */
void GPIO_Pclk_Ctrl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi){

	if(EnorDi==ENABLE){

		if(pGPIOx==GPIOA){GPIOA_PCLK_EN();}
		else if(pGPIOx==GPIOB){GPIOB_PCLK_EN();}
		else if(pGPIOx==GPIOC){GPIOC_PCLK_EN();}
		else if(pGPIOx==GPIOD){GPIOD_PCLK_EN();}
		else if(pGPIOx==GPIOE){GPIOE_PCLK_EN();}
		else if(pGPIOx==GPIOF){GPIOF_PCLK_EN();}
		else if(pGPIOx==GPIOG){GPIOG_PCLK_EN();}
		else if(pGPIOx==GPIOH){GPIOH_PCLK_EN();}
		else if(pGPIOx==GPIOI){GPIOI_PCLK_EN();}
	}
	else
	{
	}

}

/*
 * GPIO Init de-init control
 */

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initilize gpio
 *
 * @param[in]         - pGPIOHandle
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp=0;
	//1 . configure the mode of gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <=GPIO_MODE_ANALOG){
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->MODER |=temp;
	}
	else{

	}

	temp=0;
	//2. configure the speed
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OSPEEDR |=temp;
	temp=0;
	//3. configure the pupd settings
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->PUPDR |=temp;
	temp=0;

	//4. configure the optype
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OTYPER |=temp;
	temp=0;

	//5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <=GPIO_MODE_ALTFN){

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7){
			pGPIOHandle->pGPIOx->AFR[0]  &= ~( 0xF << (4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
			pGPIOHandle->pGPIOx->AFR[0] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		}

		else{
			pGPIOHandle->pGPIOx->AFR[1]  &= ~( 0xF << (4 * ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/8))); //clearing
			pGPIOHandle->pGPIOx->AFR[1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 *((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/8)));
		}

	}

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

	if(pGPIOx==GPIOA){GPIOA_REG_RESET();}
	else if(pGPIOx==GPIOB){GPIOB_REG_RESET();}
	else if(pGPIOx==GPIOC){GPIOC_REG_RESET();}
	else if(pGPIOx==GPIOD){GPIOD_REG_RESET();}
	else if(pGPIOx==GPIOE){GPIOE_REG_RESET();}
	else if(pGPIOx==GPIOF){GPIOF_REG_RESET();}
	else if(pGPIOx==GPIOG){GPIOG_REG_RESET();}
	else if(pGPIOx==GPIOH){GPIOH_REG_RESET();}
	else if(pGPIOx==GPIOI){GPIOI_REG_RESET();}



}
/*
 * GPIO Data read and write
 */
uint8_t GPIO_Read_Input_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	value=(uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001) ;

	return value;
}
uint16_t GPIO_Read_Input_Port(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value=(uint16_t)pGPIOx->IDR ;

	return value;
}
void GPIO_Write_Output_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){

	if(Value==GPIO_SET){pGPIOx->ODR |=(GPIO_SET << PinNumber);}

	else{pGPIOx->ODR |=(GPIO_RESET << PinNumber);}

}
void GPIO_Write_Output_Port(GPIO_RegDef_t *pGPIOx, uint16_t Value){

pGPIOx->ODR =Value;

}
void GPIO_Toggle_Output_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	pGPIOx->ODR ^= (1<< PinNumber);

}


/*
 * GPIO Interrupt and config
 */


void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t 	IRQPriority, uint8_t EnorDi){



}
void GPIO_IRQHandling(uint8_t PinNumber){



}
