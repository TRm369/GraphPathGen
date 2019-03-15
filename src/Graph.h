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
	///Sets the destination node - node at which the generated path should end.
	///</summary>
	bool setDestID(int ID);
	int getDestID();

	///<summary>
	///Returns node's (shortest) distance to the destination node, -1 for invalid nodes, -2 for invaldated distances
	///</summary>
	float getDistance(int nodeID);

	///<summary>
	///Returns a randomly generated path from a given node to destination node.
	///</summary>
	///<remarks>
	///Returns a vector. First element is the starting node, last is the destination node.
	///</remarks>
	vector<int> genRandomPath(int startID, float maxLength);

	///<summary>
	///Clears all calculated values and assigned roads.
	///</summary>
	void resetGraph();

	void setOnStepCB(void(*CB)(vector<int>));

protected:
	//Array of pointers to all nodes
	Node** nodes;
	int nodeCount;

	//Initialized node count
	int initdNodes;

	//Graph info
	int destID = -1;
	int maxOutEdges = 0; //The maximum number of edges going out of a node

	void (*onStep)(vector<int>);

	//Path generation helper funcs
	///<summary>
	///Calculates each node's (shortest) distance to the destination node
	///</summary>
	void calculateDistances();

	///<summary>
	///Defines the rules for valid road candidates.
	///</summary>
	bool isRoadCandidate(Node* node, float maxDist);

	void resetDistances();

	///<summary>
	///Sets the invalidated flag for nodes whose distance may not be valid anymore
	///</summary>
	///<param name="threshold">
	///All nodes with distance greater or equal to this value will have their distances invalidated.
	///</param>
	void invalidateNodes(float threshold);

	///<summary>
	///Recalculates the distance of a node
	///</summary>
	void updateDistance(Node* node);
};