# The sample project : Button_test_2

The project shows up a counter that counts up when the USR_BTN_1 is pressed on the board and resets the value when USR_BTN_2 is pressed

It uses:

1. RTOS Task to read the button presses
2. Queue to transfer data from the Button_task to the Gui_task
3. In the Gui folder it utilizes the MVP (Model - View - Presenter) architecture in a basic way.

All the changes were commented on each non-trivial line of code to make it easy to understand!

## The given files were changed during the back-end programming:

#### CM7/Core:

- gpio.c : Custom Configuration of BTN_2
- freertos.c : Button Task and queue definition


#### CM7/gui:

- Model.cpp and Model.hpp : handler for the button called at every tick
- ModelListener.hpp (referenced to CM7/generated) : definition of notification task
- Screen1Presenter.cpp and Screen1Presenter.hpp buttonControl task (same as the definition in the listener) - it only forwards the data for the view
- Screen1View.cpp and Screen1View.hpp conversion for the view and refreshing the screen


This sample code is just enough for each and every use-cases we will encounter in the development proccess!