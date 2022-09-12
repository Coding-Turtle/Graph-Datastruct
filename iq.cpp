// File:   iQ.cpp
// Author: Austin Lehman
// Date:   12/2/2021
// Class Implemented intQueue(documentation on .h file)

#include <iostream> //provides cout/cin
#include "iq.h"     //provides .h file for cIntList class


using namespace std; //Allows all standard library items to be used

//constructor sets list size
iQ::iQ (int n) { 
   list = new cIntList(n);
}

//destructor deletes list
iQ::~iQ() { 
    delete list;
}

//MODIFICATION MEMBER FUNCTIONS
    bool iQ::enq(int val) {
        return (list -> add(val)); //use cintlist to add item to queue
    }

    bool iQ::deq(int &val) {
        return (list -> deleteFirst(val));//use cintlist to remove item from queue
    }

    void iQ::clear() {
        list -> clear(); //clear queue
    }

    //CONSTANT MEMBER FUNCTION
    void iQ::printIt() const {
        list -> printIt(); //prent entire queue
    }

    int iQ::count() const {
        return (list ->length()); //return count of items in queue
    }



