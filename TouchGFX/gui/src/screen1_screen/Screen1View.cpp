#include <gui/screen1_screen/Screen1View.hpp>
#include "stm32f4xx_hal.h"
#include <images/BitmapDatabase.hpp>
extern UART_HandleTypeDef huart1;
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
	Screen1ViewBase::setupScreen();
	image1.setVisible(true);
}


void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateCurrentScore(int32_t value) // nhận dữ liệu từ Presenter
{
//	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
//  HAL_UART_Transmit(&huart1, (uint8_t*)currentScoreBuffer, CURRENTSCORE_SIZE, HAL_MAX_DELAY);
	if (value < 0)  // -1 là ẩn
	{
	    Unicode::snprintf(currentScoreBuffer, sizeof(currentScoreBuffer), "");
	}
	else
	{
	    Unicode::snprintf(currentScoreBuffer, sizeof(currentScoreBuffer), "%d", value);
	}
	currentScore.invalidate();
}


void Screen1View::updateHighScore(int32_t value)
{
	if (value < 0)  // -1 là ẩn
	{
	    Unicode::snprintf(highScoreBuffer, sizeof(highScoreBuffer), "");
	}else{
		Unicode::snprintf(highScoreBuffer, sizeof(highScoreBuffer), "%d", value);
	}
	highScore.invalidate();
}

// hiệu ứng background
void Screen1View::startBlinkEffect()
{
    blinkIndex = 0;
    isBlinking = true;
    blinkCounter = 0;
    blinkForward = true; // bắt đầu nháy xuôi
}

bool isLooping18 = false;
bool toggleImage18 = true; // true: hiển thị ảnh 1, false: ảnh 8

void Screen1View::stopBlinkEffect()
{
    isBlinking = false;
    isLooping18 = false;
    blinkCounter = 0;
    blinkIndex = 0;
    blinkForward = true;
    image1.setVisible(true); // ảnh 1 đè lên tất cả
    invalidate();
}


void Screen1View::handleTickEvent()
{
    if (isBlinking) // bắt đầu hiệu ứng
    {
        blinkCounter++;

        if (blinkCounter >= 6)
        {
            blinkCounter = 0;

            // Ẩn tất cả ảnh
            image1.setVisible(false);
            image2.setVisible(false);
            image3.setVisible(false);
            image4.setVisible(false);
            image5.setVisible(false);
            image6.setVisible(false);
            image7.setVisible(false);
            image8.setVisible(false);

            // Hiện ảnh theo chỉ số blinkIndex
            switch (blinkIndex)
            {
                case 0: image1.setVisible(true); break;
                case 1: image2.setVisible(true); break;
                case 2: image3.setVisible(true); break;
                case 3: image4.setVisible(true); break;
                case 4: image5.setVisible(true); break;
                case 5: image6.setVisible(true); break;
                case 6: image7.setVisible(true); break;
                case 7: image8.setVisible(true); break;
                default: break;
            }

            invalidate();

            if (blinkForward)
            {
                blinkIndex++;
                if (blinkIndex >= 8)
                {
                    blinkIndex = 6;
                    blinkForward = false;
                }
            }
            else
            {
                if (blinkIndex == 0)
                {
                    isBlinking = false;
                    isLooping18 = true; // Chuyển sang chế độ lặp 1-8
                    toggleImage18 = false; // Bắt đầu từ ảnh 8
                }
                else
                {
                    blinkIndex--;
                }
            }
        }
    }
    else if (isLooping18) // hiệu ứng nháy
    {
        blinkCounter++;

        if (blinkCounter >= 38)
        {
            blinkCounter = 0;

            image1.setVisible(false);
            image8.setVisible(false);

            if (toggleImage18)
            {
                image1.setVisible(true);
            }
            else
            {
                image8.setVisible(true);
            }

            toggleImage18 = !toggleImage18;
            invalidate();
        }
    }
}



