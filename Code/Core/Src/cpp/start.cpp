/*
 * start.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: Gabriel
 */

#include <start.hpp>

void Start() {
	while (true){
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		HAL_Delay(1000);
	}
}
