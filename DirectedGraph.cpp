// File:   DirectedGraph.cpp
// Author: Austin Lehman
// Date:   12/3/2021
// Class Implemented dGraph(documentation on .h file)

#include <iostream> //provides cout/cin
#include "DirectedGraph.h"     //provides .h file for intList class

using namespace std; //Allows all standard library items to be used


//CONSTRUCTOR
dGraph::dGraph(int n) {
	vCount = 0; //sets count of vertex to 0
 	eCount = 0; //sets count of edges to 0
	q = new iQ(n); //creates queue array
	lambda = new int [n]; //create lambda array for dijkstra
	set = new int [n]; //create set array for dijkstra
	labels = new int [n];//creates labels array
	a = new int [n*n]; //creates adjacency matrix
	this ->n = n; //sets n size to size of matrix
    clear(); //call clear to set all values in arrays
}

//DESTRUCTOR
dGraph::~dGraph() { 
    delete [] a; //delete matrix array
    delete [] labels; //delete label array
    delete [] set;//delete set array
    delete [] lambda;// delete lambda array
    delete  q; //deletes queue array
}

//PRIVATE MEMBER FUNCTIONS
void dGraph::dijkstra(int s) {
	int tempDist; //holds temp distance
	int next = s;//hold next
	
	fill_n(set, n, Y); //set all vallues to set Y 
	fill_n(lambda, n, INFINITE);//set all values in lambda to infinite

	lambda[s] = 0; //set intital value distance to 0

	for (int i = 0; i < n; i++) { //loop through set

		if (minLambdaY(next)) {  //if there are any y values in the Y set
			set[next] = X; //move y to X set
			
			for (int j = 0; j < n ; j++) { //loop through outgoing vertices in current X value
				if (set[j] == Y && isEdge(labels[next],labels[j])) { //if vertices is Y && has edge to X value
					tempDist = lambda[next] + a[ind(next, j)]; //temp distance calculated
					if (tempDist < lambda[j]) { //if temp distance is currently lower than distance at j
						lambda[j] = tempDist; //replace j distance with tempdist;
					}
				}
			}
		}
	}
}

int dGraph::min(int x, int y) const {
	return(x > y ? y : x);//return the smaller value
}

int dGraph::max(int x, int y) const {
	return (x > y ? x : y);//return the larger value
}

int dGraph::ind(int x, int y) const { 
	return ((x * n) + y); //calculate and return index of x,y value on matrix
}

int dGraph::indexV(int label) const {
	int rc = -1; //set rc to -1 for initial state
	for (int i = 0; i < vCount;i++) { //loop through label array
		if (labels[i] == label) { //if label passed is found in array
			rc = i; //set the return code to the labels index
			break; //break loop
		}
	}
	return rc; //return the labels index position in the label array
} 

bool dGraph::minLambdaY(int &minV) const {
	bool rc;
	int minVal = INFINITE; //set temp comparison to infinite
	int indexHold = 0; //will hold the index position

	for (int i = 0; i < n;i++) { //loop through set
		if (set[i] == Y && lambda[i] < minVal ) { //if there is a Y value in the set
			minVal = lambda[i]; //set minVal to the min value 
			indexHold = i; //hold index position for smallest value
		}
	}

	if (minVal == INFINITE) { //if there are no Y values in set
		minV = -1; //set minV to -1
		rc = false; //set rc to false
	} else {  //if there is a Y left in the set
		minV = indexHold; //set minV to smallest Y value index
		rc = true; //set rc to true
	}

	return (rc); //return if there is a min y value
}

// PUBLIC MEMBER FUNCTIONS
bool dGraph::createV(int label) {
	bool rc  = false; //set false if item not created
 
    if (!isV(label)) { // Checking if the vertex does not exist.
        if (vCount < n) { // Checking if there is room in the matrix.
            labels[vCount] = label; // Creating the vertex.
            vCount++; // Increment vertex count.
            rc = true; //item created return true
        }
    }
    return rc;
}

bool dGraph::addEdge(int uLabel, int vLabel, int weight) {
	bool rc = false; //set false if edge not added

	//Go through if all exist then create edge/add count/true change

    if (weight > 0) {  // Weight must be 0
     	// Checks to see if the two vertices exist  && Checks to see if the edge does not already exist.
        if (isV(uLabel) && isV(vLabel) && !isEdge(uLabel, vLabel)) {  
                a[ind(indexV(uLabel), indexV(vLabel))] = weight; // Adding the edge.
                eCount++;  // Increment edge count.
                rc = true;//edge has been added return true
            
        //if neither of the vertices exist & there is space to add 2 new vertices 
        } else if (vCount < n-1 && !isV(uLabel) && !isV(vLabel)) { 
	        	createV(uLabel);  // Creates first node.
	     		createV(vLabel);  // Creates second node.
	     		a[ind(indexV(uLabel), indexV(vLabel))] = weight;  // Adding the edge.
	            eCount++;  // Increment edge count.
	            vCount= vCount+2; //Increment vcount by 2
	            rc = true; //items  have been added return true
        	
        //if one of the vlabel exists & ulabel does not exist
        } else if (vCount < n && !isV(uLabel) && isV(vLabel)) {
        		createV(uLabel);//create uLabel
        		a[ind(indexV(uLabel),indexV(vLabel))] = weight; //Adding the edge
        		eCount++; //increment edge count
        		vCount++; //increment vcount
        		rc = true; //items have been added and edge exists return true
        //if ulabel exists and vlabel doest not exist
        } else if (vCount < n && isV(uLabel) && !isV(vLabel)) {
        		createV(vLabel); //create vLabel
        		a[ind(indexV(uLabel),indexV(vLabel))] = weight; //adding the edge
        		eCount++; //increment edge count
        		vCount++; //increment vcount
        		rc = true; //items have been added and edge exists return true
        }
    }
     return (rc);
}

bool dGraph::deleteEdge(int uLabel, int vLabel) {
    bool rc = false;

    if (isV(uLabel) && isV(vLabel)) { // Checking to see if the two vertices exist.
        if (isEdge(uLabel, vLabel)) { // Checking to see if the edge exist.
            a[ind(indexV(uLabel), indexV(vLabel))] = 0; // Deleting the edge by setting index to 0.
            eCount--;    // Decrementing edge count.
            rc = true; //edge deleted, return true
        }
    }
    return (rc);
}

bool dGraph::dijkstra(int sLabel, int dLabel, int &distance) {
	bool rc;
	//check if sLabel & dLabel exist & there is a path between them
	if (isV(sLabel) && isV(dLabel) && isPath(sLabel, dLabel)) { 
		dijkstra(indexV(sLabel));//calls private dijkstra to calc distances
		//access lambda index of dlabel & set distance to value
		distance = lambda[indexV(dLabel)];
		rc = true; //set rc to true for path found
	} else {
		rc = false; //if there is not a path from slabel to dlabel set false
		distance = INFINITE;  //set distance to -1 to return no path
	}

	return (rc);
}

void dGraph::clear() {
	//set vCount & eCount to 0 
	vCount = 0; 
	eCount = 0;

	fill_n(labels,n,-1);//set all values in labels to -1
	fill_n(a,n * n,0);//set all values in a to 0
}

//CONSTANT MEMBER FUNCTIONS
bool dGraph::isEdge(int uLabel, int vLabel) const {
	bool rc = false; //set rc to false if not edge
	if (isV(uLabel) && isV(vLabel)) { //if 2 vertices exist
		if (a[ind(indexV(uLabel), indexV(vLabel))] > 0) { //if the position in the index is greater than 0
			rc = true; //there is an edge return true
		}
	}
	return (rc);
}

bool dGraph::isV(int label) const { 
	return (indexV(label)>=0 ? true : false); //return true if label is in array
}

bool dGraph::isPath(int uLabel, int vLabel) const {
	bool rc = false; //set rc to false if no path exists
	int holdtest = 0; //will hold values of dequed label
	bool *marked; //pointer to create marked array
	int vhold = indexV(vLabel); //hold index of vlabel so doesnt need to calc every loop
	int uhold = indexV(uLabel); //hold ind of ulabel so does not need to calc multiple times


	if (isV(uLabel) && isV(vLabel)) { // if both labels exist									
		marked = new bool[n];//create local marked array
		fill_n(marked, n, false);//set all values in marked to false
		q->enq(uhold); //push ulabel into queue
		marked[uhold] = true; //set index position for ulabel to true

		if (a[ind(indexV(uLabel), indexV(vLabel))] > 0) { //if there is a path from node to itself
			rc = true;
		}

		while (q->deq(holdtest) && !rc) { //will break when queue is empty  or if u->v was a path from node to itself
			for (int i = 0; i < n; i++) { //loop through current bounds set
				if (a[ind(holdtest,i)] > 0 && marked[i] == false) {  //if position has a degree && has not been visited
					if (i == vhold) { //if label marked is vLabel
					 	rc = true; //there is a path, set true
				 		break; //break out of loop
					} else {
						marked[i] = true; //mark neighbor as visited
						q->enq(i); //add neighbor to queue
					}
				}
			}
		}

		delete [] marked; //release memory from marked if marked created
	}

	return (rc);
}

int dGraph::inDegree(int label) const {
	int count = 0; //set count tracker to 0 for tracking out degree
	
	if (isV(label)) { //check label is in array
		for (int i = 0;i < n; i++) { //loop through array
			if (a[ind(i, indexV(label))] > 0) { //if position has a degree
				count++; //increment count
			}
		}
	} else {
		count = -1; //set to -1 if label is not in array
	}

	return (count);
}

int dGraph::outDegree(int label) const {
	int count = 0; //set count to 0 for tracking degree
	if (isV(label)) { //check if label is in array
		for (int i = ind(indexV(label), 0); i < ind(indexV(label), n); i++) { //loop through current bounds set
			if (a[i] > 0) {  //if position has a degree
				count++; //increment count 
			}
		}
	} else {
		count = -1; // set to -1 if label is not in array
	}
	return (count);
}

int dGraph::sizeV() const {
	return (n); //return size of array
}

int dGraph::sizeUsedV() const {
	return (vCount); //return number of vertices
}

int dGraph::sizeE() const {
	return (eCount); //return number of edges
}

void dGraph::printIt() const {
    int r, c; //initialize int holders

    //print general graph information
    cout << "Graph info:\n";
    cout << "  Graph size = " << n << endl;
    cout << "  vCount = " << vCount << endl;
    cout << "  eCount = " << eCount << endl;
    cout << "\nGraph contents:\n";
    for (r = 0; r < vCount; r++) { //loop through graph to print graph layout
	cout << "  Node(" << r << "," << labels[r] << "):";
	for (c = 0; c < vCount; c++) {
	    cout << " " << a[ind(r,c)];
	}
	cout << endl;
    }

    cout << "Degree table (in, out)\n";
    //loops through graph to print in/outdegree
    for (r = 0; r < vCount; r++) { //loop through
	cout << "  Node(" << r << "," << labels[r] << "):";
	cout << " " << inDegree(labels[r]) << ", " << outDegree(labels[r]) << endl;
    }
}

void dGraph::printPaths() const {
	//loop through labels array gathering positions of i & j
	for (int i =  0; i < vCount; i++) { 
		for (int j = 0; j < vCount; j++) {
			if (isPath(labels[i], labels[j])) { //print if there is a path between current i & j value
				cout << labels[i] << " does have a path to " << labels[j] << endl;
			} else { //print if there does not exist a path between current i & j value
				cout << labels[i] << " does not have a path to " << labels[j] << endl;
			}
		}
	}
}

void dGraph::bfPrint(int label) const {
	bool rc = false; //set rc to false if no path exists
		int track = 1; //set track to follow position in loop
		int holdtest = 0; //will hold values of dequed label
		bool *marked; //pointer to create marked array

		if (isV(label)) { // if both labels exist									
			marked = new bool[n];//create local marked array
			fill_n(marked,n,false);//set all values in marked to false
			q->enq(indexV(label)); //push ulabel into queue
			marked[indexV(label)] = true; //set index position for ulabel to true

			//print initial label passed
			cout << "	Item " << 0 << " is ";
			cout << "(" << indexV(label) << ", " << labels[indexV(label)] << ")" << endl;;

			while (q->deq(holdtest)) { //will break when queue is empty  or if u->v was a path from node to itself
				for (int i = 0; i < n; i++) { //loop through current bounds set
					if (a[ind(holdtest,i)] > 0 && marked[i] == false) {  //if position has a degree && has not been visited
						//print all other labels that are connected to label
						cout << "	Item " << track << " is ";
						cout << "(" << i%n << ", " << labels[i%n] << ")" << endl;
						marked[i] = true; //mark neighbor as visited
						q->enq(i); //add neighbor to queue
						track++;
					}
				}
			}
		delete [] marked; //release memory from marked if created
		}
}
