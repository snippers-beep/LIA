// Servo motor library
#include <Servo.h>

#define AT 5 //Left Motor A turning           //i mixed both of them up but i would have to redo half the project
#define BT 6 //Right Motor B turning
#define BS 7 //Right Motor B Speed
#define AS 8 //Left Motor A Speed

#define IR 9  //IR LED infrared

#define SB 3 //Stand-by servo

#define On 1   //high
#define Off 0  //low

#define SM A1 //analog input 1 as the middle line tracking sensor
#define SR A0 //analog input 0 as the middle line tracking sensor
#define SL A2 //analog input 2 as the middle line tracking sensor 

#define Trigger 13 // trgger for ultrasonic sensor
#define Echo 12 // echo pin for untrasonic

Servo myservo;

float duration, distance;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  //activate serial monitor

pinMode(AT, OUTPUT);  //We declare all the Motor pins as OUTPUT pin 5
pinMode(BT, OUTPUT);  //pin 6
pinMode(AS, OUTPUT);  //pin 7
pinMode(BS, OUTPUT);  //pin 8
pinMode(SB, OUTPUT);   //pin 3
pinMode(Trigger, OUTPUT); // pin 13
pinMode(Echo, INPUT);  //pin 12

myservo.attach(10);  //servo motor connected to pin 10 arduino

digitalWrite(SB, HIGH); //We are turning on Standby to activate the motors

}

void loop() {
  // put your main code here, to run repeatedly:
int RV = analogRead(SR); // RV will be what the right sensor is receiving  right value pin 0
int LV = analogRead(SL); // left sensor pin 2
int MV = analogRead(SM); // middle sensor pin 1

if(MV >= 500 && RV >= 500 && LV >= 500)
{
Stop(); //stop car
}
 else
  {
    myservo.write(90); //turn servo to 95 degree
    SonicSens();
    if (distance < 20)
    {
      Stop();
      myservo.write(0);
      delay(2500);
      SonicSens();
      if(distance < 20)
      {
        Stop();
        myservo.write(180);
        delay(2500);
        SonicSens();
        if(distance < 20)
        {
          Stop();
          Backward(100); // max backwards
          delay(1000); // for 1 second
          myservo.write(0); // servo to angle 0
          Right(50); // right 50%
          delay(2000); // for 2sec
        }
        else //if no obstacle on left
        {
          Left(50); // left 50%
          delay(1000); // for 1 sec
          myservo.write(90); // 90 degrees
          delay(500); //wait a bit
        }
      }
      else // if no obstacle on right
      {
        Right(50); // 50 speed
        delay(1000); // right for 1 sec
        myservo.write(90); // turn 90 degrees
        delay(500); //wait a bit
      }
    }
    else // If no obstacle at all
    {
      Forward(100); // going forward till theres smt
      myservo.write(95); //95 degrees
    }
  }
}

//funstions using these to not have to do it manually before 
void SonicSens()
{
  digitalWrite(Trigger, LOW); // turn sensor off
  delayMicroseconds(5);       // for 5millisecods
  digitalWrite(Trigger, HIGH);//turn sensor on 
  delayMicroseconds(10);      //for 15 milliseconds
  digitalWrite(Trigger,LOW);  //turn it back off
  
  duration = pulseIn(Echo, HIGH); //The time it took for a pulse to comme back to calculate distance
  distance = (duration/2) * 0.0343;  //calculate the distance (i have no clue how the formula works)
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
