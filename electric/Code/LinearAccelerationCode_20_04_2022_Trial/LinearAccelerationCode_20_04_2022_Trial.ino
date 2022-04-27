const int pwm       = 3 ;    //naming pin 2 as ‘pwm’ variable 
const int delayTime = 5000;
const int throttle  = A0;
int currentadc = 0;
int delayStep  = (delayTime/255);
int adc = 0;
float samples;
int singleValue;

void setup(){
     pinMode(throttle, INPUT);
     pinMode(pwm, OUTPUT) ;  //setting pin 2 as output
     Serial.begin(9600);
    
}

void loop(){
  samples = 0.0;
     for (int x = 0; x < 10; ++x){          //Get 10 samples
     singleValue = analogRead(throttle);     //Read current sensor values
     Serial.print(singleValue);
     Serial.print(" ");
     samples += singleValue;        //Add samples together
     delay (1);                              // let ADC settle before next sample 5ms
     }
    
     Serial.println(" ");
     adc = samples / 10.0;
     Serial.println(adc);
     adc = adc - 173;
     adc = map(adc, 0, 1023, 0, 255);
     Serial.println(adc);

     if (currentadc - adc){
        if (currentadc < adc){
          Serial.println("Increasing"); 
          for (int i = currentadc ; i <= adc ; i++){
            analogWrite(pwm,i) ; 
            delay (delayStep);
          } 
        }
        
      else if (currentadc > adc){
          Serial.print("Decreasing"); 
          for (int i = currentadc; i >= adc ; i--){
            analogWrite(pwm,i) ; 
            delay (delayStep);
          }
        }
       currentadc = adc;
     }
/*
----------map funtion------------the above funtion scales the output of adc, which is 10 bit and gives values btw 0 to 1023, in values btw 0 to 255 form analogWrite funtion which only receives  values btw this range
*/    
}


