// File:   DirectedGraph.h
// Author: Austin
// Date:   12/3/2021
// This file provides the pre/post conditions and instructions for the proper utilization of the 
// dGraph class and their respective member functions.

// CLASS PROVIDED: dGraph
//
// CONSTRUCTORS for the dGraph class:
//   dGraph(int size);
//
// DESTRUCTOR for the dGraph class:
//   ~dGraph();
//
// MODIFICATION MEMBER FUNCTIONS for the dGraph class:
// 
//bool createV(int label);
// Pre-conditions: Node with given label must not already exist. There must be room to add new node.
// Post-conditions: Returns true if the node is created. Returns false if it does not get created.
//
//bool addEdge(int uLabel, int vLabel, int weight);
// Pre-conditions: Weight must be greater than 0 and an edge must not already exist.
// there should be room to add new vertices if the labels have not already been created.
// Post-conditions: Returns true is the edge is added, and false if it is not added.
//
//bool deleteEdge(int uLabel, int vLabel);
// Pre-conditions: Two nodes must exist. Edge must already exist.
// Post-conditions: Returns true if edge is deleted, and false if it is not deleted.
//
//bool dijkstra(int sLabel, int dLabel, int &distance);
// Pre-conditions: The two nodes must exist and there must be a path connecting the nodes. The Graph must 
// not have Cycles.
// Post-conditions: The shortest distance between the two nodes be returned as distance, and True will be returned
// If there was no path between the nodes -1 will be returned as distance and False will be returned.
//
//void clear();
// Pre-conditions: No Pre-conditions.
// Post-conditions: The graph will be cleared
//
//bool isEdge(int uLabel, int vLabel) const;
// Pre-conditions: No Pre-conditions.
// Post-conditions: True will be returned if there is an edge between 2 labels provided.
// If there is not an edge false will be returned
//
//bool isPath(int ulabel, inv vlabel) const;
// Pre-conditions: Both labels given must exist.
// Post-conditions: Returns true if the path exists, and returns false if either label 
// does not exist or if there is no path from the first label to the second.
//
//bool isV(int label) const;
// Pre-conditions: No Pre-conditions.
// Post-conditions: True will be returned if there is a node of label passed. If the node 
// does not exist False will be returned.
//
//int inDegree(int label) const;
// Pre-Conditions: No Pre-conditions.
// Post-conditions: will return the number of nodes directed to label.
// If the node does not exist -1 will return
//
//int outDegree(int label) const;
// Pre-conditiono: No Pre-conditions.	
// Post-conditions: Will return the number of nodes that current label directed to. will
// return -1 if the node does not exist.
//
//int sizeV() const;
// Pre-conditiono: No Pre-conditions.	
// Post-conditions: Will return the total amount of nodes that can be 
// held.
//
//int sizeUsedV() const;
// Pre-conditiono: No Pre-conditions.	
// Post-conditions: Will return the number of nodes that are currently used
//
//int sizeE() const;
// Pre-conditiono: No Pre-conditions.	
// Post-conditions: Will return the number of edges in the graph.
//
//void printIt() const;
// Pre-conditiono: No Pre-conditions.	
// Post-conditions: Will print the entire Graph.
//
//void printPaths() const;
// Pre-conditions: No pre-conditions.
// Post-conditions: Prints if there is a path from each node, to each other node.
//
//void bfPrint(int label) const;
// Pre-conditions: Non pre-conditions.
// Post-conditions: Prints out nodes starting at given node and then breadth-first 
// traverses through the nodes.




#ifndef P10_H
#define P10_H

#include "iq.h"


class dGraph {
    private:
	int *a;
	int *labels;
	iQ *q;
	int *lambda;
	int *set;
	int n;
	int vCount;
	int eCount;
	int const INFINITE = 1000000;
	int const X = 0;
	int const Y = 1;

	int ind(int x, int y) const;
	int min(int x, int y) const;
	int max(int x, int y) const;
	int indexV(int label) const;
	void dijkstra(int s);
	bool minLambdaY(int &minV) const;

    public:
	dGraph(int n = 100); 

	~dGraph(); 

	bool createV(int label);
	bool addEdge(int uLabel, int vLabel, int weight);
	bool deleteEdge(int v, int w);
	bool dijkstra(int sLabel, int dLabel, int &distance);
	void clear();
	bool isCyclic();

	bool isEdge(int uLabel, int vLabel) const;
	bool isV(int label) const;
	int weightEdge(int uLabel, int vLabel) const;
	int inDegree(int label) const;
	int outDegree(int label) const;
	int sizeV() const;
	int sizeUsedV() const;
	int sizeE() const;
	void bfPrint(int label) const;
	bool isPath(int ulabel, int vlabel) const;
	void printIt() const;
	void printPaths() const;
	void printItAll() const;
};

#endif
