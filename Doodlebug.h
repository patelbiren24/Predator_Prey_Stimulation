#pragma once
#include "Creature.h"

class Island;

class Doodlebug : public Creature{
	private:
		int lastEaten;
	
	public:
		Doodlebug(char type, Island *island, int *n);
		Doodlebug(char type, Island *island, int *n, int r, int c);
		Creature* hunt();
		bool starve();
		Doodlebug* spawn(int *n);
};
