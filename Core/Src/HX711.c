#include "HX711.h"
#include "main.h"
#include "delay.h"  // nếu bạn có thư viện delay_us (hoặc dùng HAL_Delay nếu chấp nhận độ trễ ms)

void HX711_Init(HX711* hx, GPIO_TypeDef* dout_port, uint16_t dout_pin,
                GPIO_TypeDef* sck_port, uint16_t sck_pin) {
    hx->dout_port = dout_port;
    hx->dout_pin = dout_pin;
    hx->sck_port = sck_port;
    hx->sck_pin = sck_pin;
    hx->offset = 0;
    hx->scale = 1.0f;
}

int32_t HX711_ReadRaw(HX711* hx) {
    int32_t value = 0;
    while(HAL_GPIO_ReadPin(hx->dout_port, hx->dout_pin));  // chờ sẵn sàng

    for (uint8_t i = 0; i < 24; i++) {
        HAL_GPIO_WritePin(hx->sck_port, hx->sck_pin, GPIO_PIN_SET);
        value = value << 1;
        if (HAL_GPIO_ReadPin(hx->dout_port, hx->dout_pin))
            value++;
        HAL_GPIO_WritePin(hx->sck_port, hx->sck_pin, GPIO_PIN_RESET);
    }

    // Bước xung thứ 25 (Channel A, gain 128)
    HAL_GPIO_WritePin(hx->sck_port, hx->sck_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hx->sck_port, hx->sck_pin, GPIO_PIN_RESET);

    if (value & 0x800000)
        value |= 0xFF000000;  // chuyển sang số âm (sign extend)

    return value;
}

float HX711_GetUnits(HX711* hx, uint8_t times) {
    int64_t sum = 0;
    for (uint8_t i = 0; i < times; i++) {
        sum += HX711_ReadRaw(hx);
        HAL_Delay(1);
    }
    int32_t avg = sum / times;
    return (avg - hx->offset) / hx->scale;
}

void HX711_Tare(HX711* hx, uint8_t times) {
    int64_t sum = 0;
    for (uint8_t i = 0; i < times; i++) {
        sum += HX711_ReadRaw(hx);
        HAL_Delay(1);
    }
    hx->offset = sum / times;
}

void HX711_SetScale(HX711* hx, float scale) {
    hx->scale = scale;
}
