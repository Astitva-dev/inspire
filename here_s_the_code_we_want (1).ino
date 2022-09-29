//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 170// sets speed of DC  motors
#define MAX_SPEED7 190
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo1;   
Servo myservo;

boolean goesForward=false;
int distance = 100;
int speedSet = 0;
int vb = 0;
int p =0;

void setup() {

  myservo1.attach(10);  
  myservo1.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
   delay(100);
  distance = readPing();
   delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(700);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(300);
  distanceL = lookLeft();
  delay(300);       
  sprinkle();

  if(distanceR>=distanceL)
  {
  
    turnLeft();
    turnLeft();
    sprinkle();
    moveStop();
    sprinkle();
   
    
   
  }else
  {
    turnRight();
    turnRight();
    sprinkle();
    moveStop();
    sprinkle();
    
  }
 }else
 {
  moveForward();
  
 }
 distance = readPing();
}

int lookRight()
{
    myservo1.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo1.write(115);
    return distance;
}

int lookLeft()
{
    myservo1.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo1.write(115); 
    return distance;
 
}

int readPing() { 
  delay(7);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);
         
   for ( speedSet = 0;  speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
     
     
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
     delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for ( speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
 
     delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  
     
  delay(900);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
 
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(900);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
   
void sprinkle(){
  myservo.attach(9);
for(p=0;p<180;p++)
{
myservo.write(p);
delay(10);
}
for(p=180;p>=1;p--)
{
myservo.write(p);
delay(10);
 }
}
