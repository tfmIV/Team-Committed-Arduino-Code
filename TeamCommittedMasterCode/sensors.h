#ifndef SENSORS_FILE
#define SENSORS_FILE

// ce pins for distance sensors
const int cePin1 = 2;
const int cePin2 = 4;

// include libraries
#include <Encoder.h>
#include <Wire.h>
#include <VL6180X.h>
#include <LSM6.h>

// initialize sensors
VL6180X sensor1;
VL6180X sensor2;
LSM6 accSens;

char report[80];

// create encoder knobLeft() w/ ports 2 and 4
// create encode knobRight() w/ ports 3 and 5
Encoder knobLeft(2, 4);
Encoder knobRight(3, 5);

// set up dist + gyro + encoders
void setupSensors() {

	// set pins to output
	pinMode(cePin1, OUTPUT);
	pinMode(cePin2, OUTPUT);

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
	
int readLeftEnc() {
	
}

#endif

