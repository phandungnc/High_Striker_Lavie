/*
 * flashManager.c
 *
 *  Created on: Jun 9, 2025
 *      Author: NKQuoc
 */


#include "flashManager.h"
#define FLASH_USER_SECTOR    FLASH_SECTOR_11
// Hàm lưu điểm cao vào Flash
void saveHighScoreToFlash(int32_t score)
{
    uint32_t currentAddr = FLASH_USER_START_ADDR;
    HAL_StatusTypeDef status;

    // Mở khóa Flash
    HAL_FLASH_Unlock();

    // Tìm địa chỉ trống đầu tiên
    for (currentAddr = FLASH_USER_START_ADDR; currentAddr < FLASH_USER_END_ADDR; currentAddr += 4) {
        int32_t storedValue = *(volatile int32_t*)currentAddr;
        if (storedValue == 0xFFFFFFFF) {  // Kiểm tra xem ô nhớ đã được ghi chưa
            break;  // Nếu chưa có giá trị nào, dùng ô này
        }
    }

    // Nếu tìm thấy ô trống
    if (currentAddr < FLASH_USER_END_ADDR) {
        status = HAL_FLASH_Program(TYPEPROGRAM_WORD, currentAddr, score);
        if (status != HAL_OK) {
            // Xử lý lỗi (Ví dụ: bật đèn báo lỗi)
        }
    } else {
        // Nếu sector đầy, xóa và ghi lại từ đầu
        FLASH_Erase_Sector(FLASH_USER_SECTOR, VOLTAGE_RANGE_3);  // Xóa toàn bộ sector

        // Ghi giá trị vào lại từ đầu
        currentAddr = FLASH_USER_START_ADDR;
        for (int i = 0; i < MAX_SLOTS; i++) {
            status = HAL_FLASH_Program(TYPEPROGRAM_WORD, currentAddr, score);
            if (status != HAL_OK) {
                // Xử lý lỗi (Ví dụ: bật đèn báo lỗi)
                break;
            }
            currentAddr += 4;  // Tiến tới ô nhớ tiếp theo
        }
    }

    // Khóa lại Flash
    HAL_FLASH_Lock();
}

int32_t readHighScoreFromFlash(){
	 uint32_t currentAddr;
	    int32_t latestScore = -1;

	    // Duyệt từ cuối flash ngược về đầu
	    for (currentAddr = FLASH_USER_END_ADDR - 4; currentAddr >= FLASH_USER_START_ADDR; currentAddr -= 4) {
	        int32_t value = *(volatile int32_t*)currentAddr;
	        if (value != 0xFFFFFFFF) {
	            latestScore = value;
	            break;
	        }

	        // Nếu trừ về dưới 0 thì thoát (tránh tràn uint32_t)
	        if (currentAddr < FLASH_USER_START_ADDR + 4)
	            break;
	    }

	    return latestScore;
}

