### Description

NEO-6M GPS Chip
The heart of the module is a NEO-6M GPS chip from u-blox. It can track up to 22 satellites on 50 channels 
and achieves the industry’s highest level of sensitivity i.e. -161 dB tracking, 
while consuming only 45mA supply current. The u-blox 6 positioning engine also boasts a Time-To-First-Fix (TTFF)
of under 1 second. One of the best features the chip provides is Power Save Mode(PSM). 
It allows a reduction in system power consumption by selectively switching parts of the receiver ON and OFF.
This dramatically reduces power consumption of the module to just 11mA making it suitable for power sensitive 
applications like GPS wristwatch. The necessary data pins of NEO-6M GPS chip are broken out to a "0.1″ pitch headers. 
This includes pins required for communication with a microcontroller over UART.

Note:- The module supports baud rate from 4800bps to 230400bps with default baud of 9600.

### Position Fix LED Indicator
There is an LED on the NEO-6M GPS Module which indicates the status of Position Fix.
It’ll blink at various rates depending on what state it’s in.

No Blinking ==> means It is searching for satellites
Blink every 1s – means Position Fix is found

### Output of sensor
Latitude,longitude, date ,time, Altitude

### Pinout
The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 1 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69


### Power 

Note: Use 3.3V to power Vcc
GND - GND

### Library
Please install the included library