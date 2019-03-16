#pragma once
#include "../stdafx.h"
#include "Graph.h"

class PathGen {
public:
	PathGen(Graph& Graph) : graph(Graph) {};

	///<summary>
	///Sets the destination node - node at which the generated path should end.
	///</summary>
	bool setDestID(int ID);
	int getDestID();

	///<summary>
	///Returns a randomly generated path from a given node to destination node.
	///</summary>
	///<remarks>
	///Returns a vector. First element is the starting node, last is the destination node.
	///</remarks>
	vector<int> genRandomPath(int startID, float maxLength);

	void setOnStepCB(void(*CB)(vector<int>));

private:
	Graph& graph;

	int destID = -1;

	void(*onStep)(vector<int>);

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