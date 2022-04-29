const int pwm       = DAC1 ;    //naming pin 2 as ‘pwm’ variable 
//const int delayTime = 10000;
//int delayStep  = (delayTime/255);
float samples = 0.0f;
int singleValue, currentValue, checkValue, midValue, x, prevValue = 0;
float currentPotVal;
int throttle = A0;




void setup(){
     analogWriteResolution(8);
     //pinMode(throttle, INPUT);
    // pinMode(pwm, OUTPUT) ;  //setting pin 2 as output
     Serial.begin(9600);
    
}

void loop(){

    currentValue = readThrottle();

    if (currentValue != prevValue){
      if (prevValue < currentValue){
        for (x = prevValue; x < currentValue; x++){          //Get 10 samples
          checkValue = readThrottle();
          if (checkValue != currentValue){
            break;
          }
          Serial.print ("Current Value: ");
          Serial.println (currentValue);
          Serial.print ("X: ");
          Serial.println (x);
          analogWrite(pwm, x) ;     
        }
      }

      if (prevValue > currentValue){
        for (x = currentValue; x > prevValue; x--){          //Get 10 samples
          checkValue = readThrottle();
          if (abs (checkValue != currentValue)){
            break;
          }
          Serial.print ("Current Value: ");
          Serial.println (currentValue);
          Serial.print ("X: ");
          Serial.println (x);
          analogWrite(pwm, x) ;     
        }
      }
     prevValue = currentValue;
    }
   
    Serial.print ("Current Value: ");
    Serial.println (currentValue);
    Serial.print ("X: ");
    Serial.println (x);
    
}

int readThrottle(){
  samples = 0.0;

  for (int i = 0; i < 10; i++){          //Get 10 samples
     singleValue = analogRead(throttle);     //Read current sensor values
     samples += singleValue;        //Add samples together
     }
    
    singleValue = samples / 10;
    singleValue = map (singleValue, 0, 1023, 0, 255);
    //singleValue  63;
    return singleValue;
}



