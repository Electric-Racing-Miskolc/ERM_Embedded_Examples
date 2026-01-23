#include <gui/screen1_screen/Screen1View.hpp>
#include "stdio.h"

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

void Screen1View::buttonControl(int state){

	sprintf(outChars, "%d", state);	//konvertál stringre int-ről

	Unicode::strncpy(textArea1Buffer, outChars, TEXTAREA1_SIZE);	//kiiratja a wildcard bufferbe a stringet

	textArea1.invalidate();		//frissíti a textArea-t

}

