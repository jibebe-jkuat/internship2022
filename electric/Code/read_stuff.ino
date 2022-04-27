float singleValue, samples;
int adc;
int throttle = A2;

void setup(){
     Serial.begin(9600);
    
}
void loop(){
  samples = 0.0;
  for (int x = 0; x < 150; ++x){          //Get 10 samples
     singleValue = analogRead(throttle);     //Read current sensor values
     Serial.print(singleValue);
     Serial.print(" ");
     samples += singleValue;        //Add samples together
     delay (1);                              // let ADC settle before next sample 5ms
     }
    
     adc  = samples/150.0 ;    //reading analog voltage and storing it in an integer
     Serial.println(adc); 
     adc  = map (adc, 0, 1023, 0, 255);
     Serial.println(adc);
     delay(500);
}
     
 