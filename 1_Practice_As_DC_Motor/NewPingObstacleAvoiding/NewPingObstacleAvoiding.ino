// Arduino Obstacle Avoiding Robot Car using NewPing library
// Code adapted from http://www.educ8s.tv
// First Include the NewPing and Servo Libraries

#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int max_dist = 20; //Set maximum distance of obstacle
int speedSet = 0;
int setspeed = 255; //For DC Motor speed
int balance = 100;  //For servo motor balance position

//Motor A
int enA = 10;
const int in1 = 9;
const int in2 = 8;
//Motor B
const int in3 = 7;
const int in4 = 6;
int enB = 5;

void setup(){

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  myservo.attach(2);
  myservo.write(balance);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){ //***************************** START MAIN LOOP *****************************

  analogWrite(enA, setspeed);
  analogWrite(enB, setspeed);

  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= max_dist)
  {
    stop_car();
    delay(100);
    back_car();
    delay(300);
    stop_car();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      right_car();
      stop_car();
    }
    else
    {
      left_car();
      stop_car();
    }
  }else
  {
    forward_car();
  }
  distance = readPing();
} //************************************** END MAIN LOOP **************************************

int lookRight()
{
  myservo.write(30);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(balance);
  return distance;
}
int lookLeft() {
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(balance);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
void forward_car()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void back_car()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right_car()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(300);
  forward_car();
}
void left_car()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);
  forward_car();
}
void stop_car()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
