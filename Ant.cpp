#include "Ant.h"

//Constructor for the ant, just a call parent constructor
Ant::Ant(char insect, Island *island, int *n):
Creature(insect, island, n)
{}

//mapped constructor for ant, just call parent mapped constructor
Ant::Ant(char insect, Island *island, int *n, int r, int c):
Creature(insect, island, n, r, c)
{}

//ant spawn function, is the same as doodlebug spawn function, just the age needed to be checked is 3
Ant* Ant::spawn(int *n){
	Ant *tmp = new Ant('A', isl, n, row, col);
	if(age >= 3){
		if(isl->addCreature(tmp,row+1, col) == true){
			tmp->row = this->row + 1;
			(*n)++;
			age = 0;
			return tmp;
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
			return NULL;
		}
	}
	else{
		return NULL;
	}
}
