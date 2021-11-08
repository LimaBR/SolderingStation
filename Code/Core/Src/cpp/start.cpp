/*
 * start.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: Gabriel
 */

#include <start.hpp>
#include <usbd_cdc_if.h>
#include <max6675_stm32_hal.hpp>

uint8_t usbSendBuf[64];
extern SPI_HandleTypeDef hspi4;
float temperature;

Max6675 sensor0(&hspi4, GPIOE, GPIO_PIN_11);

/*void SendUsbU32Hex(uint32_t data) {
	sprintf((char*)usbSendBuf, "%08lX\n\r", data);
	CDC_Transmit_FS(usbSendBuf, 10);
}

void SendUsbU08Hex(uint8_t data) {
	sprintf((char*)usbSendBuf, "%02X\n\r", data);
	CDC_Transmit_FS(usbSendBuf, 4);
}*/

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void Start() {
	while (true) {
		HAL_Delay(1000);
		temperature = sensor0.readTemp();
		HAL_Delay(1);
		for(int i=0; i<4; i++){
			//SendUsbU08Hex(SPIRecvBuf[i]);
			HAL_Delay(1);
		}

	}
}
