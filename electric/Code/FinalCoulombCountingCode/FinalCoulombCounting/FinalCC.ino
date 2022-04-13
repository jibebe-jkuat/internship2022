//float       offsetVoltage = 2163.086;
float         offsetVoltage = 2539.062;
int           currentPin = A0;
int           singleValue, adcValue, rawSensorValue;
float         sensitivity = 33;
float         currentValue, adcVoltage, samples;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const int     period = 1000;  //the value is a number of milliseconds
const byte    ledPin = 13;    //using the built in LED
double        totalCoulumbs = 0.0;
void          getCoulombs (float current);

void setup(){
  Serial.begin(9600);
  pinMode (currentPin, INPUT);
  startMillis = millis();  //initial start time
}


void loop(){
samples = 0.0;
  for (int x = 0; x < 200; ++x){ //Get 190 samples
  singleValue = analogRead(currentPin);     //Read current sensor values   
  samples     = samples + singleValue;  //Add samples together
  delay (5); // let ADC settle before next sample 5ms
}

  adcValue     = samples / 200.0;
  adcVoltage   = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
 
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
  //delay(20);

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  //delay(20);
 
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);
  //delay(10);
  getCoulombs(currentValue);
}
 
void getCoulombs(float current)
{
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if ( (currentMillis - startMillis) < period){  //test whether the period has elapsed, if not, return.
    return;
  }
  
    totalCoulumbs = totalCoulumbs + current;
    Serial.print("Total Coulumbs = ");
    Serial.println(totalCoulumbs);
    Serial.print("Total Ah = ");
    Serial.println(totalCoulumbs/3600.0);
    //digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
}
