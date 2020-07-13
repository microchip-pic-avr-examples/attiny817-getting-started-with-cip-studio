<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Getting Started with Core Independent Peripherals on AVR® Microcontrollers

Core Independent Peripherals (CIPs) is a category of peripherals available on many AVR® devices. A CIP is designed to handle its tasks among one or multiple peripherals with no code or supervision from the CPU to maintain the operation. This brings up many advantages, such as providing short and predictable response times between peripherals, reducing the complexity and execution time of the software, as well as the possibility of reduced power consumption.

<br/>This repository will present an application example on how to combine CCL, Event System, RTC and ADC to filter the signal from a button and initiate an ADC conversion core independently. This may help users start building their own projects using CIPs. This example is based on the Application Note [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451) from Microchip and will be performed on a ATtiny817 Xplained Pro board.

## Related Documentation

- [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451)
- [ATtiny817 Device Page](https://www.microchip.com/wwwproducts/en/ATtiny817)

## Software Used

- [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
- [ATtiny DFP](http://packs.download.atmel.com/) 1.4.308 or later
- AVR/GNU C Compiler (Built-in compiler) 5.4.0 or later

## Hardware Used

- [ATtiny817 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/attiny817-xpro)
- Micro-USB cable (Type-A/Micro-B)


## Operation

1. Connect the ATtiny817 Xplained Pro board to the PC using the USB cable.

2. Download the zip file or clone the example to get the source code.

3. Open the .atsln file in Atmel Studio.

4. Using the signal from a mechanical button directly into an application without any form of filtering will in many cases lead to unpredictable behavior, since the signal often transitions several times between high and low each time the button is pushed or released. This is often referred to as bounce. If an application is required to act once each time a mechanical button is pressed, some form of filtering needs to be implemented either in hardware or software, also referred to as debouncing. <br/><br/>*This is already implemented for you. For a complete description on how this is done refer to the document  [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451).*

11. Build the solution and program the ATtiny817. 

## Conclusion
 In this example several CIPs have been studied, such as CCL, Event System, RTC and ADC, so that the users now have an idea of how to start building their own projects using CIPs.
