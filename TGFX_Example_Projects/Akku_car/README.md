# The sample project : Akku_car

The project is made as an example of an accumulator charger car UI. The example uses 2 buttons, one controlls the AVG voltage of the whole accumulator, the other controlls the coltage of all cells individually. 

It uses:

1. RTOS Task to read the button presses
2. 1 Queue to transfer data from the Button_task to the Gui_task
3. In the Gui folder it utilizes the MVP (Model - View - Presenter) architecture as well as uses a **custom GUI container with their own class**

All the changes were commented on each non-trivial line of code to make it easy to understand!

## The given files were changed during the back-end programming:

#### CM7/Core:

- gpio.c : Custom Configuration of BTN_2
- freertos.c : Button Task and queue definition


#### CM7/gui:

- Model.cpp and Model.hpp : handler for the button called at every tick
- ModelListener.hpp (referenced to CM7/generated) : definition of notification task
- Screen1Presenter.cpp and Screen1Presenter.hpp buttonControl task (same as the definition in the listener) - it only forwards the data for the view
- Screen1View.cpp and Screen1View.hpp conversion for the view and refreshing the screen, this also calls the custom container's functions
- Accumulator_temp_1_segment.cpp : the custom container's own class. All the fuctions regarding the container has to be implemented here.