#include <cstdlib>
#include <ctime>
#include <string>

#include "Doodlebug.h"
#include "Ant.h"
#include "myList.h"


//Main function puts together all of the classes written together
//Outputs a grid of the simulation, 5 doodlebugs will be seeded
// and 100 ants will be seeded, then they will interact with each other
int main(int argc, char** argv){
	int sleepVal = 750; //default mySleep value
	//Debug loop, will check for -d flag and if it is followed by a valid integer string
	for(int i = 0; i < argc; i++){
		std::string str1 = argv[i];
		if(str1.compare("-d") == 0){
			if(i+1 < argc){ //check if -d flag is followed by any other command line argument
				int flag = 1;
				std::string str2 = argv[i+1];
				unsigned long i = 0;
				while(i < str2.length()){ //check if it is a valid integer
					if(!isdigit(str2[i])){
						flag = 0; //if not then break out
						break; 
					}
					i++;
				}
				if(flag == 0){
					break;
				}
				else{
					sleepVal = stoi(str2); //otherwise it is valid int, change it to a int using stoi and store in new updated mySleep value
					printf("Changed sleepVal to %d\n", sleepVal);
				}
			}
			else{
				break;
			}
		}
	}

	srand(time(NULL)); //psuedo random results
	GridDisplay gd; //initialize grid here
	gd.mySleep(500); // put a delay to show output of debug information
	Island island(&gd); //initialize island
	

	int numDood = 0; //identifier number for doodlebug
	int numAnt = 0; //identifier number for ant

	myList *dBugs = new myList(); //create a list for doodlebug movements
	myList *ants = new myList(); //create a list for ant movements

	Doodlebug *tmpD;
	Ant *tmpA;

	//loop that will initialize doodlebugs onto grid and add them to list
	for(int i = 0; i < 5; i++){
		tmpD = new Doodlebug('D', &island, &numDood);
		dBugs->insertValue(tmpD);
	}

	//loop that will initialize ants onto grid and add them to list
	for(int i = 0; i < 100; i++){
		tmpA = new Ant('A', &island, &numAnt);
		ants->insertValue(tmpA);
	}

	//make all empty spaces just a blank space
	for(int i = 0; i<20; i++){
		for(int j = 0; j<20; j++){
			if(island.isOccupied(i,j) == false){
				gd.setChar(i,j,' '); //empty state
			}
		}
	}

	gd.showGrid(); //show initial grid
	Creature *spawn; //pointer for new spawns
	myNode *tmp; //walker pointer node to walk through each list
	while(1){
		tmp = dBugs->returnHead(); //do doodlebugs first set walker to head of doodlebug list
		
		//go through the whole list of dbugs and do each of their movements
		while(tmp != NULL){
			tmpD = (Doodlebug*)tmp->bug; //set doodlebug pointer to current bug on the list
			tmpA = (Ant*)tmpD->hunt(); //attempt to hunt
			if(tmpA == NULL){ //if no ant was killed
		    	tmpD->move(); //do a movement
			}
			else{
				ants->deleteValue(tmpA->getNum()); //else remove that ant from the ant list
			}
			spawn = tmpD->spawn(&numDood);//attempt to spawn a doodlebug
			if (spawn != NULL){
				dBugs->insertValue(spawn); //if spawn was successful insert it into list
			}
			if(tmpD->starve() == true){ //check for starvation
				tmp = tmp->next; //make sure to go to next node on the list
				dBugs->deleteValue(tmpD->getNum()); //remove current doodlebug from list he dead
			}
			else{
				tmpD->grow(); //otherwise age and go to next doodlebug
				tmp = tmp->next;
			}
		}
		
		//go through whole list of ants here
		tmp = ants->returnHead(); //first set walker to head of ant list
		while(tmp != NULL){
			tmpA = (Ant*) tmp->bug; //set ant pointer to current bug on the list
			tmpA->move(); //move the ant
			spawn = tmpA->spawn(&numAnt); //attempt to spawn another ant
			if(spawn != NULL){
				ants->insertValue(spawn); //if spawn is successfull add it to the ant list
			}
			tmpA->grow(); //age ant
			tmp = tmp->next; //go to next ant
		}

		gd.showGrid(); //show updated grid
		gd.mySleep(sleepVal); //delay
	}
}

