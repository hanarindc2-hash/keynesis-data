#include <Arduino.h>

const int motorPin1= 5;
const int motorPin2= 6;
const int enablePin= 9;

void setup()
{
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(enablePin, OUTPUT);
}

void loop()
{
//1. 전진
analogWrite(enablePin, 200);
digitalWrite(motorPin1, HIGH);
digitalWrite(motorPin2, LOW);
delay(3000);
//2. 정지
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
delay(5000);
}
