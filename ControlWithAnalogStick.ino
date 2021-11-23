#include <Servo.h>

Servo myservo;

const int ENABLE = 7;　//motor ENABLE Pin
const int CH1 = 5; //motor controll Pin 1
const int CH2 = 3; //motor controll Pin 2
#define StickX A0
#define StickY A1

void setup() {
  myservo.attach(9, 500, 2400);
  Serial.begin(9600);
  pinMode(StickX, INPUT);
  pinMode(StickY, INPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  digitalWrite(ENABLE, LOW);
  delay(500);
}

void loop() {
  int stick_x = analogRead(StickX);
  int stick_y = analogRead(StickY);
  int pos;
  int motor_speed;
  Serial.print(stick_x);
  pos = map( stick_x, 0, 1023, 40, 130);
  motor_speed = motor_speed > 512 ? map(stick_y-512, 0, 512,0,255) : map(stick_y,0,512,0,255);
  myservo.write(pos);
  if(stick_y > 570){//go straight
    digitalWrite(ENABLE,HIGH);
    digitalWrite(CH1,HIGH);
    digitalWrite(CH2,LOW); 
    analogWrite(CH1,motor_speed);
  }
  else if(stick_y < 430){//back
    digitalWrite(ENABLE,HIGH);
    digitalWrite(CH2,HIGH);
    digitalWrite(CH1,LOW);
    motor_speed = -motor_speed+255;
    analogWrite(CH2,motor_speed);
    }
  else{
    digitalWrite(CH1,LOW);
    digitalWrite(CH2,LOW); 
    digitalWrite(ENABLE,LOW);
    } 
}
