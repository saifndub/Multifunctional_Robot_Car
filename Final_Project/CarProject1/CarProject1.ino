#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;

boolean goesForward=false;
int distance = 100;
int max_dist = 20;    //Set maximum distance of obstacle
int speedSet = 0;
int setspeed = 255;   //For DC Motor speed 
int balance = 100 ;   //For servo motor balance position


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// connect motor controller pins to Arduino digital pins
//pinMode(motor_input2, OUTPUT);   //RIGHT MOTOR
//pinMode(motor_input3, OUTPUT);   //LEFT MOTOR
// motor A (RIGHT MOTOR)
int enA = 10;
const int in1 = 9;
const int in2 = 8;
// motor B (LEFT MOTOR)
const int in3 = 7;
const int in4 = 6;
int enB = 5;

int led_left = 4;
int led_right = 3;
String voice;
String copy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  
  lcd.init();               // initialize the lcd 
  lcd.backlight();          //backlight turn on

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
  
  pinMode(led_left, OUTPUT);
  pinMode(led_right, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);   //RIGHT MOTOR
  pinMode(in2, OUTPUT);   //RIGHT MOTOR
  pinMode(in3, OUTPUT);   //LEFT MOTOR
  pinMode(in4, OUTPUT);   //LEFT MOTOR
  
}
void loop() 
{
  while (Serial.available()){   //Check if there is an available byte to read
     delay(10);                 //Delay added to make thing stable 
     char c = Serial.read();    //Conduct a serial read
    if (c == '#') 
        {break;}                //Exit the loop when the # is detected after the word
    voice += c;                 //Shorthand for voice = voice + c
    // voice = Serial.readStringUntil('\n');  // receive voice simultaneously
  }
  
   analogWrite(enA, setspeed);
   analogWrite(enB, setspeed); 

   lcd.setCursor(5,0);
   lcd.print(voice);

   
  if (voice.length() > 0){
    if((voice == "self") || (voice == "Self")) {
      
      /*if(Serial.available())
      {
        voice = Serial.readStringUntil('\n');
      }*/
        self_car(); 
    }
    else{
      if((voice == "go ahead") || (voice == "forward")){
      stop_car();
      led();
      forward_car();
      }
    else if((voice == "go back") || (voice == "come back")){
      back_car();
      led();
      }
    else if((voice == "right") || (voice == "Right")) {
      right_car();
      delay(500);
      stop_car();
    }
    else if((voice == "left") || (voice == "Left") || (voice == "lift")) {
      left_car();
      delay(500);
      stop_car();
    }
    else if((voice == "stop") || (voice == "Stop")) {
      stop_car();
    }
    else if((voice == "round left") || (voice == "Round Left") || (voice == "round lift")) {
      left_car();
    }
    else if((voice == "round right") || (voice == "Round Right")) {
      right_car();
    }
    else if((voice == "Munia") || (voice == "munia") || (voice == "light") || (voice == "Light") || (voice == "l e d")) {
      led();
    }
    else {
      lcd.setCursor(3,2);
      lcd.print("This Voice is");
      lcd.setCursor(4,3);
      lcd.print("not accepted");
    }

    if (voice.length() > 0){
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print(voice);
      }
  voice=""; //Reset the variable after initiating
  //delay(2000);
  
    }    
  }
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
  digitalWrite(led_right, HIGH);
  digitalWrite(led_left, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void left_car()
{
  digitalWrite(led_right, LOW);
  digitalWrite(led_left, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void stop_car()
{
  digitalWrite(led_right, LOW);
  digitalWrite(led_left, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void led()
{
  digitalWrite(led_right, HIGH);
  digitalWrite(led_left, HIGH);
}
void self_car() {

  analogWrite(enA, setspeed);
  analogWrite(enB, setspeed); 
  
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=max_dist)
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

  if(distanceR>=distanceL)
  {
    right_car();
    stop_car();
  }else
  {
    left_car();
    stop_car();
  }
 }else
 {
  forward_car();
 }
 distance = readPing();
}
int lookRight()
{
    myservo.write(30); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(balance); 
    return distance;
}

int lookLeft()
{
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
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
