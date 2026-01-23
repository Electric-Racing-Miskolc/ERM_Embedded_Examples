# ERM GUI Applications

Code examples for Riverdi type embedded STM32 displays.

# How to...
### ... install TouchGFX?

This link shows the whole process, it's not straight forward, please follow all the steps as said in [here!](https://support.touchgfx.com/docs/introduction/installation)

### ... open a project from the repository?

Each project (in the TGFX Folder) has an STM32CubeIDE folder which has the .project file. Open that with the CubeIDE to import it properly!

In the (CoreType)/TouchGFX folder you will find the TGFX project file, you can open the front-end project from that!

### ... create new project?

Use TouchGFX to install and generate the files via choosing the right Riverdi board from the "New project" menu!

### ... test code on a board?

First of all the TGFX simulator works until there was no code changed in the gui folder, so the GUI can be tested! In CubeIDE you can build your code, all the static errors (link and compile time errors) will show up there if any occurs!

Lastly if everything seems fine, in the ERM Workshop the code cen be tested via the help of @Redd151 (Sikora Dávid)

### More info about the programming in the TGFX_Projects/Button_test_2 folder!

# Examples

The TGFX_Example_Projects folder contains all the beginning knowledge for writing a GUI application. The examples currently present:

- Button_test_2    -- for the most basic gui-backend communication 
- Akku_car         -- for showcasing the possibilities of gui programming as well as custom container declarations
