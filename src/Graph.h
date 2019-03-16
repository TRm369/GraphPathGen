#pragma once

#include "../stdafx.h"
#include "Node.h"

class Graph {
public:
	Graph(int nodeCount);
	~Graph();

	///<summary>
	///Initializes a new node
	///</summary>
	///<returns>
	///Returns new node's ID
	///</returns>
	int initNewNode(edgeCount_t edgeInMaxCount, edgeCount_t edgeOutMaxCount);

	///<summary>
	///Creates a one-directional edge between two nodes
	///</summary>
	///<returns>
	///Bool succes
	///</returns>
	bool addEdge(int IDsrc, int IDdest, float weight);

	///<summary>
	///Creates a bi-directional edge between two nodes
	///</summary>
	///<returns>
	///Bool succes
	///</returns>
	bool addBidirEdge(int ID1, int ID2, float weight);

	///<summary>
	///Returns node's (shortest) distance to the destination node, -1 for invalid nodes, -2 for invaldated distances
	///</summary>
	float getDistance(int nodeID);

	///<summary>
	///Clears all calculated values and assigned roads.
	///</summary>
	void resetGraph();

//protected: TEMP
	//Array of pointers to all nodes
	Node** nodes;
	int nodeCount;

	//Initialized node count
	int initdNodes;

	//Graph info
	int maxOutEdges = 0; //The maximum number of edges going out of a node
};