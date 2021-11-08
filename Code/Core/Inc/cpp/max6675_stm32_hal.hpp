/*
 * max6675_stm32_hal.hpp
 *
 *  Created on: Nov 7, 2021
 *      Author: Gabriel
 */

#ifndef INC_CPP_MAX6675_STM32_HAL_HPP_
#define INC_CPP_MAX6675_STM32_HAL_HPP_

#include <main.h>

class Max6675 {
public:
	Max6675(SPI_HandleTypeDef* hspiConstructor, GPIO_TypeDef* GPIOxConstructor, uint16_t GPIO_PinConstructor);
	float readTemp(void);
private:
	uint8_t SPIRecvBuf[64];
	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
};

#endif /* INC_CPP_MAX6675_STM32_HAL_HPP_ */
