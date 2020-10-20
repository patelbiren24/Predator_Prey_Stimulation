#include <cstdio>
#include <cstdlib>
#include "Creature.h"

class myNode{
	public:
		Creature* bug;
		myNode *next;
};

class myList{
	private:	
		myNode *head;

	public:
		myList();
		myNode* returnHead();
		int insertValue(Creature *b);
		int deleteValue(int num);
		void deleteAll();
};
