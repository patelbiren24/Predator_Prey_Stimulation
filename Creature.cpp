#include "Creature.h"

//Island constructor, same as gddemo
Island::Island(GridDisplay *grid){
	gd = grid;
	rows = 20;
	cols = 20;
	location = new Creature**[rows];

	for(int i = 0; i<rows; i++){
		location[i] = new Creature*[cols];
		for(int j = 0; j<cols; j++){
			location[i][j] = NULL;
		}
	}
}

//return rows
int Island::getRows(){
	return rows;
}

//return cols
int Island::getCols(){
	return cols;
}

//check if the set of coordinates is a valid coordinate
bool Island::isValid(int r, int c){ 
	if (( r >= 0 && r < rows ) && ( c >= 0 && c < cols))
	  return true;
	else
	  return false;
}

//check if the coordinate is occupied or not
bool Island::isOccupied (int r, int c){
	if ( location[r][c] == NULL )
	  return false;
	else
	  return true;
}

//add a creature to the coordinate specified and update the grid to reflect the changes
bool Island::addCreature(Creature *bug, int r, int c){
	if(isValid(r,c) == false){
		return false; //check for valid coordinate
	}
	if(isOccupied(r,c) == true){
		return false; //check if it is occupied
	}

	location[r][c] = bug; //if it gets here it means it is valid so set the bug pointer to here
	gd->setChar(r,c, bug->getType()); //make changes to grid
	return true;
}

//function to remove a creature from the island, like an Ant when it gets eaten or a doodlebug when it starves
bool Island::removeCreature(int r, int c){
	if(isValid(r,c) == false){
		return false; //error checker
	}
	if(isOccupied(r,c) == false){
		return false; //error check
	}

	location[r][c] = NULL; //remove creature from location pointer
	gd->setChar(r,c, ' '); //set spot as empty
	return true;
}

//make the movements of the creatures in the island too, this will be called by the creature move function
bool Island::moveCreature(char type,int currX, int currY, int nextX, int nextY){
    // verify to/from locations are valid
    if ( isValid (currX, currY) == false )
      return false;
    if ( isValid (nextX, nextY) == false )
      return false;
    // verify a beetle exists at current location
    if ( isOccupied (currX, currY) == false)
      return false;
    // verify to location is empty
    if ( isOccupied (nextX, nextY) == true)
      return false;
    
    location[nextX][nextY] = location[currX][currY]; 
    location[currX][currY] = NULL; 
    gd->setChar (currX, currY, ' ');
    gd->setChar (nextX, nextY, type);
    return true;
}

//check for the bug type, will be used in the doodlebug hunt function
char Island::getChar(int r, int c){
	return location[r][c]->getType();
}

//return a creature pointer of the bug at that location
Creature* Island::getCreature(int r, int c){
	return location[r][c];
}

//creature constructor for a creature to be put in a random spot
Creature::Creature(char insect, Island *island, int *n){
	type = insect;
	isl = island;
	num = *n;
	age = 0;
	do  // randomly select a location until an empty location is found
    {
       row = rand() % island->getRows();   
       col = rand() % island->getCols();   
    }
    while ( island->addCreature (this, row, col) == false );
	(*n)++;
}

//creature constructor for the spawn functions where we specify the row and columns
Creature::Creature(char insect, Island *island, int *n, int r, int c){
	type = insect;
	isl = island;
	num = *n;
	age = 0;
	row = r;
	col = c;
}

//move a creature
void Creature::move(){
	int nextX;
	int nextY;
	int choice = rand() % 4;//pick a random choice of 4 possible movements
	switch(choice){
		case 0: nextX = row + 1;
				nextY = col;
				break;
		case 1: nextX = row - 1;
				nextY = col;
				break;
		case 2: nextX = row;
				nextY = col + 1;
				break;
		case 3: nextX = row;
				nextY = col - 1;
				break;
		default: return;
	}
	if(isl->moveCreature(type, row, col, nextX, nextY) == true){ //check if the movement is valid
		row = nextX; //if it is update the creatures values
		col = nextY;
	}
}

//function will return identifying number of the creature
int Creature::getNum(){
	return num;
}

//function will return creature type
char Creature::getType(){
	return type;
}

//function that will return the creature's neighbor type
char Creature::getNeighbor(int r, int c){
	if(isl->isValid(r, c) == false){
		return 'e';
	}
	if(isl->isOccupied(r,c) == false){
		return 'e';
	}
	return isl->getChar(r,c); 
}

//aging function for the creatures
void Creature::grow(){
	age++;
}
