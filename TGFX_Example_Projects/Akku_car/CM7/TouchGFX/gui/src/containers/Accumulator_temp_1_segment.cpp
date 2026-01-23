#include <gui/containers/Accumulator_temp_1_segment.hpp>
#include <touchgfx/Color.hpp>

Accumulator_temp_1_segment::Accumulator_temp_1_segment()
{

}

void Accumulator_temp_1_segment::initialize()
{
    Accumulator_temp_1_segmentBase::initialize();

    this->avgLimit[0] = lineProgress1.getY();	//reads the Y coordinate of the line, this is to be used in later calculations
    this->avgLimit[1] = avgLimit[0] + 100;	//limit of the top and bottom max value, TO BE USED IN INTERPOLATION
}

void Accumulator_temp_1_segment::updateAllBars(int value, int avg){ //updates the bars with a given value, can be used with array


	lineProgress1.setValue(value);
	updateColor(&lineProgress1Painter, value, avg);
	lineProgress1_1.setValue(value);
	updateColor(&lineProgress1_1Painter, value, avg);
	lineProgress1_2.setValue(value);
	updateColor(&lineProgress1_2Painter, value, avg);
	lineProgress1_3.setValue(value);
	updateColor(&lineProgress1_3Painter, value, avg);
	lineProgress1_4.setValue(value);
	updateColor(&lineProgress1_4Painter, value, avg);
	lineProgress1_5.setValue(value);
	updateColor(&lineProgress1_5Painter, value, avg);
	lineProgress1_6.setValue(value);
	updateColor(&lineProgress1_6Painter, value, avg);
	lineProgress1_7.setValue(value);
	updateColor(&lineProgress1_7Painter, value, avg);
	lineProgress1_8.setValue(value);
	updateColor(&lineProgress1_8Painter, value, avg);
	lineProgress1_9.setValue(value);
	updateColor(&lineProgress1_9Painter, value, avg);
	lineProgress1_10.setValue(value);
	updateColor(&lineProgress1_10Painter, value, avg);
	lineProgress1_11.setValue(value);
	updateColor(&lineProgress1_11Painter, value, avg);
	lineProgress1_12.setValue(value);
	updateColor(&lineProgress1_12Painter, value, avg);
	lineProgress1_13.setValue(value);
	updateColor(&lineProgress1_13Painter, value, avg);
	lineProgress1_14.setValue(value);
	updateColor(&lineProgress1_14Painter, value, avg);
	lineProgress1_15.setValue(value);
	updateColor(&lineProgress1_15Painter, value, avg);
	lineProgress1_16.setValue(value);
	updateColor(&lineProgress1_16Painter, value, avg);
	lineProgress1_17.setValue(value);
	updateColor(&lineProgress1_17Painter, value, avg);
	lineProgress1_18.setValue(value);
	updateColor(&lineProgress1_18Painter, value, avg);
	lineProgress1_19.setValue(value);
	updateColor(&lineProgress1_19Painter, value, avg);
	lineProgress1_20.setValue(value);
	updateColor(&lineProgress1_20Painter, value, avg);
	lineProgress1_21.setValue(value);
	updateColor(&lineProgress1_21Painter, value, avg);

	line1.setY(avgLimit[1] - avg); //here comes a custom private function for the calculation of the position if needed

	invalidateContent();	//invalidates everything, faster than determining the changed values
}

void Accumulator_temp_1_segment::updateColor(PainterRGB565* painter, int value, int avg){

	if (abs(value - avg) > 10){	//deviation from average marked by RED -- TO BE CALIBRATED
		painter->setColor(Color::getColorFromRGB(255, 0, 0));
	}
	else{
		painter->setColor(Color::getColorFromRGB(0, 240, 255));
	}
}
