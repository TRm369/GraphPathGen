#include "Graph.h"

Graph::Graph(int NodeCount) {
	nodes = new Node*[NodeCount];
	nodeCount = NodeCount;
	initdNodes = 0;
}

Graph::~Graph() {
	for (int i = 0; i < initdNodes; i++) {
		delete nodes[i];
	}
	delete[] nodes;
}

int Graph::initNewNode(edgeCount_t edgeInMaxCount, edgeCount_t edgeOutMaxCount) {
	if (initdNodes == nodeCount)
		return -1;

	nodes[initdNodes] = new Node(edgeInMaxCount, edgeOutMaxCount);
	nodes[initdNodes]->ID = initdNodes;
	if (_maxOutEdges < edgeOutMaxCount)
		_maxOutEdges = edgeOutMaxCount;
	return initdNodes++;
}

bool Graph::addEdge(int IDsrc, int IDdest, float weight) {
	if (IDsrc >= initdNodes || IDdest >= initdNodes || weight <= 0.0f || IDsrc == IDdest)
		return false;

	nodes[IDsrc]->addOutgoing(nodes[IDdest], weight);
	nodes[IDdest]->addIncoming(nodes[IDsrc], weight);

	//On adding the edges to nodes, they should (internally) check for overflows.
	//See Node.cpp for details.
	return true;
}

bool Graph::addBidirEdge(int ID1, int ID2, float weight) {
	if (ID1 >= initdNodes || ID2 >= initdNodes || weight <= 0.0f || ID1 == ID2)
		return false;

	//One way
	nodes[ID1]->addOutgoing(nodes[ID2], weight);
	nodes[ID2]->addIncoming(nodes[ID1], weight);
	//The other way
	nodes[ID2]->addOutgoing(nodes[ID1], weight);
	nodes[ID1]->addIncoming(nodes[ID2], weight);

	//On adding the edges to nodes, they should (internally) check for overflows.
	//See Node.cpp for details.
	return true;
}

float Graph::getDistance(int nodeID) {
	if (nodeID >= initdNodes)
		return -1.0f;

	if (nodes[nodeID]->flags & FLAG_DIST_INVALID)
		return -2.0f;

	return nodes[nodeID]->distance;
}

int Graph::maxOutEdges() {
	return _maxOutEdges;
}

void Graph::resetGraph() {
	for (int i = 0; i < initdNodes; i++) {
		nodes[i]->distance = REALLY_HIGH_NUMBER;
		nodes[i]->roadID = ROAD_EMPTY;
		nodes[i]->assignedOnIter = 0;
		nodes[i]->assignedOnIter -= 1; //Overflow to the max val
		nodes[i]->flags = 0;
	}
}

void Graph::resetDistances() {
	for (int i = 0; i < initdNodes; i++) {
		nodes[i]->distance = REALLY_HIGH_NUMBER;
	}
}

void Graph::invalidateNodes(float distThres) {
	for (int i = 0; i < initdNodes; i++) {
		if (nodes[i]->distance >= distThres) {
			nodes[i]->flags |= FLAG_DIST_INVALID;
		}
	}
}

void Graph::setFlags(flags_t mask) {
	for (int i = 0; i < initdNodes; i++) {
		nodes[i]->flags |= mask;
	}
}

void Graph::clearFlags(flags_t mask) {
	flags_t invMask = ~mask;
	for (int i = 0; i < initdNodes; i++) {
		nodes[i]->flags &= invMask;
	}
}

int Graph::size() {
	return initdNodes;
}

int Graph::maxSize() {
	return nodeCount;
}

Node* Graph::operator[](int index) {
	return nodes[index];
}
