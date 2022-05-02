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

Functions : calculateVelocity
Controls the speed_km_h_value variable

*****4. Speed and Battery percentage display on LCD

Input ---> Battery percentage and Speed derived from previous functions
Output ---> Display values and text describing them to an LCD.
*/

///----------------------------------------PIN ASSIGNMENTS-----------------------------//
int hall_sensor_pin = 2; //digital pin 2
//-------------------------------------------------------------------------------------//

//-----------------------------------------VELOCITY DETERMINATION INITS----------------//
// set number of hall trips for RPM reading (higher improves accuracy)
//100
float hall_thresh = 10.0;
float wheel_diameter = 0.6; // in meters
float speed_km_h_value = 0.0;
//------------------------------------------------------------------------------------//

//-----------------------------------BATTERY PERCENTAGE INITS-------------------------//
float battery_percentage = 0.0;
//-----------------------------------------------------------------------------------//

//-----------------------------------SPEED CONTROL INITS----------------------------//
int speedOutput = DAC1;
float samples = 0.0;
int singleValue, currentValue, checkValue, midValue, x, prevValue = 0;
float currentPotVal;
int throttle = A0;
//---------------------------------------------------------------------------------//

//---------------------------------------LCD INITS-----------------------------------//
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//-----------------------------------------------------------------------------------//



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //------HALL SENSOR
  pinMode(hall_sensor_pin, INPUT); // make the hall sensor pin an input

  //-----LCD 
  lcd.init();  
  lcd.backlight();

  //---SPEED CONTROL
  analogWriteResolution(8);
  

}




void loop() {
  //calculate Velocity
  speed_km_h_value = calculateVelocity();
  battery_percentage = calculateBattPercentage();
  lcdDisplayBattAndSpeed(battery_percentage,speed_km_h_value);
  speedControl();
  delay(1);
  
}


/*-------------------------------------------------------------CALCULATE BATTERY PERCENTAGE ------------------------------------------------------**/

float calculateBattPercentage(){
  float batt_percentage = 0.0;
  return batt_percentage;
}

/*------------------------------------------------------------CALCULATE VELOCITY--------------------------------------------------------------*/
float calculateVelocity(){
  /*Calculate velocity from number of hall sensor trips and returns velocity in km/h*/
  
  // preallocate values for tach
  float hall_count = 1.0;
  float start = micros();
  bool on_state = false;
  // counting number of times the hall sensor is tripped
  // but without double counting during the same trip
  while(true){
    if (digitalRead(hall_sensor_pin)==0){
      if (on_state==false){
        on_state = true;
        hall_count+=1.0;
      }
    } else{
      on_state = false;
    }
    
    if (hall_count>=hall_thresh){
      break;
    }
  }
  
  // print information about Time and RPM
  float end_time = micros();
  float time_passed = ((end_time-start)/1000000.0);
  //Serial.print("Time Passed: ");
  //Serial.print(time_passed);
  //Serial.println("s");
  float rpm_val = (hall_count/time_passed)*60.0;
  //Serial.print(rpm_val);
  //Serial.println(" RPM");
  float speed_km_h = 0.1885 * rpm_val * wheel_diameter; 
  //Serial.print(speed_km_h);
 // Serial.println(" KM/H");
  //delay(1);        // delay in between reads for stability
  return speed_km_h;
}

/**-------------------------------------------------------------SPEED CONTROL-----------------------------------------------------------------**/
int readAnalog(int analogPin){
  samples = 0.0;

  for (int i = 0; i < 10; i++){          //Get 10 samples
     singleValue = analogRead(analogPin);     //Read current sensor values
     samples += singleValue;        //Add samples together
     }
    
    singleValue = samples / 10;
    singleValue = map (singleValue, 0, 1023, 0, 255);
    return singleValue;
}

void speedControl(){
  currentValue = readAnalog(throttle);

    if (currentValue != prevValue){
      if (prevValue < currentValue){
        for (x = prevValue; x < currentValue; x++){          //Get 10 samples
          checkValue = readThrottle();
          if (checkValue != currentValue){
            break;
          }
          analogWrite(speedOutput, x) ;     
        }
      }

      if (prevValue > currentValue){
        for (x = currentValue; x > prevValue; x--){          //Get 10 samples
          checkValue = readThrottle();
          if (abs (checkValue != currentValue)){
            break;
          }
          analogWrite(speedOutput, x) ;     
        }
      }
     prevValue = currentValue;
    }
  
}



/*--------------------------------------------------------------LCD DISPLAY--------------------------------------------------------------------------------------*/
void lcdDisplayBattAndSpeed(float battery_percentage, float speed_km_h){
  String batStr = "BATTERY: ";
  String speedStr = "KM/H: ";

  String final_bat_str = batStr + battery_percentage;
  String final_speed_str = speedStr + speed_km_h;

  lcd.setCursor(0,0); //topLeft
  lcd.print(final_bat_str);
  lcd.setCursor(0,1);//bottomLeft
  lcd.print(final_speed_str);
  
}
