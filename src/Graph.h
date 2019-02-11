#pragma once

#include "../stdafx.h"
#include "Node.h"
#include "CircQueue.h"

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
	int initNewNode(uint16_t edgeInMaxCount, uint16_t edgeOutMaxCount);

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
	///Calculates each node's (shortest) distance to a given destination node
	///</summary>
	void calculateDistances(int destID);

	///<summary>
	///Returns node's (shortest) distance to the destination node
	///</summary>
	float getDistance(int nodeID);

	int getDestID();

protected:
	//Array of pointers to all nodes
	Node** nodes;
	int nodeCount;

	//Initialized node count
	int initdNodes;

	//Graph info
	int destNodeID = -1;
};