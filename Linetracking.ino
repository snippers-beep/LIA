// Servo motor library
#include <Servo.h>

#define AT 8 //Left Motor A turning
#define BT 7 //Right Motor B turning
#define BS 6 //Right Motor B Speed
#define AS 5 //Left Motor A Speed

#define IR 9  //IR LED infrared

#define SB 3 //Stand-by servo

#define On 1   //high
#define Off 0  //low

Servo myservo; // create servo control object

#define SM A1  //Mid sensor analog
#define SR A0  //Right sensor analog
#define SL A2  //Left sensor analog

#define Trigger 13  //triggger of ultrasonic pin 13
#define Echo 12     // echo pin ultrasonic sensor

unsigned long PTime = 0;  //previous time that will keep track

const long prinTime = 150;  //time between prints
 
 int search = 0;  //create and integer to give it a value of one for future use

float duration, distance; // creating 2 variables

void setup() 
{
  // put your setup code here, to run once:
  pinMode(AT, OUTPUT);  //setting all the outputs for the pins pin 8
  pinMode(BT, OUTPUT);  //pin 7
  pinMode(BS, OUTPUT);  //pin 6
  pinMode(AS, OUTPUT);  //pin 5
  pinMode(SM, INPUT);  //pin A1
  pinMode(SR, INPUT);  //pin A0
  pinMode(SL, INPUT);  //pin A2
  digitalWrite(SB, HIGH);  // turning the standby on activating the motor pin 3
myservo.attach(10); // server motor attached to pin 10
Serial.begin(9600); // begin serial monitor
pinMode(Trigger, OUTPUT);  // pin 13
pinMode(Echo, INPUT);  // set pin 12 as input 

}

void loop() {
  // put your main code here, to run repeatedly:
  int VR = analogRead(SR); //VR is the reading of the value of SR
  int VL = analogRead(SL); //VL is the reading of the value of SL
  int VM = analogRead(SM); //VM is the reading of the value of SM

  long Time = millis(); // making time into actual time

if(Time - PTime >= prinTime)  //printing the readings of the analog readings of the tracking sensor
{
  PTime = Time;
  Serial.print("L="); // for clarity that this is left
  Serial.print(VL);   //showing left sensor value
  Serial.print("M="); // for clarity that this is middle
  Serial.print(VM);   //showing middle sensor value
  Serial.print("R="); // for clarity that this is right
  Serial.print(VR);   //showing right sensor value
} 
SonicSens();
if(distance < 20) //shecking if its about to run into something
{
  Stop(); // stop the car so it doesnt crash
}
else  //if it isnt about to crash:
{
  if(VL >= 500 && VR >= 500 && VM >= 500) //to stop the car while picked up, thanks artin this was really annoying
  {
    Stop(); //stops as you dont want it moving in your hands
  }
  else if (VM >= 500)  //checks if theres a line in the middle
  {
    Forward(75); // 75% speed easier to read lines 
  }
  else if (VR >= 500 && VL >= 500) // checks if both the right and left has lines
  {
    Right(75); // I should make it so when both are detected it recenters to not be tricked butttt i ours the only side label is on the left soo
  }
  else if (VL >= 500) //checks if the left has lines
  {
    Left(75); // goes left 
  }
  else if (VR >= 500) // checks if  right has lines
  {
    Right(75); // goes right
  }
  else 
  {
   Search(); // searching function
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
void Search()
{
  switch (search) //to use different steps
  {
    case 0: //first case as defined earlier
    myservo.write(0); // look to the right
    Right(50); // goes slowly to the right
    if (millis() - PTime > 5000) //it does this for 5 seconds before doing to the next step
    {
      search = 1; // makes it go to the next step
      PTime = millis(); // reset PTime
    }
    break; //break out of case 0
    case 1: // case N.2
    myservo.write(180); // look left 
    Left(50); // turn left
    if (millis() - PTime > 5000) //check if its been 5 seconds then to the next step
    {
      search = 2; // starts the next step
      PTime = millis(); // reset time
    }
    break; // break out of the previous case
    case 2: // 3rd case
    Stop(); // stops the car
    myservo.write(90); // look straight
  }
}