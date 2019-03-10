#ifndef MAZE_FILE
#define MAZE_FILE

#include <StackArray.h>


class Node() {

public:
	bool visited;
	int wallN;
	int wallS;
	int wallE;
	int wallW;
	int xPos;
	int yPos;

	Node() {
		visited = false;
		wallN = false;
		wallS = false;
		wallE = false;
		wallW = false;
		xPos = 0;
		yPos = 0;

	}
}

int mazeSize = 15;
Node maze[mazeSize + 1][mazeSize + 1];

StackArray<Node>paths;

void scanForward() {
	while(!isWallFront()) {
		if ((currentX == 7 || current == 8) && (currentY == 7 || currentX == 8)) {
			goal = true;
			break;
		}
		if ((facing == 0) || (facing == 2)) {
			if (!isWallEast()) {
				maze[currentX - 1][currentY].xPos = currentX - 1;
				maze[currentX - 1][currentY].yPos = currentY;
				paths.push(maze[currentX - 1][currentY]);
			}
			if (!isWallWest()) {
				maze[currentX + 1][currentY].xPos = currentX + 1;
				maze[currentX + 1][currentY].yPos = currentY;
				paths.push(maze[currentX + 1][currentY]);
			}
			if (facing == 0) { 
				moveNorth();
			} else {
				moveSouth();
			}

		}
		if ((facing == 1) || (facing == 3)) {
			if (!isWallNorth()) {
				maze[currentX][currentY - 1].xPos = currentX ;
				maze[currentX][currentY - 1].yPos = currentY - 1;
				paths.push(maze[currentX][currentY - 1]);
			}
			if (!isWallSouth()) {
				maze[currentX][currentY + 1].xPos = currentX;
				maze[currentX][currentY + 1].yPos = currentY + 1;
				paths.push(maze[currentX][currentY + 1]);
			}
			if (facing == 1) { 
				moveEast();
			} else {
				moveWest();
			}
		}
	}
}

void getWalls() {
	maze[currentX][currentY].wallW = isWallWest();
	if (currentX != mazeSize) maze[currentX + 1][currentY].wallE = isWallWest();
	maze[currentX][currentY].wallE = isWallEast();
	if (currentX != 0) maze[currentX - 1][currentY].wallW = isWallEast();
	maze[currentX][currentY].wallN = isWallNorth();
	if (currentY != 0) maze[currentX][currentY - 1].wallS = isWallNorth();
	maze[currentX][currentY].wallS = isWallSouth();
	if (currentY != mazeSize) maze[currentX][currentY + 1].wallN = isWallSouth();
}

getWalls();
scanForward();
while (!paths.isEmpty()) {
	Node next = paths.pop();
	
}






int* getNeighbors(int x, int y) {
	int[] neighbors = {0, 0, 0, 0};
	Node input = maze[x][y];
	if (!input.wallN) neighbors[0] = 1;
	if (!input.wallE) neighbors[1] = 1;
	if (!input.wallS) neighbors[2] = 1;
	if (!input.wallW) neighbors[3] = 1;
	return neighbors;
}








#endif