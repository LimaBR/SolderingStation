/*
 * start.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: Gabriel
 */

#include <start.hpp>
#include <usbd_cdc_if.h>

uint8_t usbSendBuf[64];

void Start() {
	strcpy((char*)usbSendBuf, "Hello World!\n");
	while (true){
		CDC_Transmit_FS(usbSendBuf, 13);
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		HAL_Delay(1000);
	}
}
