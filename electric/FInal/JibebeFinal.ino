/*
 * 
 * Jibebe Final
The Final Code for the Jibebe Tricycle Electrical Susbsystem.

Jibebe Github: https://jibebe-jkuat.github.io/

Authors:
Paul Moses - Computer Engineer
Amos Wanene - Electrical Engineer
Brian Willy - Electrical Engineer


Board to be used: Arduino Due
Functions of the Code:
*******1. Speed and Throttle Control for BLDC Motor

Throttle ----------------------> Arduino -------------------> Motor Speed Controller
Uses inbuilt ADC to read throttle value and uses DAC to write analog value to Speed Controller 

Input -------> throttle Value
Output -----> Corrected Speed Value

Functions used: readThrottle and writeSpeed

*******2. Battery Percentage Determination
*
Uses Current Sensors and coloumb counting algorithm to calculate the battery Percentage.
Input ----> Currrent Sensor Value
Output ----> Battery Percentage

This fucntion controls the value of the battery Percentage variable

*****3. Velocity Determination
*
*Uses Stationary Hall Sensor and rotating magnet to determine the speed of the rotating wheel of the tricyle

Input ------> Hall Sensor Trips by Magnet
Output -----> Speed in km/h

*****4. Speed and Battery percentage display on LCD

Input ---> Battery percentage and Speed derived from previous functions
Output ---> Display values and text describing them to an LCD.
*/

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
