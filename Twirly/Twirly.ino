
//MotorStuff
const int m1_1 = 8;
const int m1_2 = 7;
const int m2_1 = 11;
const int m2_2 = 12;
const int m1_pwm = 9;
const int m2_pwm = 10;
const int ledPin = 13;
bool fullSpeedAhead = true;

#include <Encoder.h>
#include <Wire.h>
#include <VL6180X.h>
VL6180X sensor;
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
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test");
  Wire.begin();

  //Distance Sensor Stuff
  sensor.init();
  sensor.configureDefault();
  // Reduce range max convergence time and ALS integration
  // time to 30 ms and 50 ms, respectively, to allow 10 Hz
  // operation (as suggested by Table 6 ("Interleaved mode
  // limits (10 Hz operation)") in the datasheet).
  sensor.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor.setTimeout(500);
   // stop continuous mode if already active
  sensor.stopContinuous();
  // in case stopContinuous() triggered a single-shot
  // measurement, wait for it to complete
  delay(300);
  // start interleaved continuous mode with period of 100 ms
  sensor.startInterleavedContinuous(100);
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
const int startingLeft = knobLeft.read();
const int startingRight = knobRight.read();

void onward(int sped, int newLeft, int newRight) {

   if ((newLeft<newRight) && (fullSpeedAhead == true)) {
    while (newLeft<newRight) {
      go(0,2);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
    
  } else if ((newLeft>newRight) && (fullSpeedAhead == false)) {
    while (newLeft>newRight) {
      go(0,1);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  } else if ((newLeft<newRight) && (fullSpeedAhead == true)) {
    while (newLeft<newRight) {
      go(0,2);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  } else if ((newLeft>newRight) && (fullSpeedAhead == false)){
    while (newLeft>newRight) {
      go(0,1);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  }
  
    go(sped,1);
    go(sped,2);
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

void backwardAhead(int sped, int newLeft, int newRight) {

while(newLeft<startingLeft && newRight<startingRight) {
   if ((newLeft<newRight) && (fullSpeedAhead == true)) {
    while (newLeft<newRight) {
      go(0,2);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
    
  } else if ((newLeft>newRight) && (fullSpeedAhead == false)) {
    while (newLeft>newRight) {
      go(0,1);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  } else if ((newLeft<newRight) && (fullSpeedAhead == true)) {
    while (newLeft<newRight) {
      go(0,2);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  } else if ((newLeft>newRight) && (fullSpeedAhead == false)){
    while (newLeft>newRight) {
      go(0,1);
      newLeft = knobLeft.read();
      newRight = knobRight.read();
    }
  }
  
    go(sped,1);
    go(sped,2);
}
go(0,1);
go(0,2);
}

long positionLeft = -999;
long positionRight = -999;

void loop() {

//Encoder Stuff
long newLeft, newRight;
 newLeft = -knobLeft.read();
 newRight = knobRight.read();


 if (newLeft != positionLeft || newRight != positionRight) {
   Serial.print("Left = ");
   Serial.print(newLeft);
   Serial.print(", Right = ");
   Serial.print(newRight);
   Serial.println();
   positionLeft = newLeft;
   positionRight = newRight;
}


go(100,1);
go(-100,2);
delay(10000);
go(0,1);
go(0,2);
delay(20000);
  

  
}










  //for (int i = 100; i >= 0; i--){
    //go(i, 1);
    //go(-i, 2);
    //delay(10);
  //}
  //go(0, 1);
  //go(0, 2);
  //digitalWrite(ledPin, LOW);
  //delay(1000);

// if (newLeft != positionLeft || newRight != positionRight) {
//   Serial.print("Left = ");
//   Serial.print(newLeft);
//   Serial.print(", Right = ");
//   Serial.print(newRight);
//   Serial.println();
//   positionLeft = newLeft;
//   positionRight = newRight;
// }

 // if a character is sent from the serial monitor,
// // reset both back to zero.
// if (Serial.available()) {
//   Serial.read();
//   Serial.println("Reset both knobs to zero");
//   knobLeft.write(0);
//   knobRight.write(0);
// }


/*void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for (i = 100; i >= -100; i--){
    go(i, 1);
    go(i, 2);
    delay(10);
  }
  go(0,1);
  go(0,2);
  digitalWrite(ledPin, LOW);
  delay(1000);
  go(255);
  delay(5000);
  digitalWrite(ledPin, LOW);
  go(0);
  delay(5000);
  }*/
