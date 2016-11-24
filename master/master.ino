#include <Servo.h>                        //include servo library
#include <Stepper.h>                      //include stepper library

const int stepsPerRevolution = 48;        //stepper steps per revolution

class Slap                                //class definition
{
  Servo slap;                             //define variables
  int pos,
      servoIncrement,
      updateInterval;
  unsigned long lastUpdate;
  
  public:
  
  Slap (int interval, int increment)      //constructor with input parameters interval and increment
  {
    updateInterval = interval;
    servoIncrement = increment;
  }
  
  void Attach (int pin)                   //Attach member function - assigns pin to Slap object
  {
    slap.attach(pin);
  }
  
  void Detatch ()                         //Detach member function - releases pin from slap object
  {
    slap.detach();
  }
  
  void Update()                           //Update member function - moves servo
  {
    if((millis()-lastUpdate) > updateInterval)  //if update interval exceeded
    {
      lastUpdate = millis();              //update timestamp
      pos += servoIncrement;              //update position
      slap.write(pos);                    //move servo to position
      Serial.println(pos);                //print position
      if ((pos >= 180 ) || (pos <= 0))    //if position is outside range of motion...
      {
        servoIncrement = -servoIncrement; //reverse direction
      }
    }
  }
  
};

class Motor                               //class definition
{
  int motorPin;                           //define variable
  
  public:

  Motor (int pin)                         //constructor with input parameter pin
  {
    motorPin = pin;                       //initialize variables
    (motorPin, OUTPUT);
  }

  void Update (int motorSpeed)            //Update member function - moves motor
  {
    if (motorSpeed >= 0 && motorSpeed <= 255) //validates motor speed
    {
      analogWrite(motorPin, motorSpeed);  //move motor om pin positioin at speed
      Serial.println(motorSpeed);         //print speed
    }
  }
};

class Ultra                               //class definition
{  
  long duration,                          //define variables
       distance,
       Sensor;
  int input,
      output;
       
  public:

  Ultra (int in, int out)                   //constructor with input parameters in and out
  {
    input = in;                             //define variables
    output = out;

    pinMode(input, INPUT);                  //set pin modes
    pinMode(output, OUTPUT);
  }

  long Sonar (int trigPin, int echoPin)     //Sonar member function - queries distance
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    Serial.println(distance);
  }

  
};

Motor right (5);                          //define right motor object on pin 5
Motor left (6);                           //define left motor object on pin 6
Slap slapper(8,5);                        //define slapper object to update 5 positions every 8ms
Stepper steering (stepsPerRevolution, 0, 1, 2, 3); //define stepper motor on pins 0 - 3
Ultra leftU (7, 8);                       //define left ultrasonic on pins 7 & 8
Ultra frontU (9,10);                      //define front ultrasonic on pins 9 & 10
Ultra rightU(11,12);                      //define right ultrasonic on pins 11 & 12
 
void setup() 
{ 
  Serial.begin(9600);                     //serial connection for debugging
  slapper.Attach(13);                      //attach slapper to pin 13
  steering.setSpeed(120);
} 
 
void loop() 
{ 
  int rtMotorSpeed = 0,                     //variables determined by algorithm
      ltMotorSpeed = 0,
      things = 0,
      otherthings = 0,
      happening = 0,
      steps = 5,
      steerPosition = 0;
  long RUD = 0,
       FUD = 0,
       LUD = 0;
  Serial.println("Left Ultra");
  LUD = leftU.Sonar (7,8);                      //query left ultrasonic
  Serial.println("Right Ultra");
  FUD = frontU.Sonar (9,10);                    //query front ultrasonic
  Serial.println("Front Ultra");
  RUD = rightU.Sonar (11,12);                   //query right ultrasonic
  if ((LUD-RUD)>10)                             //if veering right
  {
    steering.step(-1*steps);                    //steer left
    steerPosition -= steps;
    Serial.println("Steering Position");
    Serial.println(steerPosition);
    Serial.println("Left Motor Speed");
    left.Update(ltMotorSpeed);                  //spin left motors slower
  }
  else if ((RUD-LUD)>10)                        //if feering left
  {
    steering.step(steps);                       //steer right
    steerPosition += steps;
    Serial.println("Steering Position");
    Serial.println(steerPosition);
    Serial.println("Right Motor Speed");
    right.Update(rtMotorSpeed);                   //spin right motors slower
  }
  if (otherthings == happening)                 //if large delta in distance
  {
    Serial.println("Servo Position");
    slapper.Update();                            //call Update meber function to move servo
  }
} 
