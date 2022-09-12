// File:   cIntList.cpp
// Author: Austin Lehman
// Date:   10/4/2021
//
// Class Implemented CintList(documentation on .h file)

#include <iostream> //provides cout/cin
#include "cIntList"     //provides .h file for cIntList class

using namespace std; //Allows all standard library items to be used

//constructor sets list size
cIntList::cIntList (int count) { 
    capacity = count; // sets list capacity to current size
    a = new int [count]; // creates new array with size given 
    count = 0; // sets initial count to 0
    first = 0; //set first positions in circular list to 0
    last = 0; //set last position in circular list to 0
}

//destructor deletes list
cIntList::~cIntList () { 
    delete [] a;
}

//MODIFICATION PRIVATE FUNCTIONS

//increments value of item given to move through circular list
void cIntList::incVal (int &value) {
    value = (value + 1) % capacity;
}

void cIntList::incVal (int &value) const {
    value = (value + 1) % capacity;
}
//decrements value of item given to move through circular list
void cIntList::decVal (int &value) {
    value = (value + capacity - 1) % capacity;
}

void cIntList::decVal (int &value) const {
    value = (value + capacity - 1) % capacity;
}

//MODIFICTION MEMBER FUNCTIONS
bool cIntList::insert (int v) {
    bool check = false; //default check set to false

    if (count < capacity) { //check if room to add new value
        decVal(first); //decrement first position to insert new item
        a[first] = v; //assign value at new first position with value
        count++; //increment count
        check = true; //set check to true for item insert

        if (count == 1) { //if there is only one item in list after add
            last = first; // set last index value to first
        }
    }
   return check; //return true/false if item was inserted or not
}

bool cIntList::add (int v) { //add given value to list
    bool check = false; //default check set to false

    if (count < capacity) { //check if room to insert new value
        incVal (last); //increment last position to add new item
        a[last] = v; //assign value at new last position with value
        count++; //increment count
        check = true; //set check to true for item insert
        
        if (count == 1) { //if there is only one item after insert
            first = last; //set first index value to last
        }
    }
    return check; //return true/false if item was added or not
}

bool cIntList::insertAt (int v, int index) {
    bool check = false; //default check set to false
    int look = last; //look set for checking index positions

    // check if room for new insert, if index <= count to avoid gaps in array
    // and that index >= 0 for valid insertion point.
    if (count < capacity && index <= count && index >= 0) {
        
        if (index == 0) { //case one if item is being inserted at index position 0
           check = insert(v); //insert item using insert function, set check to true if inserted
        
        }else if (index == count - 1) {  //case two if item is being added to end list
            check = add (v); //add item using add set check to true if added
        
        }else { //case three if item is being inserted is not first or last
            for(int i = count; i > index; --i) { //loop through index to access each position
                //shift items for new item to be inserted
                a[(look + 1) % capacity] = a[look]; //current value is shifted right one position
                decVal (look); //look assigned to previous position   
            }
            look = (first + index) % capacity ; //next position in list is assigned current
            a [look] = v; //current index position is set to value given
            incVal (last); //increment last position to account for inserted item
            check = true; //check set to true to account for inserted item
            count++; // increment count
        }
    }
    return check; //return true/false if item was inserted
}

bool cIntList::deleteAt (int index, int &value) { 
    bool check = false;
    int holdValue;
    int look = (first + index)% capacity;

    //check if item being deleted in bounds of array
    if (index >= 0 && index < count) {

        if (index == 0) { //case one if item being deleted is first in list
            //call deleteFirst, return value to holdValue and set check
            check = deleteFirst(holdValue); 

        }else if (index == count - 1) { //case two if item being deleted is last in list
            //call deleteLast, return value to holdValue and set check
            check = deleteLast(holdValue);

        }else { //case three if item being deleted is not first or last
            holdValue = a[look]; 
            //Step 2. continue where previous look left off, shift items over one
            for (int i = index; i < count; i++) { //loop through array
                a[look] = a[(look + 1) % capacity]; //shift next item to the left by one
                incVal(look); //set look to next position in list
           }
            decVal (last); //set last to previous position in array
            count--; //decrement count
            check = true; //set check to true for removal
        }
        value = holdValue; //set original value to value of item removed
    }

    return check; //return true/false if an item was deleted from the list
}

bool cIntList::deleteFirst (int &value) {
    bool check = false; //default check set to false

    if (count > 0 ) { //if there is an item to be removed
        value = a[first]; //set value to value of first item in array
        incVal (first); // change first to next index in array
        count--; //decrement count
        check = true; //set check to true for item removal
            
        if (count == 0) { //if after deletion list is empty
            //set first and last value to 0 for redundancy
            first = 0;
            last = 0;
        } 
    } else {
        value = -1;
    }
    return check; //return true/false if item was removed from list
}

bool cIntList::deleteLast (int &value) {
    bool check = false; //default check set to false

    if (count > 0 ) { //check if there is an item to be removed
        value = a[last]; //set value to value of last item in list
        decVal (last); //change last to previous index in array
        count--; //decrement count
        check = true; //set check to true for item removal
       
        if (count == 0) { //if after deletion list is empty
            //set first and last to 0 for redundancy
            first = 0; 
            last = 0;
        }
    }
    return check; //return true/false if item was removed from the list
}

void cIntList::clear () { //causes list to be cleared
    //set count, first, and last to 0 to clear list
    count = 0;
    first = 0;
    last = 0;  
}

//CONSTANT MEMBER FUNCTIONS
int cIntList::find (int v) const { //find value of given value if is in list
    int look = first; //set look to first position in list
    int rc = -1; //set return code to -1 default

    if(count > 0){ //check if there are any items in list
        for (int i = 0; i < count; i++) { //loop through entire array
            
            if (a[look] == v) { //of the item in current index == value being searched for
                rc = i; //set rc to current i(index)
                break; //break out of loop
            
            }else { //if current index != value 
                look = (look + 1) % capacity; //set look index to next position in list
            }
        }
    }
  return rc; //return rc(-1 if item not found, else index of first occurrence of item found)
}

void cIntList::printIt () const { // will print item position and value of list
    int look = first; //set look to first position in list

    for (int i = 0; i < count; ++i) { //loop through entire list
        //print current index and current value of index   
        cout << "At pos " << i << " there is " << a[look] << endl; 
        incVal(look); //set look index to next position in array
    }
}

int cIntList::length () const {//returns the current number of entries in the list 
    return count;
}
