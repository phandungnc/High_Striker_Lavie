#include "hx711.h"
//static GPIO_TypeDef* DOUT_PORT;
//static uint16_t DOUT_PIN;
//static GPIO_TypeDef* SCK_PORT;
//static uint16_t SCK_PIN;

void HX711_Init(GPIO_TypeDef* GPIOx_SCK, uint16_t SCK_Pin, GPIO_TypeDef* GPIOx_DOUT, uint16_t DOUT_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Cấu hình chân PB12 (SCK) làm Output
    GPIO_InitStruct.Pin = SCK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOx_SCK, &GPIO_InitStruct);

    // Cấu hình chân PB14 (DOUT) làm Input
    GPIO_InitStruct.Pin = DOUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOx_DOUT, &GPIO_InitStruct);
}

// Đọc dữ liệu từ HX711
int32_t HX711_ReadData(GPIO_TypeDef* GPIOx_SCK, uint16_t SCK_Pin, GPIO_TypeDef* GPIOx_DOUT, uint16_t DOUT_Pin)
{
	// chờ DOUT xuống LOW
	    uint32_t timeout = HAL_GetTick();
	    while (HAL_GPIO_ReadPin(GPIOx_DOUT, DOUT_Pin) == GPIO_PIN_SET) {
	        if (HAL_GetTick() - timeout > 1000)
	            return 0xFFFFFFFF;
	    }

	    int32_t value = 0;
	    for (int i = 0; i < 24; i++) {
	        HAL_GPIO_WritePin(GPIOx_SCK, SCK_Pin, GPIO_PIN_SET);
	        delay_us(1);
	        value <<= 1;
	        if (HAL_GPIO_ReadPin(GPIOx_DOUT, DOUT_Pin))
	            value |= 1;
	        HAL_GPIO_WritePin(GPIOx_SCK, SCK_Pin, GPIO_PIN_RESET);
	        delay_us(1);
	    }

	    // xử lý số âm
	    if (value & 0x800000)
	    value |= 0xFF000000; // Sign extend nếu số âm
	    else
	    value &= 0x00FFFFFF; // Đảm bảo không dư bit nếu số dương


	    // 1 xung clock để thiết lập gain 128
	    HAL_GPIO_WritePin(GPIOx_SCK, SCK_Pin, GPIO_PIN_SET);
	    delay_us(1);
	    HAL_GPIO_WritePin(GPIOx_SCK, SCK_Pin, GPIO_PIN_RESET);
	    delay_us(1);
	    return value;
}
