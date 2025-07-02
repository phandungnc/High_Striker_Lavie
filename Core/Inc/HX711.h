#ifndef __HX711_H__
#define __HX711_H__

#include "stm32f1xx_hal.h"  // đổi thành tên chip bạn đang dùng, ví dụ stm32f4xx_hal.h

typedef struct {
    GPIO_TypeDef* dout_port;
    uint16_t dout_pin;
    GPIO_TypeDef* sck_port;
    uint16_t sck_pin;
    int32_t offset;
    float scale;
} HX711;

void HX711_Init(HX711* hx, GPIO_TypeDef* dout_port, uint16_t dout_pin,
                GPIO_TypeDef* sck_port, uint16_t sck_pin);

int32_t HX711_ReadRaw(HX711* hx);
float HX711_GetUnits(HX711* hx, uint8_t times);
void HX711_Tare(HX711* hx, uint8_t times);
void HX711_SetScale(HX711* hx, float scale);

#endif
