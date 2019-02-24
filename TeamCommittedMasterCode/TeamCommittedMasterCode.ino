
// motor pins
const int m1_1 = 8;
const int m1_2 = 7;
const int m2_1 = 11;
const int m2_2 = 12;
const int m1_pwm = 9;
const int m2_pwm = 10;
const int ledPin = 13;

// ce pins for distance sensors
const int cePin1 = 2;
const int cePin2 = 4;

bool fullSpeedAhead = true;

// include libraries
#include <Encoder.h>
#include <Wire.h>
#include <VL6180X.h>
#include <LSM6.h>

VL6180X sensor1;
VL6180X sensor2;
LSM6 accSens;


char report[80];

// create encoder knobLeft() w/ ports 2 and 4
// create encode knobRight() w/ ports 3 and 5
Encoder knobLeft(2, 4);
Encoder knobRight(3, 5);

void setup() {

  // set pins to outputs
  pinMode(m1_1, OUTPUT);
  pinMode(m1_2, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_1, OUTPUT);
  pinMode(m2_1, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
  pinMode(cePin1, OUTPUT);
  pinMode(cePin2, OUTPUT);

 
  // begin serial data transmission at 9600 bits/sec (this rate is called baud)
  Serial.begin(9600);
  
  Wire.begin();

  // turn both CE pins off
  digitalWrite(cePin2, LOW);
  digitalWrite(cePin1, LOW);
  delay(500);

  
  // turn CE pin 1 on
  digitalWrite(cePin1, HIGH);
  delay(50);

  // initialize sensor 1 and set specific address
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setAddress(0x30);
  sensor1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor1.setTimeout(500);
  sensor1.stopContinuous();
  delay(500);

  // turn CE pin 2 on
  digitalWrite(cePin2, HIGH);
  delay(50);

  // initialize sensor 2 and set different address from sensor 1
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setAddress(0x29);
  sensor2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor2.setTimeout(500);
  sensor2.stopContinuous();
  delay(500);


  // initialize accelerometer
  accSens.init();
  accSens.enableDefault();
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
