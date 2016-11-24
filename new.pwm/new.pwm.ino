class Motor                               //class definition
{
  int motorPin;                           //define variable
  
  public:

  Motor (int pin)                         //constructor with input parameter pin
  {
    motorPin = pin;
  }

  void Mode ()                            //Mode member function - assigns pin to Motor object
  {
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

Motor forward (3);                        //define forward object on pin 3
 
void setup() 
{ 
  
  Serial.begin(9600);                     //serial connection for debugging
  forward.Mode();                         //set motor pin to output mode
} 
 
 
void loop() 
{ 
  int motorSpeed = 0,                     //motor speed determined by algorithm
      things = 0,
      happening = 0;
  if (things == happening)
  {
    forward.Update(motorSpeed);             //call Update member function to move motor
  }
} 
