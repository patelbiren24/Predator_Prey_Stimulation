bpate37: bpate37.cpp GridDisplay.o Creature.o Ant.o Doodlebug.o myList.o
	g++ -o bpate37 bpate37.cpp GridDisplay.o Creature.o Ant.o Doodlebug.o myList.o

Ant.o: Ant.cpp Ant.h 
	g++ -c Ant.cpp 

Doodlebug.o: Doodlebug.cpp Doodlebug.h
	g++ -c Doodlebug.cpp 

Creature.o: Creature.cpp Creature.h
	g++ -c Creature.cpp

GridDisplay.o: GridDisplay.cpp GridDisplay.h
	g++ -c GridDisplay.cpp

myList.o: myList.cpp myList.h
	g++ -c myList.cpp 

clean:
	rm bpate37 *.o
