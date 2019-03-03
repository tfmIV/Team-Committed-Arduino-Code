#ifndef MOTORS_FILE
#define MOTORS_FILE

// motor pins
const int m1_1 = 8;
const int m1_2 = 7;
const int m2_1 = 11;
const int m2_2 = 12;
const int m1_pwm = 9;
const int m2_pwm = 10;
const int ledPin = 13;

void setupMotors() {
	// set pins to outputs
	pinMode(m1_1, OUTPUT);
	pinMode(m1_2, OUTPUT);
	pinMode(m1_pwm, OUTPUT);
	pinMode(m2_1, OUTPUT);
	pinMode(m2_1, OUTPUT);
	pinMode(m2_pwm, OUTPUT);
}


#endif