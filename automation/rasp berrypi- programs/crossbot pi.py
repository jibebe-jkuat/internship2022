#Import time library
#from RPIO import PWM
import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)                    # programming the GPIO by BCM pin numbers



#  ultrasonic pins
TRIG = 17
ECHO = 27

# motor pins

leftfront=16
leftback=12
rightfront=21
rightback=20

#servo motor 
myservo=17


GPIO.setup(myservo,GPIO.OUT)                    #initialize SERVO pin
pwm= GPIO.PWM(myservo,50)
pwm.start(2.5)


pwm.ChangeDutyCycle(6.5)# neutral  deg position

GPIO.setup(TRIG,GPIO.OUT)                  # initialize GPIO Pin as outputs
GPIO.setup(ECHO,GPIO.IN)                   # initialize GPIO Pin as input

GPIO.setup(leftfront,GPIO.OUT)
GPIO.setup(leftback,GPIO.OUT)
GPIO.setup(rightfront,GPIO.OUT)
GPIO.setup(rightback,GPIO.OUT)
time.sleep(5)

def stop():
    print('stop')
    GPIO.setup(leftfront,0)
    GPIO.setup(leftback,0)
    GPIO.setup(rightfront,0)
    GPIO.setup(rightback,0)

def forward():
    GPIO.setup(leftfront,1)
    GPIO.setup(leftback,0)
    GPIO.setup(rightfront,1)
    GPIO.setup(rightback,0)
    print("forward")

def left():
    GPIO.setup(leftfront,0)
    GPIO.setup(leftback,1)
    GPIO.setup(rightfront,1)
    GPIO.setup(rightback,0)
    print("left")

def right():
    GPIO.setup(leftfront,1)
    GPIO.setup(leftback,0)
    GPIO.setup(rightfront,0)
    GPIO.setup(rightback,1)
    print("right")

def back():
    GPIO.setup(leftfront,0)
    GPIO.setup(leftback,1)
    GPIO.setup(rightfront,0)
    GPIO.setup(rightback,1)
    print("back")

def distmeas():
    print("Distance measurement in progress")

    GPIO.setup(TRIG,GPIO.OUT)
    GPIO.setup(ECHO,GPIO.IN)
    GPIO.output(TRIG,False)
    print("waiting for sensor to settle please")
    time.sleep(2)

    GPIO.output(TRIG,True)
    time.sleep(0.00001)
    GPIO.output(TRIG,False)

    while GPIO.input(ECHO)==0:
        pulse_start=time.time()

    while GPIO.input(ECHO)==1:
        pulse_end=time.time()


    pulse_duration = pulse_end - pulse_start

    distance = pulse_duration * 17150

    distance = round(distance,2)

    print(f"Distance :{distance}cm")
    return distance

    


def lookleft():
    pwm.ChangeDutyCycle(12.5)# left -90 deg position
    left_distance= distmeas()
    return left_distance

def lookright():
    pwm.ChangeDutyCycle(2.5)# right +90 deg position
    right_distance = distmeas()
    return right_distance 

def lookforward():
    pwm.ChangeDutyCycle(6.5)# neutral
    forward_distance = distmeas()
    return forward_distance 


  
while True:

  distanceRight = 0
  distanceLeft = 0
  time.sleep(0.05)

  distance = lookforward()

  if (distance <= 40):
    stop()
    print("STOP")
    time.sleep(0.3)
    back();
    print("REVERSE")

    time.sleep(0.4)
    stop()
    time.sleep(0.3);
    distanceRight = lookRight()
    time.sleep(0.3)
    distanceLeft = lookLeft()
    time.sleep(0.3);

    if (distanceRight >= distanceLeft):
      right()
      print("TURNING RIGHT")
      stop()
      
    else:   
        left()
        print("TURNING LEFT")
        stop();
    

  else:
    forward(); 
    print("FOWARD")

  













