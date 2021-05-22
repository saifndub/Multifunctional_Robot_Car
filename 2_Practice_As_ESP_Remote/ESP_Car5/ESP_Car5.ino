// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "CarProject1"
#define REMOTEXY_WIFI_PASSWORD "123456789"
#define REMOTEXY_SERVER_PORT 6377

#include <NewPing.h>//=====================================================
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
int balance = 100 ;   //For servo motor balance position//=====================================================

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,4,0,0,0,30,0,8,13,0,
  5,16,59,15,37,37,2,26,31,3,
  131,1,8,41,15,2,26,1,9,10,
  38,17,16,2,31,88,0 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position 
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_1; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

/*define right motor control pins
#define right_motor_A 9
#define right_motor_B 8
#define right_motor_speed 10 //enable pin

//define left motor control pins
#define left_motor_A 7
#define left_motor_B 6
#define left_motor_speed 5 //enable pin*/

int enA = 10;
const int in1 = 9;
const int in2 = 8;
// motor B (LEFT MOTOR)
const int in3 = 7;
const int in4 = 6;
int enB = 5;

int led_left = 4;
int led_right = 3;

/*define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};*/

//define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {in1, in2, enA};
uint8_t LeftMotor[3] = {in3, in4, enB};

void setup() 
{
  RemoteXY_Init (); 
  
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
  
   //initialization pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);   //RIGHT MOTOR
  pinMode(in2, OUTPUT);   //RIGHT MOTOR
  pinMode(in3, OUTPUT);   //LEFT MOTOR
  pinMode(in4, OUTPUT);   //LEFT MOTOR;

  //Serial.begin(9600);
}

void loop() 
{ 
 RemoteXY_Handler ();
  
  //digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);

   if((RemoteXY.select_1==0) || (RemoteXY.select_1==1) || (RemoteXY.button_1==1))
  {
    Wheel (RightMotor, 0);
    Wheel (LeftMotor, 0);
  }
  
  else if(RemoteXY.select_1==2)
  {
    //manage the right motor
    Wheel (RightMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
    Wheel (LeftMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
  }
  else if (RemoteXY.select_1==1) {

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
}

//speed control of motors
void Wheel (uint8_t * motor, int v) // v = motor speed, motor = pointer to an array of pins 
{
  if (v > 100) v=100;
  if (v < -100) v=-100;
  if (v > 0){

    digitalWrite (motor [0], HIGH);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], v * 2.55);
    //Serial.println(v * 2.55);
  }
  else if ( v<0 ){

    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], HIGH);
    analogWrite (motor [2], (-v) * 2.55);
    //Serial.println(v * 2.55);
  }
  else{
    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], 0);
  }
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
