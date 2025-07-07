#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <main.h>
Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::updateCurrentScore(int32_t value)
{
    view.updateCurrentScore(value); // view là instance của Screen1View, được khai báo ở presenter.hpp
}

void Screen1Presenter::updateHighScore(int32_t value)
{
    view.updateHighScore(value);
}

void Screen1Presenter::startBlinkEffect()
{
    view.startBlinkEffect();
}

void Screen1Presenter::stopBlinkEffect()
{
    view.stopBlinkEffect();
}
