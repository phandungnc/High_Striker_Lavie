#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstdint>
#include <touchgfx/hal/HAL.hpp>
#include <stm32f4xx_hal.h>
#include <touchgfx/Bitmap.hpp>
#include <images/BitmapDatabase.hpp>
// Định nghĩa biến global modelInstance, kiểu Model, cho phép truy cập lớp Model từ bất kỳ chỗ nào trong code
Model* modelInstance = nullptr;
//static Model* modelInstance1 = nullptr;
extern UART_HandleTypeDef huart1; // khai báo để sử dụng biến đã được cài đặt ở file khác.

// gọi instructor
Model::Model() : modelListener(nullptr)  // Sử dụng nullptr thay vì 0, khởi tạo đối tượng đã khai báo trong hpp
{
    // Constructor, có thể khởi tạo thêm nếu cần
	 modelInstance = this; // Gán địa chỉ của đối tượng hiện tại (this) vào biến toàn cục modelInstance.
	 	 	 	 	 	   // bất kỳ nơi nào trong chương trình (kể cả từ file C thông qua extern "C")
	                       // bạn có thể dùng modelInstance->... để truy cập đối tượng Model hiện tại đang được dùng.
}

void Model::tick()
{
    // Logic xử lý nếu cần
//	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13); // debug
	// update newScore
	if (hasNewScore)
	    {
	        hasNewScore = false;


	        if (modelListener)  // bên file hpp: ModelListener* modelListener;  // Con trỏ ModelListener
	        {
	            modelListener->updateCurrentScore(pendingScore);
	        }
	    }
	// update highScore
	if (hasNewHighScore)
	    {
	        hasNewHighScore = false;
	        if (modelListener)
	        {
	            modelListener->updateHighScore(pendingHighScore);
	        }
	    }
	// bắt đầu chạy hiệu ứng
    if (shouldStartBlinkEffect)
    {
        shouldStartBlinkEffect = false;
        if (modelListener)
        {
            modelListener->startBlinkEffect();
        }
    }
    // dừng hiệu ứng
    if (shouldStopBlinkEffect)
    {
    	shouldStopBlinkEffect = false;
        if (modelListener)
        {
            modelListener->stopBlinkEffect();
        }
    }
}

void Model::setCurrentScore(int32_t value)
{
	pendingScore = value;
	hasNewScore = true;
}

void Model::setHighScore(int32_t value)
{
    pendingHighScore = value;
    hasNewHighScore = true;
}

extern "C" void update_score_from_sensor(int32_t score)  //khai báo code C để khi biên dịch C++ k chạy đoạn này.
{
	if (modelInstance)
	    {
	        modelInstance->setCurrentScore(score);
	    }
}

extern "C" void update_high_score_from_sensor(int32_t score)
{
    if (modelInstance)
    {
        modelInstance->setHighScore(score);
    }
}


extern "C" void trigger_blink_effect_from_c()
{
    if (modelInstance)
    {
        modelInstance->shouldStartBlinkEffect = true;
    }
}

extern "C" void stop_blink_effect_from_c()
{
    if (modelInstance)
    {
        modelInstance->shouldStopBlinkEffect = true;
    }
}



