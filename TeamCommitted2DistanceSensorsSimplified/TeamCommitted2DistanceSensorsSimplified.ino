
// distance sensor CE pins
const int cePin1 = 4;
const int cePin2 = 2;

// include sensor library
#include <VL6180X.h>
#include <Wire.h>

// create sensors 1 and 2
VL6180X sensor1;
VL6180X sensor2;

void setup() {

  // begin serial data transmission at 9600 bits/sec (this rate is called baud)
  Serial.begin(9600);
  
  // begin wire??
  Wire.begin();

  // initialize and turn CE pins of both sensors off
  pinMode(cePin1, OUTPUT);
  pinMode(cePin2, OUTPUT);  
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

  // stop sensor 1 for now
  sensor1.stopContinuous();
  delay(500);

  // turn CE pin 2 on
  digitalWrite(cePin2, HIGH);
  delay(50);

  // initialize sensor 2 and set different address from sensor 1
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setAddress(0x31);
  sensor2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor2.setTimeout(500);

  // stop sensor 2 for now
  sensor2.stopContinuous();
  delay(500);

}

void loop() {

  // initialize sensor1Val and sensor2Val (used to store sensor readings)
  long sensor1Val, sensor2Val;
 
  // store sensor values
  sensor1Val = sensor1.readRangeSingle();
  delay(50);
  sensor2Val = sensor2.readRangeSingle();
  delay(50);

  // print sensor values
  Serial.print("Sensor 1: ");
  Serial.print(sensor1Val);
  Serial.print("Sensor 2: ");
  Serial.print(sensor2Val);
  Serial.println();
  delay(100);

}
