#pragma once
#include "../stdafx.h"
#include "Graph.h"

class PathGen {
public:
	PathGen(Graph& Graph) : graph(Graph) {};

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

	////Path generation helper funcs

	//Calculates each node's (shortest) distance to the destination node
	void calculateDistances();

	//Defines the rules for valid road candidates.
	bool isRoadCandidate(Node* node, float maxDist);

	//Recalculates the distance of a node
	void updateDistance(Node* node);
};