const int pwm = 2 ;    //naming pin 2 as ‘pwm’ variable 
const int adc = 0 ;   //naming pin 0 of analog input side as ‘adc’
const int delayTime = 9000;
int currentadc = 0;
int delayStep = (delayTime/255);

void setup()
{
     pinMode(pwm,OUTPUT) ;  //setting pin 2 as output
     Serial.begin(9600);
    
}
void loop()
{
     int adc  = analogRead(0) ;    //reading analog voltage and storing it in an integer 
     adc = map(adc, 0, 1023, 0, 255); 

    
     if (currentadc != adc){
        if (currentadc < adc){
          Serial.print("Increasing"); 
          for ( int i = currentadc; i <= adc ; i++){
            analogWrite(pwm,i) ; 
            delay (delayStep);
          } 
        }
        
        else if (currentadc > adc){
          Serial.print("Decreasing"); 
          for ( int i = currentadc; i >= adc ; i--){
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

//       for ( int i = 0; i <= adc ; i++){
//        analogWrite(pwm,i) ; 
//        delay (delayStep);
//       }    
