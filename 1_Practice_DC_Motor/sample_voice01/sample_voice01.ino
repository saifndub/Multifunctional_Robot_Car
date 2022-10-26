int motor_input1 = 9;
int motor_input2 = 8;
int motor_input3 = 7;
int motor_input4 = 6;
int enA = 10;
int enB = 5;
String voice;
void setup()
{
  Serial.begin(38400);
  pinMode(motor_input1, OUTPUT); //RIGHT MOTOR
  pinMode(motor_input2, OUTPUT); //RIGHT MOTOR
  pinMode(motor_input3, OUTPUT); //LEFT MOTOR
  pinMode(motor_input4, OUTPUT); //LEFT MOTOR
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}
void loop()
{
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  while (Serial.available() > 0)
  {
    delay(10);
    char c = Serial.read();
    if (c == '#')
    {
      break;
    }
    voice += c;
  }
  if (voice == "forward") {
    digitalWrite(motor_input1, LOW);
    digitalWrite(motor_input2, HIGH);
    digitalWrite(motor_input3, LOW);
    digitalWrite(motor_input4, HIGH);
    delay(5000);
  }
  else if (voice == "back") {
    digitalWrite(motor_input1, HIGH);
    digitalWrite(motor_input2, LOW);
    digitalWrite(motor_input3, HIGH);
    digitalWrite(motor_input4, LOW);
    Serial.println(voice);
    delay(5000);
  }
  else if (voice == "left") {
    digitalWrite(motor_input1, LOW);
    digitalWrite(motor_input2, HIGH);
    digitalWrite(motor_input3, HIGH);
    digitalWrite(motor_input4, LOW);
    Serial.println(voice);
    delay(800);
  }
  else if (voice == "right") {
    digitalWrite(motor_input1, HIGH);
    digitalWrite(motor_input2, LOW);
    digitalWrite(motor_input3, LOW);
    digitalWrite(motor_input4, HIGH);
    Serial.println(voice);
    delay(800);
  }
  if (voice.length() > 0)
  {
    Serial.println(voice);
    voice = "";
    digitalWrite(motor_input1, LOW);
    digitalWrite(motor_input2, LOW);
    digitalWrite(motor_input3, LOW);
    digitalWrite(motor_input4, LOW);
  }
}
