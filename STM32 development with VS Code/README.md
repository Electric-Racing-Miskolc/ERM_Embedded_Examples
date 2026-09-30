# STM32 development with VS Code

This is a quick tutorial on how to setup VS Code to work with STM32.

## Installing software

Download and install the following software:

- [VS Code](https://code.visualstudio.com/download)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

## Configuring STM32CubeMX

Open CubeMX and in the menu bar click `Help` > `Connection & Updates` \
![image 1](images/1_CubeMX_Connection.png)

Then click `myST` > `Enter myST account information` \
![image 2](images/2_CubeMX_myST.png)

Log into your ST account.

## Configuring VS Code

Before installing extensions, I recommend creating a separate VS Code profile to use for STM32 development. \
The STM32 extension pack can slow down the editor. If you create a separate profile, VS Code can remain fast for other kinds of usage.

### Creating VS Code profile

To create a profile, click the Manage button in the bottom left (usually gear icon) and then click `profiles` \
![image 3](images/3_VSCode_Profiles.png)

Then click on `New Profile`, name your profile, change the icon, set the contents sources like on the picture, and filany, click `Create` \
![image 4](images/4_VSCode_NewProfile.png)

### Installing VS Code Extension pack

Open the Extensions menu (icon with boxes), search for `STM32CubeIDE for Visual Studio Code`, find the official one created by `STMicroelectronics` and click `Install` \
![image 5](images/5_VSCode_extension.png)

You are now done with the setup!

## Usage

After creating/opening a project with CubeMX, you need to configure it to use CMake, because that is the only toolchain the VS Code extension supports. \
Go to `Project Manager` > `Project` > `Toolchain / IDE`, and select `CMake` \
![image 6](images/6_CubeMX_config.png) \
Hit `Generate`, and open the folder with VS Code.

Activate the STM32 profile, from the profile selector.

Use the `Build` button in the bottom left corner to build your project \
Shortcut: `F7` \
![image 7](images/7_VSCode_build.png)

In the debug panel, Click the `Run and Debug` button and select a programmer, to flash and debug on a microcontroller \
Shortcut: `F5` \
![image 8](images/8_VSCode_debug.png)

Enjoy your new faster developer experience!