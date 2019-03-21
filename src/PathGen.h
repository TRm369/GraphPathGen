#pragma once
#include "../stdafx.h"
#include "Graph.h"
#include "FILOcontainer.h"
#include "CircQueue.h"

class PathGen {
public:
	PathGen(Graph& Graph);

	//Sets the destination node - node at which the generated path should end.
	bool setDestID(int ID);
	int getDestID();

	//Returns a randomly generated path from a given node to destination node.
	//  Returns a vector. First element is the starting node, last is the destination node.
	vector<int> genRandomPath(int startID, float maxLength);

	void setOnStepCB(void(*CB)(vector<int>));

private:
	Graph& graph;

	int destID = -1;

	void(*onStep)(vector<int>);

	////To reduce reallocating memory, containers for some functions are kept here, allocated once and reused
	//UpdateDist
	FILOcontainer<pair<Node*, float>> updateDistFILO1;
	FILOcontainer<pair<Node*, float>> updateDistFILO2;
	CircQueue<flags_t*> updateDistCQ1;

	////Path generation helper funcs

	//Calculates each node's (shortest) distance to the destination node
	void calculateDistances();

	//Defines the rules for valid road candidates.
	bool isRoadCandidate(Node* node, float maxDist);

	//Recalculates the distance of a node
	void updateDistance(Node* node);
};