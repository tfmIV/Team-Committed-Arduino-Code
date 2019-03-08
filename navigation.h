#ifndef NAVIGATION_FILE
#define NAVIGATION_FILE

int north = 0;
int south = 2;
int east = 1;
int west = 3;
int facing = 0;

bool wallBehind = true;

bool isWallNorth() {
	if (facing == 0) {
		return isWallFront();
	} else if (facing == 1) {
		return isWallLeft();
	} else if (facing == 2) {
		return wallBehind;
	} else {
		return isWallRight();
	}
}

bool isWallSouth() {
	if (facing == 0) {
		return wallBehind;
	} else if (facing == 1) {
		return isWallRight();
	} else if (facing == 2) {
		return isWallFront();
	} else {
		return isWallLeft();
	}
}

bool isWallEast() {
	if (facing == 0) {
		return isWallRight();
	} else if (facing == 1) {
		return isWallFront();
	} else if (facing == 2) {
		return isWallLeft();
	} else {
		return wallBehind;
	}
}

bool isWallWest() {
	if (facing == 0) {
		return isWallLeft();
	} else if (facing == 1) {
		return wallBehind;
	} else if (facing == 2) {
		return isWallRight();
	} else {
		return isWallFront();
	}
}

void moveNorth() {
	if (facing == 0) {
		goOneSquare();
	} else if (facing == 1) {
		turnLeft90();
		goOneSquare();
	} else if (facing == 2) {
		turnLeft90();
		turnLeft90();
		goOneSquare();
	} else {
		turnRight90();
		goOneSquare();
	}
}

void moveSouth() {
	if (facing == 0) {
		turnLeft90();
		turnLeft90();
		goOneSquare();
	} else if (facing == 1) {
		turnRight90();
		goOneSquare();
	} else if (facing == 2) {
		goOneSquare();
	} else {
		turnLeft90();
		goOneSquare();
	}
}

void moveEast() {
	if (facing == 0) {
		turnRight90();
		goOneSquare();
	} else if (facing == 1) {
		goOneSquare();
	} else if (facing == 2) {
		turnLeft90();
		goOneSquare();
	} else {
		turnLeft90();
		turnLeft90();
		goOneSquare();
	}
}

void moveWest() {
	if (facing == 0) {
		turnLeft90();
		goOneSquare();
	} else if (facing == 1) {
		turnLeft90();
		turnLeft90();
		goOneSquare();
	} else if (facing == 2) {
		turnRight90();
		goOneSquare();
	} else {
		goOneSquare();
	}
}

#endif