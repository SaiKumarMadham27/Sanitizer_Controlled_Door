#include <Servo.h>
#include <LiquidCrystal.h>
int Contrast=75;
LiquidCrystal lcd(12, 11, 9, 4, 3, 2);
int angle = 0;
#define trig 7
#define echo 8
Servo servo;
const int sensor = 10;
const int Relay = 13;
int state;
int value;
long duration;
int distance;
void setup()
{
Serial.begin(9600);
analogWrite(6,Contrast);
lcd.begin(16,2);
lcd.print("before you enter please sanitize");
servo.attach(5);
servo.write(0)
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(sensor, INPUT);
pinMode(Relay, OUTPUT);
}
void loop()
{
digitalWrite(trig, LOW);
delayMicroseconds(5);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
value = digitalRead(sensor);
duration = pulseIn(echo, HIGH);
distance= duration*0.034/2;
delay(1000);
if (distance > 1 && distance < 15)
{
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("Hands detected");
lcd.setCursor(0, 1);
lcd.print("wash hands - 20s");
digitalWrite(Relay, HIGH);
state = 1;
delay(2000);
lcd.clear();
lcd.print("You are safe now");
}
else
{
digitalWrite(Relay, LOW);
}
if ((state == 1) && (value == LOW))
{
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("you may go in");
state = 1;
delay(1000);
lcd.clear();
lcd.print("you are safe now");
}
else
{
digitalWrite(Relay, LOW);
}
if ((state == 1) && (value == LOW))
{
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("you may go in");
lcd.setCursor(1, 1);
lcd.print("10 seconds left");
servo.write(180);
delay(10000);
servo.write(0);
lcd.clear();
lcd.print("wash your hands");
lcd.setCursor(0, 1);
lcd.print("before you enter");
state = 0;
}
else if ((state == 0) && (value == 0))
{
lcd.clear();
lcd.print("wash your hands");
lcd.setCursor(0, 1);
lcd.print("to grant access");
}
}
