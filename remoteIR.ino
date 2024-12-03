//Infrared control using a remote 

// IR remote library
#include <IRremote.hpp>
// Servo motor library                   //also had server.h for like 10 minutes i was so confused why it wasnt working...
#include <Servo.h>

#define AT 8 //Left Motor A turning
#define BT 7 //Right Motor B turning
#define BS 6 //Right Motor B Speed
#define AS 5 //Left Motor A Speed

#define IR 9  //IR LED infrared

#define SB 3 //Stand-by servo

#define On 1   //high
#define Off 0  //low

Servo myservo;  //Class designed to control servo motors. its being classified

#define UP 4          //numerick valu when Up is pressed
#define RIGHT 5       //numerick valu when Right is pressed
#define LEFT 6        //numerick valu when Left is pressed
#define DOWN  7      //numerick valu when Down is pressed
#define OK 8         //numerick valu when OK is pressed

void setup()
{
  pinMode(AT, OUTPUT);
  pinMode(BT, OUTPUT);
  pinMode(BS, OUTPUT);
  pinMode(AS, OUTPUT);
  digitalWrite(SB, HIGH);
  myservo.attach(10);
  Serial.begin(9600);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
if (IrReceiver.decode())
{
  Serial.println(IrReceiver.decodedIRData.command);
  if(IrReceiver.decodedIRData.command == OK)
  {
    Stop();
  }
  else if(IrReceiver.decodedIRData.command == UP)
  {
    Forward(75);
    myservo.write(90);
  }
  else if(IrReceiver.decodedIRData.command == RIGHT)
  {
    Right(50);
    myservo.write(0);
  }
  else if(IrReceiver.decodedIRData.command == LEFT)
  {
    Left(50);
    myservo.write(180);
  }
  else if(IrReceiver.decodedIRData.command == DOWN)
  {
    Backward(100);
    myservo.write(90);
  }
  IrReceiver.resume();
}
}



void Forward(int speed)
{
  digitalWrite(AS, On); // This turns on the speed off the left motor 
  analogWrite(AT, speed); // determines its speed 
  digitalWrite(BS, On); // This turns on the speed off the right motor 
  analogWrite(BT, speed); //determines its speed
}
void Left(int speed)
{
  digitalWrite(AS, Off); // This turns off the speed off the left motor 
  analogWrite(AT, speed); //determines its speed
  digitalWrite(BS, On);  // This turns on the speed off the right motor 
  analogWrite(BT, speed); //determines its speed
}
void Right(int speed)
{
  digitalWrite(AS, On); // This turns on the speed off the left motor 
  analogWrite(AT, speed); //determines its speed
  digitalWrite(BS, Off); // This turns off the speed off the right motor 
  analogWrite(BT, speed); //determines its speed
}
void Backward(int speed)
{
  digitalWrite(AS, Off); // This turns off the speed off the left motor 
  analogWrite(AT, speed); //determines its speed
  digitalWrite(BS, Off); // This turns off the speed off the right motor 
  analogWrite(BT, speed); //determines its speed
}
void Stop()
{
  digitalWrite(AS, On); // This turns on the speed off the left motor 
  analogWrite(AT, 0); //determines its speed
  digitalWrite(BS, On); // This turns on the speed off the right motor 
  analogWrite(BT, 0); //determines its speed
}