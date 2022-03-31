 volatile byte rotation; // variale for interrupt fun
 float timetaken,rpm,dtime;
 int v;
 unsigned long pevtime;
 void setup()
 {
   Serial.begin(9600);
   attachInterrupt(0, magnet_detect, RISING);//secound pin of arduino used as interrupt
   rotation = 0;
   rpm = 0;
   pevtime = 0;
 }
 void loop()
 {
if(millis()-dtime>1000) //to drop down to zero when braked.
v = (0.035) * rpm * 0.37699;  // ACTUAL CODE KM/hr
  }
 
 void magnet_detect()//Called whenever a magnet is detected
 {
  rotation++;
  dtime=millis();
  if(rotation>=2)
 {
    timetaken = millis()-pevtime; //time in millisec
    rpm=(1000/timetaken)*60;    
    pevtime = millis();
    rotation=0;
 Serial.write(v);
 }
 }
