#pragma once
#include "Creature.h"

class Ant : public Creature{
	public:
		Ant(char insect, Island *island, int *n);
		Ant(char insect, Island *island, int *n, int r, int c);
		Ant* spawn(int *n);
};
