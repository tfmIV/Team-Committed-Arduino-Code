#ifndef SENSORS_FILE
#define SENSORS_FILE

// ce pins for distance sensors
const int cePin1 = 2;
const int cePin2 = 4;
const int cePin3 = 6;

// include libraries
#include <Encoder.h>
#include <Wire.h>
#include <VL6180X.h>
#include <LSM6.h>

// initialize sensors
VL6180X leftDist;
VL6180X rightDist;
VL6180X frontDist;

LSM6 accSens;

char report[80];

// create encoder knobLeft() w/ ports 2 and 4
// create encode knobRight() w/ ports 3 and 5
Encoder knobLeft(2, 4);  // MUST CHANGE THESE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Encoder knobRight(3, 5);

//initialize encoder readings
int startingLeft = knobLeft.read();
int startingRight = knobRight.read();
long positionLeft = -999;
long positionRight = -999;

// set up dist + gyro + encoders
void setupSensors() {

	// set pins to output
	pinMode(cePin1, OUTPUT);
	pinMode(cePin2, OUTPUT);
	pinMode(cePin3, OUTPUT);

	Wire.begin();

	// turn CE pins off
	digitalWrite(cePin3, LOW);
	digitalWrite(cePin2, LOW);
	digitalWrite(cePin1, LOW);
	delay(500);

	// turn CE pin 1 on
	digitalWrite(cePin1, HIGH);
	delay(50);

	// initialize sensor 1 and set specific address
	leftDist.init();
	leftDist.configureDefault();
	leftDist.setAddress(0x30);
	leftDist.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
	leftDist.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
	leftDist.setTimeout(500);
	leftDist.stopContinuous();
	delay(500);

	// turn CE pin 2 on
	digitalWrite(cePin2, HIGH);
	delay(50);

	// initialize sensor 2 and set different address from sensor 1
	rightDist.init();
	rightDist.configureDefault();
	rightDist.setAddress(0x29);
	rightDist.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
	rightDist.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
	rightDist.setTimeout(500);
	rightDist.stopContinuous();
	delay(500);

	// turn CE pin 3 on
	digitalWrite(cePin3, HIGH);
	delay(50);

	// initialize sensor 2 and set different address from sensor 1
	frontDist.init();
	frontDist.configureDefault();
	frontDist.setAddress(0x29);
	frontDist.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
	frontDist.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
	frontDist.setTimeout(500);
	frontDist.stopContinuous();
	delay(500);


	// initialize accelerometer
	accSens.init();
	accSens.enableDefault();
}
	
int readLeftEnc() {
	return knobLeft.read();
}

int readRightEnc() {
	return -knobRight.read();
}

int readDistLeft() {
	return leftDist.readRangeSingle();
}

int readDistRight() {
	return rightDist.readRangeSingle();
}

int readDistFront() {
	return frontDist.readRangeSingle();
}

bool isWallLeft() {
	return (readDistLeft() < 10);
}

bool isWallRight() {
	return (readDistRight() < 10);
}

bool isWallFront() {
	return (readDistFront() < 10);
}


#endif

