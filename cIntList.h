// File:   cIntList.h
// Author: Austin Lehman
// Date:   10/4/2021
// This file provides the pre/post conditions and instructions for the proper utilization of the 
// cIntList class and their respective member functions.

// CLASS PROVIDED: cIntList
//
// CONSTRUCTORS for the cIntList class:
//   cIntList(int size);
//
// DESTRUCTOR for the cIntList class:
//   ~cIntList();
//
// MODIFICATION MEMBER FUNCTIONS for the cIntList class:
// 
// bool insert (int v);
// Precondition: The list must have room for a new item.
// Postcondition: The value passed will be placed at the beginning of the list
// If a number is inserted into the list "true" will be returned, else "false" will be returned.
//
// bool add (int v);
// Precondition: The list must have room for a new item.
// Postcondition: The value passed will be placed at the end of the list. If a number is added
// to the list "true" will be returned, else "false" will be returned.
//
// bool insertAt( int v, int index);
// Precondition: The list must have room for a new item, and the index value must be greater than
// or equal to 0 and  less than the length of list.
// Postcondition: The value passed will be placed at the index position chosen. If a number is
// added to the list "true" will be returned, else "false" will be returned. 
//    
// bool deleteAt( int  index, int &value);
// Precondition: index position must be greater than or equal to 0 and less than length 
// Postcondition: if an item is removed, "true" will be returned and the item that was removed
// will have its value returned. If an item is not removed false will be returned, and the value
// will not be changed.
//
// bool deleteFirst (int &value);
// Precondition: No known Precondition
// Postcondition: The first item in the list will be removed, value will be set to the value of the
// item that was removed, and "true" will be returned. If an item is not removed from the list,
// then "false" will be returned, and the value will not be changed.
//
// bool deleteLast (int &value);
// Precondition: No known Precondition
// Postcondition: The last item in the list will be removed, value will be set to the value of the 
// item that was removed, and "true" will be returned. If an item is not removed from the list,
// then "false" will be returned, and the value will not be changed. 
//
// void clear();
// Precondition: No known Precondition
// Postcondition: All items will be removed from the list.
//
// CONSTANT MEMBER FUNCTIONS for the cIntList class:
//
// int find (int v) const;
// Precondition: No known Precondition 
// Postcondition: if the value is in the list its  first occurrence in the list will be returned. 
// If the value is not in the list, -1 will be returned.
//
// void printIt() const;
// Precondition: No known Precondition
// Postcondition: The values and their corresponding list positions will be sent to the 
// desired output device for the entirety of the list. 
// Each value and position will be displayed on its own line.
//
// int length() const;
// Precondition: No known Precondition
// Postcondition: The current amount of numbers in the list will be sent to the 
// desired output.
//

#ifndef P3_H
#define P3_H //macro Guard Start

class cIntList {
    private:
    //PRIVATE MEMBER VARIABLES
	int *a; 
	int capacity; 
	int count;
	int first;
	int last; 

	//PRIVATE MEMBER FUNCTIONS
	void incVal (int &value) ;
	void incVal (int &value) const;
	void decVal (int &value) ;
	void decVal (int &value) const;

    public:
    //CONSTRUCTORS
	cIntList (int count = 100); 

	~cIntList (); 

	//MODIFICATION MEMBER FUNCTIONS
	bool insert (int v);

	bool add (int v); 

	bool insertAt (int v, int index); 

	bool deleteAt (int index, int &value); 

	bool deleteFirst (int &value);

	bool deleteLast (int &value);
	
	void clear ();

	//CONSTANT MEMBER FUNCTIONS
	int find (int v) const; 

	void printIt () const; 

	int length () const; 
};

#endif //end macro guard
