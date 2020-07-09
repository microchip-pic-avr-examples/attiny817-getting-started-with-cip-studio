<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Getting Started with Core Independent Peripherals on AVR® Microcontrollers

Core Independent Peripherals (CIPs) is a category of peripherals available on many AVR® devices. A CIP is designed to handle its tasks among one or multiple peripherals with no code or supervision from the CPU to maintain the operation. This brings up many advantages, such as providing short and predictable response times between peripherals, reducing the complexity and execution time of the software, as well as the possibility of reduced power consumption.
<br/>This repository will present an application example on how to combine CCL, Event System, RTC and ADC to filter the signal from a button and initiate an ADC conversion core independently. This may help users start building their own projects using CIPs. This example is based on the Application Note [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451) from Microchip and will be performed on a ATtiny817 Xplained Pro board.

## Related Documentation

- [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451)
- [ATtiny817 Xplained Pro User Guide](https://www.microchip.com/DS50002684)
- [ATtiny817 Data Sheet](https://www.microchip.com/DS40001901)
- [ATtiny817 Device Page](https://www.microchip.com/wwwproducts/en/ATtiny817)

## Software Used

- [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
- [AVR/GNU C Compiler](http://packs.download.atmel.com/) 
- [Atmel Studio DFP](http://packs.download.atmel.com/) 1.4.308 or later

## Hardware Used

- [ATtiny817 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/attiny817-xpro)
- Micro-USB cable (Type-A/Micro-B)

## Setup

1. Connect the ATtiny817 Xplained Pro board to the PC using the USB cable.


## Operation

1. Download the zip file or clone the example to get the source code.

2. Open the .atsln file in Atmel Studio.

3. Using the signal from a mechanical button directly into an application without any form of filtering will in many cases lead to unpredictable behavior, since the signal often transitions several times between high and low each time the button is pushed or released. This is often referred to as bounce. If an application is required to act once each time a mechanical button is pressed, some form of filtering needs to be implemented either in hardware or software, also referred to as debouncing.

<br/>*The project is already configured for you, but the next steps will explain what has been implemented in order for the system to work. Fora complete description follow the document  [AN2451 - Getting Started with Core Independent Peripherals on AVR® Microcontrollers](https://www.microchip.com/DS00002451).*

4. Event System (EVSYS) Setup: <br/>The application example uses the Event System to route the signals to and from the CCL for maximum flexibility. The button signal and a suitable clock signal must be routed to the event inputs of a LUT, while the output from this LUT must be routed to the ADC event input.<br/> The event output from the Periodic Interrupt Timer (PIT) unit in the Real-Time Counter (RTC) is suitable as a clock signal. If the RTC clock is set to 32 kHz, a good starting point would be to select the PIT output event corresponding to dividing the RTC clock by 1024 as the source for one event channel. The input event selected as IN[2] for the LUT may then be configured to be a user of this channel.
<br/>The I/O pin connected to the button may be configured as the event generator for a second event channel. The remaining available LUT input event may then be configured as a user of this channel. The I/O pin may also be configured as an input with its associated pull-up resistor enabled if there is no external pull-up resistor connected.
<br/>To trigger an ADC conversion from the filtered button signal, the LUT output may be configured as the generator for a third event channel, while the ADC may be configured as a user.

5. Real Time Counter (RTC) Setup: <br/> The RTC module includes a function called PIT. The PIT uses the same clock source as the rest of the RTC, and when enabled, provides a set of output events in the form of clock signals with periods corresponding to n times the RTC clock period. In order to use the PIT output events, the PIT must be enabled in the RTC module.

6. Configurable Custom Logic (CCL) Setup: <br/> Each Lookup Table (LUT) in the CCL includes a filter that can be used to synchronize or filter the LUT output. The filter is by default clocked by the peripheral clock signal, but an alternative clock signal provided to the LUT on IN[2] can be used. By providing a suitable clock signal on IN[2] and the signal from a mechanical button on either IN[0] or IN[1], a single LUT can be used to filter glitches on the button signal that would otherwise cause unwanted behavior.
<br/> The LUT inputs can be selected from a large number of different signals, among them two different event signals. For maximum flexibility in terms of sources for the button and clock signal, the two event signals may be selected as inputs. One of the event inputs must be assigned to IN[2] to be used as an alternative clock signal. The other event signal may be assigned to one of the two remaining inputs, while the unused input may be configured as Masked.
<br/>To configure a LUT for this purpose, its filter and alternative clock source features must be enabled. The CCL Setup is completed by enabling the LUT and the CCL.

7. Analog-to-Digital Converter (ADC) Setup: <br/>One of the internal analog sources available to the ADC is the voltage from the on-board temperature sensor. To configure the ADC to sample the temperature sensor, the ADC reference may be set to the internal reference, and the sensor may be selected as the ADC input signal. Then, the ADC voltage reference may be set to 1.1V and enabled in the Voltage Reference (VREF) module. <br/>By setting the ADC up as described, a 10-bit converted voltage value will be available in the ADC Result register when the result ready interrupt is requested. To convert the result to a temperature value, it must be corrected by an offset and a gain factor included in the signature row of the device. For simplicity, this
correction is not included in the application example

8. Universal Synchronous and Asynchronous Receiver and Transmitter (USART)
Setup: <br/>For verification and testing purposes, it can be helpful to transmit data to a serial terminal for visualization. To configure the USART to send data over its TX (transmit) pin, it is required to only enable the transmitter, set the baud rate, and configure the USART TX pin as an output. By using the USART driver provided by Atmel START, the baud rate is calculated and configured by the driver.


9. CPU Details: <br/>Since the result ready interrupt is enabled in the ADC and the application example may store and transmit ADC results via the USART, the correct Interrupt Service Routine (ISR) may be implemented along with a mechanism to forward data to the USART.

10. Build the solution and program the ATtiny817. 

## Conclusion
 In this example several CIPs have been studied, such as CCL, Event System, RTC and ADC so that the users now have an idea of how to start building their own projects using CIPs.
