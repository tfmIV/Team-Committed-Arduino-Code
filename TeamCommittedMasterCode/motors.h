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

void turnLeft(int time, int spd) {
	go(spd, 2);
	go(spd, 1);
	delay(time);
}

void turnRight(int time, int spd) {
	go(-spd, 1);
	go(-spd, 2);
	delay(time);
}


#endif