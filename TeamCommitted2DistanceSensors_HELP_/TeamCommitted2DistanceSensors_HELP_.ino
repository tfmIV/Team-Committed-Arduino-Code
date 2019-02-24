#include <Encoder.h>


//MotorStuff
const int m1_1 = 8;
const int m1_2 = 7;
const int m2_1 = 11;
const int m2_2 = 12;
const int m1_pwm = 9;
const int m2_pwm = 10;
const int ledPin = 13;

const int cePin1 = 0;
const int cePin2 = 1;

bool fullSpeedAhead = true;

 long original1 = 0;
 long original2 = 0;

#include <Encoder.h>
#include <Wire.h>
#include <VL6180X.h>
VL6180X sensor1;
VL6180X sensor2;

Encoder knobLeft(2, 4);
Encoder knobRight(3, 5);

void setup() {

  // put your setup code here, to run once:
  pinMode(m1_1, OUTPUT);
  pinMode(m1_2, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_1, OUTPUT);
  pinMode(m2_1, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
  pinMode(cePin1, OUTPUT);
  pinMode(cePin2, OUTPUT);

 
  
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test");
  Wire.begin();


  digitalWrite(cePin2, LOW);
  digitalWrite(cePin1, LOW);
  delay(500);

  digitalWrite(cePin1, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setAddress(0x30);
  sensor1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor1.setTimeout(500);

  sensor1.stopContinuous();
  delay(500);


  digitalWrite(cePin2, HIGH);
  delay(50);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setAddress(0x29);
  sensor2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor2.setTimeout(500);

  sensor2.stopContinuous();
  delay(500);


}

void nameChange(int sensorAddress, int cePin, String sensor) {
  sensor2.setAddress(sensorAddress);
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

///Go
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

long sensor1Val, sensor2Val;
sensor1Val = sensor1.readRangeSingle();
sensor2Val = sensor2.readRangeSingle();

  Serial.print("Sensor 1: ");
  Serial.print(sensor1Val);
  Serial.print("Sensor 2: ");
  Serial.print(sensor2Val);
  delay(1000);

original1 = sensor1Val;
original2 = sensor2Val;

}
