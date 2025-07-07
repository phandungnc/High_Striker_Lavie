#ifndef FLASH_MANAGER_H
#define FLASH_MANAGER_H

#include "stm32f4xx_hal.h"

// Địa chỉ bắt đầu và kết thúc lưu trên Flash
#define FLASH_USER_START_ADDR   0x080E0000  // Địa chỉ bắt đầu lưu (sector 11)
#define FLASH_USER_END_ADDR     0x080E07F0  // Địa chỉ kết thúc (128KB sector)
#define MAX_SLOTS               1000        // Số lượng giá trị có thể lưu trước khi xóa sector

// Hàm lưu điểm cao vào Flash
void saveHighScoreToFlash(int32_t score);
int32_t readHighScoreFromFlash();
#endif // FLASH_MANAGER_H
