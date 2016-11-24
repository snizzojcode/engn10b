#include <Stepper.h>

const int stepsPerRevolution = 48;

class Steer
{
  Stepper steer;
  int pin1,
      pin2,
      pin3,
      pin4,
      stepsPerRevolution,
      steeringSpeed;
  public:

  Steer (int rpm, int inpin1, int inpin2, int inpin3, int inpin4)
  {
    stepsPerRevolution = rpm;
    pin1 = inpin1;
    pin2 = inpin2;
    pin3 = inpin3;
    pin4 = inpin4;
    steer (stepsPerRevolution, pin1, pin2, pin3, pin4);
  }

  void setSpeed(int speed)
  {
    steer.setSpeed(speed);
  }
};

Steer steering (stepsPerRevolution, 8,9,10,11); //define stepper object on pins 9-11

void setup()
{
  steering.setSpeed(120);
}

void loop()
{
  
}

