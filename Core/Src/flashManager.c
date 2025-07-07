#include "flashManager.h"

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
