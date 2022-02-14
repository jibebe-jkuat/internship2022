//---------------MAG SENSOR-----------
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);





//-----------------GPS-----------------
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RXPin = 0, TXPin = 1;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600


TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXPin, TXPin); // the serial interface to the GPS device


  float gps_latitude = 0.00;
  float gps_longitude = 0.00;
  float gps_altitude = 0.00;
  int gps_year = 0;
  int gps_month = 0;
  int gps_date = 0;
  int gps_hour = 0;
  int gps_minute = 0;
  int gps_second = 0;

  //----mag sensor---
  float mag_x = 0.00;
  float mag_y = 0.00;
  float mag_z =0.00;

  

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  


   /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }

  
}

void loop() {
  sensors_event_t event; 
  mag.getEvent(&event);
  mag_x = event.magnetic.x; 
  mag_y = event.magnetic.y;
  mag_z = event.magnetic.z;


  
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        gps_latitude = gps.location.lat();
        gps_longitude = gps.location.lng();
        if (gps.altitude.isValid())
           gps_altitude = gps.altitude.meters();
        else
           gps_altitude = -1;
      } else {
        Serial.println(F("location: INVALID"));
      }

   

      
      if (gps.date.isValid() && gps.time.isValid()) {
        gps_year = gps.date.year();
        gps_month = gps.date.month();
        gps_date = gps.date.day();
        gps_hour = gps.time.hour();
        gps_minute =  gps.time.minute();
        gps_second = gps.time.second();
        
      } else {
        Serial.println(F("DATE AND TIME INVALID"));
      }


     



       float heading = atan2(mag_y, mag_x);
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






    
      Serial.println();
      Serial.println("----LOCATION-------");
      Serial.print("Latitude: ");Serial.println(gps_latitude);
      Serial.print("Longitude: ");Serial.println(gps_longitude);
      Serial.print("Altitude: ");Serial.println(gps_altitude);
      Serial.println("----COMPASS--------");
      Serial.print("X: ");Serial.println(mag_x);
      Serial.print("Y: ");Serial.println(mag_y);
      Serial.print("Z: ");Serial.println(mag_z);
      Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
