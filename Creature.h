#pragma once
#include <cstdlib>
#include "GridDisplay.h"


//Creature prototype here because island depends on it
class Creature;

class Island{
	private:
		int rows; //island row size
		int cols; //island colum size
		Creature* **location; //keep track of creature* locations
		GridDisplay *gd; //map it to a grid
	
	public:
		Island(GridDisplay *grid);
		int getRows();
		int getCols();
		bool isValid(int r, int c);
		bool isOccupied(int r, int c);
		bool addCreature(Creature *bug, int r, int c);
		bool removeCreature(int r, int c);
		bool moveCreature(char type, int currX, int currY, int nextX, int nextY);
		char getChar(int r, int c);
		Creature* getCreature(int r, int c);
};

class Creature{
	protected:
		char type; //each creature will be identified as a 'D' or 'A'
		int row; //row coord
		int col; //col coord
		int age; //how old the bug is in days
		int num; //identifying number for removing or adding it onto the linked list
		Island *isl;

	public:
		Creature(char insect, Island *island, int *n);
		Creature(char innsect, Island *island, int *n, int r, int c);
		void move();
		void grow();
		int getNum();
		char getType();
		char getNeighbor(int r, int c);
};
