const int currentPin = A0;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
 
void setup() 
{
  Serial.begin(9600);
  delay(2000);
}
 
void loop()
{
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((offsetVoltage - adcVoltage) / sensitivity);
  
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
 


  delay(2000);

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  
 

  delay(2000);
 
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);
 
  
  delay(2500);
}
