#ifndef MOVEMENT_FILE
#define MOVEMENT_FILE

bool moving = false;

 void goOneSquare() {
 	moving = true;
 	go(-spd, 1);
 	go(spd, 2);
 	delay(50);
 	go(0, 1);
 	go(0, 2);
 	moving = false;
 }


void turnLeft90() {
	moving = true;
	turnLeft(50, 50);
	go(0, 1);
	go(0, 2);
	moving = false;
}

void turnRight90() {
	moving = true;
	turnRight(50, 50);
	go(0, 1);
	go(0, 2);
	moving = false;
}



#endif