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

