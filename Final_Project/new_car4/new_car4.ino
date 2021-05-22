
// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "CarProject"
#define REMOTEXY_WIFI_PASSWORD "123456789"
#define REMOTEXY_SERVER_PORT 6377

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

//define right motor control pins
#define right_motor_A 9
#define right_motor_B 8
#define right_motor_speed 10 //enable pin

//define left motor control pins
#define left_motor_A 7
#define left_motor_B 6
#define left_motor_speed 5 //enable pin

//define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};

void setup() 
{
  RemoteXY_Init (); 
  
   //initialization pins
  pinMode (right_motor_A, OUTPUT);
  pinMode (right_motor_B, OUTPUT);
  pinMode (left_motor_A, OUTPUT);
  pinMode (left_motor_B, OUTPUT);

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
