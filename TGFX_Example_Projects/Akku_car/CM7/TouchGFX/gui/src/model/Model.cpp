#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"

extern osMessageQueueId_t queueButtonHandle;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	handleButton();
}

void Model::handleButton(){

	if(osMessageQueueGetCount(queueButtonHandle) > 0){	//if Queue is not empty

			uint8_t in = 0;
			osMessageQueueGet(queueButtonHandle, &in, 0, 10); //reads and pops the last data

			if (in == 1){	//if data is 1, it adds to stateAVG
				stateAVG++;

				if (stateAVG > 1000){	//resets over 1000
					stateAVG = 0;
				}
			}
			if(in == 2){	//if data is 2, it adds to stateALL
				stateALL++;

				if (stateALL > 1000){	//resets over 1000
					stateALL = 0;
				}
			}



			modelListener->buttonControl(stateAVG, stateALL);	//sends data to listener (function is in the header file)
		}
}
