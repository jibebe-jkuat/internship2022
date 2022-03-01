#include <AFMotor.h>   // import motor library
#include <Servo.h>      // import servo library

#define echoPin 52
#define trigPin 53

const int buzzer = 51;   //buzzer

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance 

// creating oblects for each motor
AF_DCMotor rightFront(1);
AF_DCMotor leftFront(2);
AF_DCMotor leftBack(3);
AF_DCMotor rightBack(4);


Servo myservo;

byte motorSpeed =70;
byte maxDist = 150;
byte stopDist = 30;

void setup()
{  
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

   myservo.attach(10);
   
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

   Serial.begin(9600);
  
  }

void loop() 
{
 myservo.write(90);                            //Set the servo to look straight ahead
 
  delay(750);
  int distance = getDistance();                   //Check that there are no objects ahead
  if(distance >= stopDist)                        //If there are no objects within the stopping distance, move forward
  {
    moveForward();
  }

  while(distance >= stopDist)                     //Keep checking the object distance until it is within the minimum stopping distance
  {
    distance = getDistance();
    delay(250);
  }
  stopMove();                                     //Stop the motors
  int turnDir = checkDirection();                 //Check the left and right object distances and get the turning instruction
  Serial.print(turnDir);
  switch (turnDir)                                //Turn left, turn around or turn right depending on the instruction
  {
    case 0:                                       //Turn left
      turnLeft (400);
      break;
    case 1:                                       //Turn around
      turnLeft (700);
      break;
    case 2:                                       //Turn right
      turnRight (400);
      break;
  }
}


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

void moveForward()      //SET ALL MOTORS TO MOVE FORWARD 
{
   rightFront.run(FORWARD);
   leftFront.run(FORWARD);
   leftBack.run(FORWARD);
   rightBack.run(FORWARD);
}

void stopMove()                                   //Set all motors to stop
{
   rightFront.run(RELEASE);
   leftFront.run(RELEASE);
   leftBack.run(RELEASE);
   rightBack.run(RELEASE);
}

void turnLeft(int duration)                                 //Set motors to turn left for the specified duration then stop
{
   rightFront.run(FORWARD);
   leftFront.run(FORWARD);
   leftBack.run(RELEASE);
   rightBack.run(FORWARD);
  
}

void turnRight(int duration)                                //Set motors to turn right for the specified duration then stop
{
   rightFront.run(FORWARD);
   leftFront.run(FORWARD);
   leftBack.run(FORWARD);
   rightBack.run(RELEASE);
}

int getDistance()                                   //Measure the distance to an object
{
  
   // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}


int checkDirection()                                            //Check the left and right directions and decide which way to turn
{
  int distances [2] = {0,0};                                    //Left and right distances
  int turnDir = 1;                                              //Direction to turn, 0 left, 1 reverse, 2 right
  myservo.write(180);                                         //Turn servo to look left
  delay(500);
  distances [0] = getDistance();                                //Get the left object distance
  myservo.write(0);                                           //Turn servo to look right
  delay(1000);
  distances [1] = getDistance();                                //Get the right object distance
  if (distances[0]>=200 && distances[1]>=200)                   //If both directions are clear, turn left
    turnDir = 0;
  else if (distances[0]<=stopDist && distances[1]<=stopDist)    //If both directions are blocked, turn around
    turnDir = 1;
  else if (distances[0]>=distances[1])                          //If left has more space, turn left
    turnDir = 0;
  else if (distances[0]<distances[1])                           //If right has more space, turn right
    turnDir = 2;
  return turnDir;
}
