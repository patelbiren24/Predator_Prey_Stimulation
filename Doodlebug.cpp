#include "Doodlebug.h"

//constructor for doodlebug, will just call parent constructor
Doodlebug::Doodlebug(char type, Island *island, int *n):
Creature(type, island, n)
{
	lastEaten = 0; //doodlebug have their own lastEaten attribute
}

//mapped constructor for doodlebug, will just call parent constructor
Doodlebug::Doodlebug(char type, Island *island, int *n, int r, int c):
Creature(type, island, n, r, c)
{
	lastEaten = 0; //doodlebug have their own lastEaten attribute
}

//Doodlebug hunt method, will check its adjacent tiles for possible Ants, if none is found increment its starvation attribute
Creature* Doodlebug::hunt(){
	Creature *tmp;
	//if statements will check the 4 adjacent tiles, up down left right for ants
	if(getNeighbor(row+1, col)== 'A'){ //call the get neighbor function, if we get a match for an ant
		tmp = isl->getCreature(row+1, col); //get the creature pointer of the ant that will be eaten
		isl->removeCreature(row+1, col); //remove that ant from the island array
		isl->moveCreature('D', row, col, row+1, col); // move the doodlebug to that spot
		row = row+1; //update its coordinate attributes
		lastEaten = 0; //update its starvation counter
		return tmp; //return the pointer of that creature that was eaten so it can be removed from the linked list
	}
	else if(getNeighbor(row-1, col) == 'A'){
		tmp = isl->getCreature(row-1, col);
		isl->removeCreature(row-1, col);
		isl->moveCreature('D', row, col, row-1, col);
		row = row - 1;
		lastEaten = 0;
		return tmp;
	}
	else if(getNeighbor(row, col+1) == 'A'){
		tmp = isl->getCreature(row, col+1);
		isl->removeCreature(row, col+1);
		isl->moveCreature('D', row, col, row, col+1);
		col = col+1;
		lastEaten = 0;
		return tmp;
	}

	
	else if(getNeighbor(row, col-1) == 'A'){
		tmp = isl->getCreature(row, col-1);
		isl->removeCreature(row, col-1);
		isl->moveCreature('D', row, col, row, col-1);
		col = col-1;
		lastEaten = 0;
		return tmp;
	}
	else{ //no ant found
		lastEaten++; //increment starvation
		return NULL; //return nothing
	}
}

//function that will check if the doodlebug has starved or not
bool Doodlebug::starve(){
	if(lastEaten >= 3){ //has it been 3 days?
		isl->removeCreature(row, col); //remove the doodlebug from the island
		return true; //return true
	}
	return false; //not starving yet
}

//spawn method for the doodlebug
Doodlebug* Doodlebug::spawn(int *n){
	Doodlebug *tmp = new Doodlebug('D', isl, n, row, col); //make a temporary doodlebug
	if(age >= 8){ //if the doodlebug is of age to spawn
		//if statements will try and add a doodlebug to an adjacent spot
		//if it doesnt find a spot the age will continue growing and will check next turn
		if(isl->addCreature(tmp,row+1, col) == true){ //check if creature is added
			tmp->row = this->row + 1; //update tmps coordinates
			(*n)++; //update int identifier for doodlebugs
			age = 0; //reset current doodlebugs age to 0
			return tmp; //return the new doodlebug to add onto the list
		}
		else if(isl->addCreature(tmp, row-1, col) == true){
			tmp->row = this->row - 1;
			(*n)++;
			age = 0;
			return tmp;
		}
		else if(isl->addCreature(tmp, row, col+1) == true){
			tmp->col = this->col + 1;
			(*n)++;
			age = 0;
			return tmp;
		}
		else if(isl->addCreature(tmp, row, col-1) == true){
			tmp->col = this->col - 1;
			(*n)++;
			age = 0;
			return tmp;
		}
		else{
			return NULL; //cant find a spot so return nothing
		}
	}
	else{
		return NULL; //not ready yet return nothing.
	}
}
