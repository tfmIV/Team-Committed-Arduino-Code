


// include libraries
#include "sensors.h"
#include "motors.h"
#include "navigation.h"
#include "movement.h"


void setup() {

  // begin serial data transmission at 9600 bits/sec (this rate is called baud)
  Serial.begin(9600);
  
  setupSensors();
  setupMotors();
 
}


//Go forward motor 1
void forward1(int spd) {
  digitalWrite(m1_1, LOW);
  digitalWrite(m1_2, HIGH);
  analogWrite(m1_pwm, spd);
}

//Go forward motor 2
void forward2(int spd) {
  digitalWrite(m2_1, LOW);
  digitalWrite(m2_2, HIGH);
  analogWrite(m2_pwm, spd);
}

//Go backward motor 1
void backward1(int spd) {
  digitalWrite(m1_1, HIGH);
  digitalWrite(m1_2, LOW);
  analogWrite(m1_pwm, spd);
}

//Go backward motor 2
void backward2(int spd){
  digitalWrite(m2_1, HIGH);
  digitalWrite(m2_2, LOW);
  analogWrite(m2_pwm, spd);
}

 //Go 
void go(int spd, int mot){
  
  if (mot == 1) {
   if (spd > 0){
    forward1(spd);
  }
   else if (spd < 0){
    backward1(-spd);
  }
   else {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_2, LOW);
    analogWrite(m1_pwm, 0);
  }
  }
  
  if (mot == 2) {
   if (spd > 0){
    forward2(spd);
  }
   else if (spd < 0){
    backward2(-spd);
  }
   else {
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_2, LOW);
    analogWrite(m2_pwm, 0);
  }
  }
}

//initialize encoder readings
int startingLeft = knobLeft.read();
int startingRight = knobRight.read();
long positionLeft = -999;
long positionRight = -999;


void onward(int sped){
  go(sped,1);
  go(sped,2);
}

void alignment(int sped, int newLeft, int newRight) {
    while (newLeft<newRight && sensor1.readRangeContinuousMillimeters()>70) {
        go(sped - 10,2);
        go(sped + 10,1);
      newLeft = knobLeft.read();
      newRight = -knobRight.read();
   Serial.print("Left = ");
   Serial.print(newLeft);
   Serial.print(", Right = ");
   Serial.print(newRight);
   Serial.println();
    }
    while (newLeft>newRight && sensor1.readRangeContinuousMillimeters()>70) {
        go(sped - 10,1);
        go(sped + 10,2);
      newLeft = knobLeft.read();
      newRight = -knobRight.read();
   Serial.print("Left = ");
   Serial.print(newLeft);
   Serial.print(", Right = ");
   Serial.print(newRight);
   Serial.println();
    }
}


void loop() {

  //Encoder Stuff
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = -knobRight.read();

  // distance sensor stuff
  long sensor1Val, sensor2Val;
  sensor1Val = sensor1.readRangeSingle();
  sensor2Val = sensor2.readRangeSingle();

//  // read gyro value
//  accSens.readGyro();
//  delay(50);
//
//  // print gyro values
//  Serial.println(accSens.g.x);
//  Serial.println(accSens.g.y);
//  Serial.println(accSens.g.z);

  // print accelerometer/gyro data
  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
  accSens.a.x, accSens.a.y, accSens.a.z,
  accSens.g.x, accSens.g.y, accSens.g.z);
  Serial.println(report);

  Serial.print("Sensor 1: ");
  Serial.print(sensor1Val);
  Serial.print("Sensor 2: ");
  Serial.print(sensor2Val);
  Serial.println();
  delay(100);

}
