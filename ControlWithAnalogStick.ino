#include <Servo.h>

Servo myservo; 

#define ENABLE 7 //motor enable Pin
#define CH1 5 //motor controll Pin 1
#define CH2 3 //motor controll Pin 2
#define StickX A0 
#define StickY A1

void setup() {
  myservo.attach(9, 500, 2400);
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
  int angle;
  int motor_speed;
  angle = map( stick_x, 0, 1023, 40, 130);
  motor_speed = motor_speed > 512 /*Go Straight?*/ ? map(stick_y-512, 0, 512,0,255) : /*Back*/ map(stick_y,0,512,0,255);
  //analogRead : 0 ~ 1023 / motor speed level : 0 ~ 255
  
  myservo.write(angle);
  
  if(stick_y > 570){//Go straight
    digitalWrite(ENABLE,HIGH);
    digitalWrite(CH1,HIGH);
    digitalWrite(CH2,LOW); 
    analogWrite(CH1,motor_speed);
  }
  else if(stick_y < 430){//Back
    digitalWrite(ENABLE,HIGH);
    digitalWrite(CH2,HIGH);
    digitalWrite(CH1,LOW);
    motor_speed = -motor_speed+255;
    analogWrite(CH2,motor_speed);
    }
  else{ //No Control
    digitalWrite(CH1,LOW);
    digitalWrite(CH2,LOW); 
    digitalWrite(ENABLE,LOW);
    } 
}
