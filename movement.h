#ifndef MOVEMENT_FILE
#define MOVEMENT_FILE

 void goOneSquare() {
 	go(-spd, 1);
 	go(spd, 2);
 	delay(50);
 }


void turnLeft90() {
	turnLeft(50, 50);
}

void turnRight90() {
	turnRight(50, 50);
}



#endif