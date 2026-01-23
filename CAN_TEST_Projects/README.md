# CANFD Communication example code

This project is made to showcase how the canFD protokol works and how to properly program it for stm32 microcontrollers. 

 ## CANFD Configuration

The first, very important step, is planning. Relevant questions are:
1. At what initial bitrate?
2. At what data bitrate?
3. What clock source?
4. What clock speed(Hz)?

### This section will answer all of these questions!

## 1. and 2., the bitrates?

The limitations: in the CANFD protocoll the initial (header) part can only go up to 1mbit/s, and the data part up to 8 mbit/s. This is also maximalized by the used transciever, usually limiting the datarate down to 2-5mbit/s. **Higher datarate is not always better!** Higher datarate brings up problems as hardvare limitations, but more on that later. 

The conventional initial and datarate notation is the following: **initialrate @ datarate**. (In our case it's 1mbps @ 4mbps.)

### Why these rates? The initial is the maximum for speed, 4mbps datarate is because the transciever is only capable of 5mbps and the clocksource on one of the LCD is 80MHz, limiting it to only 4mbps at max.

## 3. and 4. the clocks?

Choosing the clock source is important because the clock tolerance has to be made into consideration. Clock tolerance is measured in ppm (parts per million) and shows the maximum deviation from the stated frequency. When using internal clock source, the STM **datasheet of the contoller** will state it's tolerance, but **you need to convert it to ppm!** *(dw, the value will be up in the 1-9k range)*

When using external oscillator as clock source, you can use the universal 50 ppm, most of them only  deviates with only that amount, so **it is advised to use external clock source.**

For the clock speed, the easiest to go for the max bitrate*20 in Hz, so 4 000 000 bit/s needs 80 000 000Hz --> 4mbit/s goes with 80MHz;

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

- Sample point is at what time point in the bittime (in %) do you measure the value of the bit. So lets say 1 bittime is 10 ns. At the beginning of the bittime the signal is still changing, so you have to measure the value at the end of the bittime. But if you consider the inperfection of the timer clock, you may run out of the bittime if the clock misfires. Sample-Point is given in %, from 50 to 90 (**87.5 % is the preferred value used by CANopen and DeviceNet**, 75% is the default value for ARINC 825). When communicating only between microcontrollers, keeping to 87.5% is not important, but all controller has to be close to the given sample point. In this example a sample point of 80% is used. Also note that the USB-CANFD-TOOL can only work at 80%, that is the reason for the setting. (cheap chinese shit)

This sample point also states the max length of the CAN-BUS, but we only need maximum of 10m length so any setting should work.

**After selecting all the right values, the Kvaser calculator will give us the timing parameters.**

> [!NOTE]
> For Delay Compensation to work the **data prescaler has to be 1 or 2!**\
> If 80MHz cannot be set for some reason in the stm32 configuration, than you can use the **clock divider in the FDCAN1 configuration**\
> All the values are called the same in the MX configurator as the Kvaser calculator.\
> For the project's calculations there's a second link with all the used values.

>[!IMPORTANT]
>Up to this point every data has to be configured in the CubeMX in the Clock configuration and in the FDCAN1 configuration. Example configuration is shown in the below picure.\
>![alt](./CubeMX%20configuration%20of%20CAN_TEST_50.png)

## What is TDC, aka Transciever Delay Compensation?

In the CAN Network when you are the transmitter, every other device has to be reciever. For this, somehow the can devices has to know if someone may started transmitting data at the same time as you. For this the can pheripheral when transmittin via the CAN_TX pin, reads back the values on the CAN_RX pin. If the message in a given point in time had a recessive (1, passively driven) bit, but the bus was in dominant (0, actively driven) state, than a CANBUS_Error is created and the device (you) stop transmitting. This usually means that a higher priority message is incoming.

The problem with the CANFD protocol is that the bittime is way shorter than the daley that the transmitter loop delay. What it means? Lets say through the TJA1441 example:

**The first bit's timeline:**
           
                  ~0ns         102.5ns       ~0ns 
        CAN_TX ----------> Transciever_TX ----------> CANBUS |
        CAN_RX <---------- Transciever_RX <---------- CANBUS |
                  ~0ns         115.5ns       ~0ns       

So this way you can see that around 215ns delay is existent from write to read. This means that with a bittime of 25ns around the 9th bit is already started being transmitted.

**TDC is made to compensate for this delayed readback.**

The HAL_Driver has 2 dedicated function for configuring and starting the TDCO registers:

`HAL_FDCAN_ConfigTxDelayCompensation(*hfdcan, TdcOffset, TdcFilter);`
`HAL_FDCAN_EnableTxDelayCompensation(*hfdcan);`

In the Config function `TdcOffset` gives the secondary sample point, wich is the readback sample point and `TdcFilter` is the minimum possible delay. These have to be calculated with the below equasion:

$$
TDCO = SecondarySamplePointPosition \\% / (ProtocolClockPeriod (ns) * (Bitrate(Mbits) /1000)) 
$$

and

$$
TDCF = TDCO + (LoopDelay(ns) / TimeQuanta(ns))
$$

*calculate ONLY the whole part of the equasion!*

## Priority?

Every can message has an identifier (11bit for standard and 29bit for extended). The lower the value the higher the priority. Why? When two message is being transmitted at the same time,the identifiers has to be different, so the message that has a 1 bit (recessive, passively driven) will cancel transmitting if at the same time the bus is in dominant (0, actively driven) state, meaning someone other with lower ID aka higher priority is present.

## So how to send and receive messages?

In the two projects the CAN_TEST_50 is fulli commented, see the codebase for further information!

The basic theory part is that there are filters that dictate if a message is relevant for the device or not. If the message is not valid it gets rejected, but if valid it gets stored in the RX_FIFO. 

For sending you have to add the configured message header and the data variables to the TX_FIFO, wich will be sent as soon as there's tome on the CAN_BUS.

> [!IMPORTANT]
> Only CAN_TEST_50 is commented for ease of understanding, project 101 is much more complicated as it uses 2 cores!

### What codes have been changed regarding the CAN communication?

- fdcan.c ----------> CANFD configuration
- stm32u5xx_it.c ---> Interrupt services for sending data at button press and after reception of valid message

## Links and online resources: 

**ControllersTech Tutorials, wathc before beginning!**
https://www.youtube.com/watch?v=kXyzaaSk6Qs\
https://www.youtube.com/watch?v=sY1ie-CnOR0\
https://controllerstech.com/stm32-fdcan-in-loopback-mode/

**Kvaser CANFD Bit-timing Calculator**
https://www.kvaser.com/support/calculators/can-fd-bit-timing-calculator/
(https://www.kvaser.com/support/calculators/can-fd-bit-timing-calculator/?v=0.12&nbr=1000000&dbr=4000000&nsjw=5&dtps1=7&dtps2=2&f=80000&t=50&d=215&np=1&dp=1)

**TJA1441 datasheet**
https://www.nxp.com/docs/en/data-sheet/TJA1441.pdf

**FDCAN pheriperal datasheet used in STM32 controllers**
https://www.st.com/resource/en/application_note/an5348-introduction-to-fdcan-peripherals-for-stm32-product-classes-stmicroelectronics.pdf

**What is TDC?** 
https://onlinedocs.microchip.com/oxy/GUID-DDF2C9BC-07FB-4ABF-938A-774B157B4519-en-US-8/GUID-34D318BC-78F6-41C9-B394-6F24B613118E.html

**How to calculate TDC?** 
https://www.st.com/resource/en/technical_note/tn1346-spc58x-configuring-can-and-canfd-bit-timing-parameters-stmicroelectronics.pdf

