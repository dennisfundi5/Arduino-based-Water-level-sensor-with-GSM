#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

Servo myservo;
SoftwareSerial sgsm(2, 3); //gsm tx(2) and rx(3)

int trigPin = 4;
int echoPin = 5;
int speedOfSound = 330;
float pingTime;
float targetDistance;

int led0 = 8;
int led1 = 9;
int led2 = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sgsm.begin(9600);

  myservo.attach(6);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  myservo.write(0);
  delay(1000);
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2000);
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin, LOW);

  pingTime = pulseIn (echoPin, HIGH);
  pingTime = pingTime / 1000000;

  targetDistance = speedOfSound * pingTime;
  targetDistance = targetDistance / 2;
  targetDistance = targetDistance * 100;   // converting the distance to centimeters

  int val = map(targetDistance, 0, 19.4, 100, 0);
  Serial.print ("The Distance to the target Is: ");
  Serial.print (val);
  Serial.println ("%");
  Serial.println ("    ");

  if (val <= 40) {

    sgsm.print("\r");
    delay(400);
    sgsm.print("AT+CMGF=1\r");
    delay(400);
    sgsm.print("AT+CMGS=\"+254758247840\"\r");
    delay(400);
    // The text message to be sent
    sgsm.println("Hi maestro,");
    sgsm.println("Info from Water Level Sensing Module");
    sgsm.println("STATUS: LOWER READING");
    delay(400);
    sgsm.write(0x1A);
    delay(300);
  }
  if (val >= 41 && val <= 79) {

    sgsm.print("\r");
    delay(400);
    sgsm.print("AT+CMGF=1\r");
    delay(400);
    sgsm.print("AT+CMGS=\"+254758247840\"\r");
    delay(400);
    // The text message to be sent
    sgsm.println("Hi maestro,");
    sgsm.println("Info from Water Level Sensing Module");
    sgsm.println("STATUS: INTERMEDIATE");
    delay(400);
    sgsm.write(0x1A);
    delay(300);
  }
  if (val >= 80 && val <= 100) {

    sgsm.print("\r");
    delay(400);
    sgsm.print("AT+CMGF=1\r");
    delay(400);
    sgsm.print("AT+CMGS=\"+254758247840\"\r");
    delay(400);
    // The text message to be sent
    sgsm.println("Maesto!!,");
    sgsm.println("Info from Water Level Sensing Module");
    sgsm.println("STATUS: CRITICAL LEVEL");
    delay(400);
    sgsm.write(0x1A);
    delay(300);
  }

  if (val <= 40 ) {
    digitalWrite(led0, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  if (val >= 41 && val <= 79) {
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }

  if (val >= 80 && val <= 90) {
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }

}
