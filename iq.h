// File:   iQ.h
// Author: Austin Lehman
// Date:   12/3/2021
// This file provides the pre/post conditions and instructions for the proper utilization of the 
// iQ class and their respective member functions.

// CLASS PROVIDED: intQueue
//
// CONSTRUCTORS for intQueue
// 	intQueue (int size);
//	
// Destructor for intQueue
// ~intQueue ();
//
// Public Modification Member Functions 
// bool enq (int val);
// Precondition: there is room to add item to queue
// Postcondition: the item has been added to the queue
//
// bool deq (int &val);
// Precondition: no precondition
// Postcondition: an item will be removed from the queue and value will be set to the value
// of the item removed and true will be returned. if an item is not removed false will be returned and
// the value will not be changed
//
// void clear ();
// precondition: no precondition
// postCondition: the queue has been cleared
//
// void printIt() const;
// precondition:no precondition
// postcondition: the queue will be printed out with its current index and value.
// each value will be printed out on its own queue
//
// int count() const;
// precondition: no precondition
// postcondition: the total amount of items in the queue will be returned.

#ifndef iQ_H
#define iQ_H //macro Guard Start
#include "cIntList.h"

class iQ {
	private:
		cIntList * list;
	
	public:
		iQ(int n = 100);
		~iQ();
		bool enq(int v);
		bool deq(int &v);
		void clear();
		void printIt() const;
		int count() const;
};
#endif //end macro guard