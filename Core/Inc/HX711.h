#ifndef HX711_H
#define HX711_H

#include "stm32f4xx_hal.h"

void HX711_Init(GPIO_TypeDef* GPIOx_SCK, uint16_t SCK_Pin, GPIO_TypeDef* GPIOx_DOUT, uint16_t DOUT_Pin);
int32_t HX711_ReadData(GPIO_TypeDef* GPIOx_SCK, uint16_t SCK_Pin, GPIO_TypeDef* GPIOx_DOUT, uint16_t DOUT_Pin);

#endif
