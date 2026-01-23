#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"

extern osMessageQueueId_t CANQueue01Handle;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	handleMessages();
}

void Model::handleMessages(){

	if(osMessageQueueGetCount(CANQueue01Handle)> 0){	//if Queue is not empty

			osMessageQueueGet(CANQueue01Handle, &in, 0, 10); //reads and pops the last data

			modelListener->CANMessageControl(in);	//sends data to listener (function is in the header file)
		}
}
