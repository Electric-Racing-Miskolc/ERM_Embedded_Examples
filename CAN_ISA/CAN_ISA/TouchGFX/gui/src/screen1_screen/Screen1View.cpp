#include <gui/screen1_screen/Screen1View.hpp>
#include <stdio.h>

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

void Screen1View::CANMessageDisplay(int message){

	sprintf(outChars, "%d.%d", message/1000, message%1000 );
	Unicode::strncpy(textArea1Buffer, outChars, TEXTAREA1_SIZE);
	textArea1.invalidate();

}
