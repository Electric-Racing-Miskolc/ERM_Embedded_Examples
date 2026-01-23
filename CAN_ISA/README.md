# CAN 2.0A/B Communication example code

This project is made to showcase how the canFD protokol works and how to properly program it for stm32 microcontrollers. 

 ## CANFD Configuration

The first, very important step, is planning. Relevant questions are:
1. At what initial bitrate?
2. At what data bitrate?
3. What clock source?
4. What clock speed(Hz)?

### This section will answer all of these questions!

## 1. and 2., the bitrates?

The limitations: in the standard CAN 2.0 A/B protocol the max bitrate is 1mb/s, so in this case we will use 1mb/s as both the initial and data rate.

## 3. and 4. the clocks?

Choosing the clock source is important because the clock tolerance has to be made into consideration. Clock tolerance is measured in ppm (parts per million) and shows the maximum deviation from the stated frequency. When using internal clock source, the STM **datasheet of the contoller** will state it's tolerance, but **you need to convert it to ppm!** *(dw, the value will bi up in the 1-9k range)*

When using external oscillator as clock source, you can use the universal 50 ppm, most of them only  deviates with only that amount, so **it is advised to use external clock source.**

For the clock speed, ususally 16Mhz is more than enough, but 40 or 80 will grant way more possibility regardign the timing settings.

## Bit-time calculations

For the calculations you will need ALL of the device data in the can network. Kvaser has a calculator [see in links] which only need 7 input and calculates all the variables. 

### You will need:

**FOR EACH DEVICE ON THE BUS:**

- Clock speed
- Clock tolerance
- Node delay

**GLOBAL SETTINGS OF THE BUS:**

- Initial bitrate
- Data bitrate
- Initial sample point
- Data sample point

### What are these?

We've talked about the clock speed and tolerance, but **what is node delay?**

- The node delay is the delay caused by the transciever.In the transciever datasheet you will find it as "propogation delay" or "loop delay" or as "delay time from TXD LOW to RXD LOW". 

Bitrates are also mentioned above, but what are sample points?

- Sample point is at what time point in the bittime (in %) do you measure the value of the bit. So lets say 1 bittime is 10 ns. At the beginning of the bittime the signal is still changing, so you have to measure the value at the end of the bittime. But if you consider the inperfection of the timer clock, you may run out of the bittime if the clock misfires. Sample-Point is given in %, from 50 to 90 (**87.5 % is the preferred value used by CANopen and DeviceNet**, 75% is the default value for ARINC 825). When communicating only between microcontrollers, keeping to 87.5% is not important, but all controller has to be close to the given sample point. In this example a sample point of 80% is used.

This sample point also states the max length of the CAN-BUS, but we only need maximum of 10m length so any setting may work.

**After selecting all the right values, the Kvaser calculator will give us the timing parameters.**

>[!IMPORTANT]
>Up to this point every data has to be configured in the CubeMX in the Clock configuration and in the FDCAN1 configuration. Example configuration is shown in the below picure.\
>![alt](./CubeMX%20configuration%20of%20CAN_ISA.png)

## Priority?

Every can message has an identifier (11bit for standard and 29bit for extended). The lower the value the higher the priority. Why? When two message is being transmitted at the same time,the identifiers has to be different, so the message that has a 1 bit (recessive, passively driven) will cancel transmitting if at the same time the bus is in dominant (0, actively driven) state, meaning someone other with lower ID aka higher priority is present.

## So how to send and receive messages?

In the two projects the CAN_ISA is fully commented, see the codebase for further information!

The basic theory part is that there are filters that dictate if a message is relevant for the device or not. If the message is not valid it gets rejected, but if valid it gets stored in the RX_FIFO. 

For sending you have to add the configured message header and the data variables to the TX_FIFO, wich will be sent as soon as there's tome on the CAN_BUS.

### What codes have been changed regarding the CAN communication?

- fdcan.c ----------> CANFD configuration
- stm32u5xx_it.c ---> Interrupt services for sending data at button press and after reception of valid message

## Links and online resources: 

**ControllersTech Tutorials, wathc before beginning!**
https://www.youtube.com/watch?v=kXyzaaSk6Qs\
https://www.youtube.com/watch?v=sY1ie-CnOR0\
https://controllerstech.com/stm32-fdcan-in-loopback-mode/

**Kvaser CANFD Bit-timing Calculator**
https://www.kvaser.com/support/calculators/can-fd-bit-timing-calculator/\
(https://www.kvaser.com/support/calculators/can-fd-bit-timing-calculator/?v=0.12&nbr=1000000&dbr=1000000&nsjw=10&dtps1=69&dtps2=10&f=80000&t=50&d=215&np=5&dp=5)

**TJA1441 datasheet**
https://www.nxp.com/docs/en/data-sheet/TJA1441.pdf

**FDCAN pheriperal datasheet used in STM32 controllers**
https://www.st.com/resource/en/application_note/an5348-introduction-to-fdcan-peripherals-for-stm32-product-classes-stmicroelectronics.pdf

# ISSUES

TODO: In the Screen1View file the decimals are presented incorrectly. This is corrected in the CAN_LOGGER project!