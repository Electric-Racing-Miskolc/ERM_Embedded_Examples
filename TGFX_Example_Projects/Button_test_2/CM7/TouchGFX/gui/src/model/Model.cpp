#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"


extern osMessageQueueId_t btn_queueHandle;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

	handleButton();

}

void Model::handleButton(){

	if(osMessageQueueGetCount(btn_queueHandle) > 0){	//ha van adat a Queue-ban

			uint8_t in = 0;
			osMessageQueueGet(btn_queueHandle, &in, 0, 10); //leszedi a queue utolsó adatát

			if (in == 1){	//ha 1 az adat akkor növeli az értéket
				state++;
			}
			if(in == 2){	//ha 2 az érték akkor resetel
				state = 0;
			}

			modelListener->buttonControl(state);	//listenernek (headerben van csak) küldi a
		}
}
