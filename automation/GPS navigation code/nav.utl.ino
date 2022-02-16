
//-----------------------GPS------------------------
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RXPin = 18, TXPin = 19;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600
float latitude;
float longitude;
float latc,logc;
float bearing;
float heading;
float latd=-1.094897,logd=37.0188916;

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXPin, TXPin); // the serial interface to the GPS device
//---------------------COMPASS--------------
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
//------------------- MOTOR----------------------------
#include <AFMotor.h>   // import motor library
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance 

// creating oblects for each motor
AF_DCMotor rightFront(1);
AF_DCMotor leftFront(2);
AF_DCMotor leftBack(3);
AF_DCMotor rightBack(4);


byte motorSpeed =200;
byte maxDist = 200;
byte stopDist = 40;



void setup(void) 
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
gpsSerial.begin(GPSBaud);

// turn on all the motors 
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed);
  leftBack.setSpeed(motorSpeed);
  rightBack.setSpeed(motorSpeed);
  
  // making sure all the motors are stopped 
   rightFront.run(RELEASE);
   leftFront.run(RELEASE);
   leftBack.run(RELEASE);
   rightBack.run(RELEASE);  
  
  
}

void loop()
{
 headingcal();
 delay(200);
 gpsdata();
 delay(200);
 gpsheading();
 delay(200);
 steering();
 delay(200);
 }

void headingcal(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  

}

void gpsdata()
{
 if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  Serial.println(F("No GPS data received: check wiring"));
  latc= latitude;
  logc=  longitude;

}  

void gpsheading()
{
  float x,y,deltalog,deltalat;
  deltalog= logd-logc;
  deltalat=latd-latc;

  x=cos(latd)*sin(deltalog);
  y=(cos(latc)*sin(latd))-(sin(latc)*cos(latd)*cos(deltalog));
  
  bearing=(atan2(x,y))*(180/3.14);
  Serial.print("bearing");
  Serial.println(bearing);

  float a,d,c;
  a=(((sin(deltalat/2)))*(sin(deltalat/2))) + ((cos(latc))*(cos(latd))* (((sin(deltalog/2)))*(sin(deltalog/2)))  );
  c=2*(atan2(sqrt(a),sqrt(1-a)));
  d=6371*c; 
//Serial.println(d);  
 }

 
//---------------------------------------------------------
void accelerate()                 //Function to accelerate the motors from 0 to full speed
{
  for (int i=0; i<255; i++)     //Loop from 0 to full speed
  {
  rightFront.setSpeed(i);
  leftFront.setSpeed(i);
  leftBack.setSpeed(i);
  rightBack.setSpeed(i);
   
  }
}

//-----------------------------------------------------
void decelerate()                                 //Function to decelerate the motors from full speed to zero
{
  for (int i=255; i!=0; i--)               //Loop from full speed to 0
  {
  rightFront.setSpeed(i);
  leftFront.setSpeed(i);
  leftBack.setSpeed(i);
  rightBack.setSpeed(i);
  }
 }
//-----------------------------------------------------------
void moveForward()      //SET ALL MOTORS TO MOVE FORWARD 
{
   rightFront.run(FORWARD);
   leftFront.run(FORWARD);
   leftBack.run(FORWARD);
   rightBack.run(FORWARD);
}
//------------------------------------------------------
void stopMove()                                   //Set all motors to stop
{
   rightFront.run(RELEASE);
   leftFront.run(RELEASE);
   leftBack.run(RELEASE);
   rightBack.run(RELEASE);
}
//----------------------------------------------------------
void turnLeft(int duration)                                 //Set motors to turn left for the specified duration then stop
{
   rightFront.run(FORWARD);
   leftFront.run(RELEASE);
   leftBack.run(RELEASE);
   rightBack.run(FORWARD);
  
}
//--------------------------------------
void turnRight(int duration)                                //Set motors to turn right for the specified duration then stop
{
   rightFront.run(RELEASE);
   leftFront.run(FORWARD);
   leftBack.run(FORWARD);
   rightBack.run(RELEASE);
}

void steering()
{
float finalv;
finalv=heading/bearing;
Serial.print("finalv: ");
Serial.println(finalv);
  
if(finalv>=0&&finalv<=1)
{
  moveForward();
}

else if(finalv >1 && finalv <=8)
{
  turnLeft(400);
}

else if(finalv <=13 && finalv >=8)
{
  turnRight(400);
}

else if(logd==logc && latc==latd)
{
  stopMove();
}  
}

 
