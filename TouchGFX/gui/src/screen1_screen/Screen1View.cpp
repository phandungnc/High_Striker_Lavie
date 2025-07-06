#include <gui/screen1_screen/Screen1View.hpp>
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart1;
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateCurrentScore(int32_t value) // nhận dữ liệu từ Presenter
{
	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
    Unicode::snprintf(currentScoreBuffer, CURRENTSCORE_SIZE, "%d", static_cast<int>(value));
//    HAL_UART_Transmit(&huart1, (uint8_t*)currentScoreBuffer, CURRENTSCORE_SIZE, HAL_MAX_DELAY);
    currentScore.setWildcard(currentScoreBuffer);
    currentScore.invalidate();  // hoặc tên TextArea bạn đặt
}
