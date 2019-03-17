#pragma once

#include "../stdafx.h"
#include "Node.h"

class Graph {
public:
	Graph(int nodeCount);
	~Graph();

	////Graph construction

	//Initializes a new node and returns its ID
	int initNewNode(edgeCount_t edgeInMaxCount, edgeCount_t edgeOutMaxCount);

	//Creates a one-directional edge between two nodes
	//  Returns true on success
	bool addEdge(int IDsrc, int IDdest, float weight);

	//Creates a bi-directional edge between two nodes
	//  Returns true on success
	bool addBidirEdge(int ID1, int ID2, float weight);

	////Graph info

	//Returns node's (shortest) distance to the destination node, -1 for invalid nodes, -2 for invaldated distances
	float getDistance(int nodeID);

	int maxOutEdges();

	////Loop functions
	//Keeping the looping through the nodes array in this class instead of in the PathGen class seems (according to some medium-effort testing) faster.

	//Clears all calculated values and assigned roads.
	void resetGraph();

	void resetDistances();

	//Sets the invalidated flag for nodes whose distance is greater than distance
	void invalidateNodes(float distThres);

	//Sets the flags set in the mask for all nodes
	void setFlags(flags_t mask);

	//Clears the flags set in the mask for all nodes
	void clearFlags(flags_t mask);

	////Container functions
	
	int size();
	int maxSize();
	Node* operator[](int index);

protected:
	//Array of pointers to all nodes
	Node** nodes;
	int nodeCount;

	//Initialized node count
	int initdNodes;

	//The maximum number of edges going out of a node
	int _maxOutEdges = 0;
};