#include <gui/screen1_screen/Screen1View.hpp>
#include <stdio.h>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    buttonControl(500,500);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::buttonControl(int stateAVG, int stateALL){

	sprintf(outCharsT, "%d,%d", stateAVG/10, stateAVG%10 );	//convert from int to string
	sprintf(outCharsV, "%d,%d", stateALL/10, stateALL%10 );

	Unicode::strncpy(txtAVGTempBuffer, outCharsT, TXTAVGTEMP_SIZE); //writes data to wildcard buffer
	Unicode::strncpy(txtAVGVoltBuffer, outCharsV, TXTAVGVOLT_SIZE);

	txtAVGTemp.invalidate();	//invalidate, aka refreshes text fields
	txtAVGVolt.invalidate();

	//calls custom container's update function
	accumulator_temp_segment1.updateAllBars(stateALL/10, stateAVG/10);
	accumulator_temp_segment1_1.updateAllBars(stateALL/10, stateAVG/10);
	accumulator_temp_segment1_2.updateAllBars(stateALL/10, stateAVG/10);
	accumulator_temp_segment1_3.updateAllBars(stateALL/10, stateAVG/10);
	accumulator_temp_segment1_4.updateAllBars(stateALL/10, stateAVG/10);
	// 				          ^-- sometimes doesn't get indexed, fuck knows why, but works
}
