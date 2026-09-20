# Flash programming

To program a microcontroller's flash memory, you acan use two methods depending on what chp you use. The H5 series lets you use STM32CubeIde's built in memory management tool (more in the folder for the H5), and the G4 series chips are inferior to the H5, so you'll need to modify the linker script (.ld files) by hand (more in the the folder for the G4).

Both the G4 and the H5 uses a dual bank system, but the size of the memory is different. The G4 has 512Kb of memory and uses a page-based system with 2Kb pages. The H5 has 2Mb os memory and uses a sector-based system with 8Kb sectors. With this math you can see that both chips have 256 pages or sectors, 128/memory bank. We usually want to write in the end of the memory.