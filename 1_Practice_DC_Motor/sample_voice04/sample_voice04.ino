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
int in3 = 7;
int in4 = 6;
int enB = 5;

int led_left = 4;
int led_right = 3;
String voice;

#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  lcd.init();      // initialize the lcd
  lcd.backlight(); //backlight turn on

  pinMode(led_left, OUTPUT);
  pinMode(led_right, OUTPUT);
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

  if (voice.length() > 0) {
    if ((voice == "go ahead") || (voice == "forward")) {
      stop_car();
      forward_car();
    }
    else if ((voice == "go back") || (voice == "come back")) {
      back_car();
      led();
    }
    else if ((voice == "right") || (voice == "Right")) {
      right_car();
      delay(500);
      stop_car();
    }
    else if ((voice == "left") || (voice == "Left") || (voice == "lift")) {
      left_car();
      delay(500);
      stop_car();
    }
    else if ((voice == "stop") || (voice == "Stop")) {
      stop_car();
    }
    else if ((voice == "round left") || (voice == "Round Left") || (voice == "round lift")) {
      left_car();
    }
    else if ((voice == "round right") || (voice == "Round Right")) {
      right_car();
    }
    else if ((voice == "Munia") || (voice == "munia") || (voice == "light") || (voice == "Light") || (voice == "l e d")) {
      led();
    }
    else {
      lcd.setCursor(3, 2);
      lcd.print("This Voice is");
      lcd.setCursor(4, 3);
      lcd.print("not accepted");
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
