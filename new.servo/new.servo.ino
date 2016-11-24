#include <Servo.h>                      //include servo library

class Slap                              //class definition
{
  Servo slap;                           //define variables
  int pos,
      stepIncrement,
      updateInterval;
  unsigned long lastUpdate;
  
  public:
  
  Slap (int interval, int increment)    //constructor with input parameters interval and increment
  {
    updateInterval = interval;
    stepIncrement = increment;
  }
  
  void Attach (int pin)                 //Attach member function - assigns pin to Slap object
  {
    slap.attach(pin);
  }
  
  void Detatch ()                       //Detach member function - releases pin from slap object
  {
    slap.detach();
  }
  
  void Update()                         //Update member function - moves servo
  {
    if((millis()-lastUpdate) > updateInterval)  //if update interval exceeded
    {
      lastUpdate = millis();            //update timestamp
      pos += stepIncrement;             //update position
      slap.write(pos);                  //move servo to position
      Serial.println(pos);              //print position
      if ((pos >= 180 ) || (pos <= 0))  //if position is outside range of motion...
      {
        stepIncrement = -stepIncrement; //reverse direction
      }
    }
  }
  
};

Slap slapper(8,5);                      //define slapper object to update 5 positions every 8ms

void setup()
{
  Serial.begin(9600);                   //serial connection for debugging
  slapper.Attach(9);                    //attach slapper to pin 9
}

void loop()
{
  int things = 0,                       //variables determined by algorithm
      happening = 0;
  if (things == happening) 
  { 
    slapper.Update();                   //call Update meber function to move servo
  }
}
