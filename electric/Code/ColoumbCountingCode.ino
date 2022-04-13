unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const int period = 1000;  //the value is a number of milliseconds
const byte ledPin = 13;    //using the built in LED
float current = .5;
float totalCoulumbs = 0.0;

void setup()
{
  Serial.begin(9600);  //start Serial in case we need to print debugging info
  pinMode(ledPin, OUTPUT);
  startMillis = millis();  //initial start time
}

void loop()
{
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    totalCoulumbs = totalCoulumbs + current;
    Serial.print("Total Coulumbs = ");
    Serial.println(totalCoulumbs);
    Serial.print("Total Ah = ");
    Serial.println(totalCoulumbs/3600.0);
    digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}
