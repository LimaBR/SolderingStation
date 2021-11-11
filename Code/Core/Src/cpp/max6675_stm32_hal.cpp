/*
 * max6675_stm32_hal.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: Gabriel
 */

#include <max6675_stm32_hal.hpp>

Max6675::Max6675(SPI_HandleTypeDef* hspiConstructor, GPIO_TypeDef* GPIOxConstructor, uint16_t GPIO_PinConstructor){
	//Dava para usar initialization lists
	hspi = hspiConstructor;
	GPIOx = GPIOxConstructor;
	GPIO_Pin = GPIO_PinConstructor;
}

float Max6675::readTemp(void){
	uint16_t buf;
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(hspi, SPIRecvBuf, 2, 1);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	buf = SPIRecvBuf[1] + (SPIRecvBuf[0]<<8);
	if ((buf>>2) & 1){
		return -1;
	}else{
		return (float)(buf>>3)/4;
	}
}
