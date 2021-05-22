#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display

// connect motor controller pins to Arduino digital pins
//pinMode(motor_input2, OUTPUT);   //RIGHT MOTOR
//pinMode(motor_input3, OUTPUT);   //LEFT MOTOR
// motor one (RIGHT MOTOR)
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two (LEFT MOTOR)
int enB = 5;
int in3 = 7;
int in4 = 6;

String voice;

#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  lcd.init();      // initialize the lcd
  lcd.backlight(); //backlight turn on

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); //RIGHT MOTOR
  pinMode(in2, OUTPUT); //RIGHT MOTOR
  pinMode(in3, OUTPUT); //LEFT MOTOR
  pinMode(in4, OUTPUT); //LEFT MOTOR
}
void loop()
{
  while (Serial.available())
  {                         //Check if there is an available byte to read
    delay(10);              //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#')
    {
      break;
    }           //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
    // voice = Serial.readStringUntil('\n');  // receive voice simultaneously
  }

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  lcd.setCursor(5, 0);
  lcd.print(voice);

  /*if (voice != voice){
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print(voice);
      }*/

  if (voice.length() > 0) {
    if (voice == "go ahead") {
      forward_car();
    }
    else if (voice == "go back") {
      back_car();
    }
    else if (voice == "right") {
      right_car();
    }
    else if (voice == "left") {
      left_car();
    }
    else if (voice == "stop") {
      stop_car();
    }

    if (voice.length() > 0) {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print(voice);
    }
    voice = ""; //Reset the variable after initiating
    delay(2000);
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
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void left_car()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void stop_car()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
