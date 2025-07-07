#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updateCurrentScore(int32_t value);
    void updateHighScore(int32_t value);
    void startBlinkEffect();
    void stopBlinkEffect();
    int blinkIndex;
    bool isBlinking;
    int blinkCounter; // đếm tick (ví dụ mỗi 6 tick = 100ms nếu 60Hz)
    bool blinkForward; // true: nháy xuôi, false: nháy ngược
    virtual void handleTickEvent(); // override từ ViewBase
protected:
    touchgfx::Image backgroundImage;
};

#endif // SCREEN1VIEW_HPP
