# ERM Embedded Samples Repository

This repostory is dedicated to all the embedded STM32 program sample codes. This repository should contain all the projects trying out a new sensor, or microcontroller, etc

# Rules

- Each project has to be in seperate folder
- DO NOT CREATE NEW WORKSPACE ON GIT! Workspace folders should only exist on the local machine, the one is only an example with the right configuration
- Main branch is protected, create a new branch for each new project. After the completion of the configuration and the code generation, you can pull request!
- Please use a gitignore. 
The .gitignore file should be placed in the root of your project directory. \
In this repo there are examples for:
    - regular CubeIDE/CubeMX projects (.gitignore_CubeIDE_example)
    - and TouchGFX projects (.gitignore_TouchGFX_example). 

# Examples 

The current folders contain all the beginning knowledge for embedded programming. The examples currently present:

- CAN_TEST_Projects -- for explaining the CANFD communication and it's coding
- ISA_TEST -- programming the Isabellenhütte IVT-S-300-U3-I-CAN2-12/24 sensor unit
- TGFX_Example_Projects -- Code examples for Riverdi type embedded STM32 displays.
