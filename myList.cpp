#include "Creature.h"
#include "myList.h"

//simple constructor function, just sets head to NULL
myList::myList(){
	head = NULL;
}

//Linked list function to insert a node
int myList::insertValue(Creature *b){
	if(head == NULL){ //if no node has been added yet
		myNode* hd = new myNode;
		hd->bug = b;
		hd->next = NULL;
		head = hd;
		return 1;
	}
	myNode *tmp = head; //tmp to loop through the linked list
	myNode *add = new myNode; //make new node that will be added
	add->bug = b;
	add->next = NULL;
	while(tmp != NULL){
		if(tmp->next == NULL){ //if the next thing is null add the new node here
			tmp->next = add;
			return 1; // return true for adding a node
		}
		else{
			tmp = tmp->next;
		}
	}
	return 1; //never should get here, but g++ was whining
}

//linked list function to remove a node
int myList::deleteValue(int num){
	if(head == NULL) return -1; //check if nothing is on the list return a false
	if(head->bug->getNum() == num){ //if were removing the head
		myNode *tmp = head;
		head = head->next;
		delete tmp;
		return 1; //return true for removal
	}
	myNode *walker = head->next; //walker var
	myNode *lagWalker = head; //have a walker "lag" behind so we can reconnect the list
	while(walker != NULL){
		if(walker->bug->getNum() == num){ //if value found
			lagWalker->next = walker->next; //remake the link using the lag walker
			delete walker;
			return 1;
		}
		lagWalker = walker;
		walker = walker->next;
	}
	return -1;
}



//remove all the nodes recursively
void myList::deleteAll(){
	if(head == NULL) return;
	myNode *walker = head;
	myNode *tmp;
	while(walker != NULL){
		tmp = walker;
		walker = walker->next;
		delete tmp;
	}
	head = NULL;
}

myNode* myList::returnHead(){
	return head;
}
