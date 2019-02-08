#include "Graph.h"

Graph::Graph(int NodeCount) {
	nodes = new Node*[NodeCount];
	nodeCount = NodeCount;
	initdNodes = 0;
}


Graph::~Graph() {
	delete[] nodes;
}

int Graph::initNewNode(uint16_t edgeInMaxCount, uint16_t edgeOutMaxCount) {
	if (initdNodes == nodeCount)
		return -1;

	nodes[initdNodes] = new Node(edgeInMaxCount, edgeOutMaxCount);
	return initdNodes++;
}

bool Graph::addEdge(int IDsrc, int IDdest, float weight) {
	if (IDsrc >= initdNodes || IDdest >= initdNodes || weight < 0.0f)
		return false;

	nodes[IDsrc]->addOutgoing(nodes[IDdest], weight);
	nodes[IDdest]->addIncoming(nodes[IDsrc], weight);

	//On adding the edges to nodes, they should (internally) check for overflows.
	//See Node.cpp for details.
	return true;
}

bool Graph::addBidirEdge(int ID1, int ID2, float weight) {
	if (ID1 >= initdNodes || ID2 >= initdNodes || weight < 0.0f)
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

void Graph::calculateDistances(int destID) {
	nodes[destID]->distance = 0.0f;
	queue<Node*> toExpand;
	toExpand.push(nodes[destID]);

	Node* currNode;
	Node** loopEnd;
	Node** outPtr;
	float* outWeight;
	while (!toExpand.empty()) {
		currNode = toExpand.front();
		toExpand.pop();
		currNode->flags = 0;


		//for (int i = 0; i < currNode->outgoingCount; i++) {
		outPtr = currNode->outgoing;
		outWeight = currNode->outgoingWeight;
		loopEnd = outPtr + currNode->outgoingCount;
		while (outPtr < loopEnd) {
			if ((*outPtr)->distance > currNode->distance + *outWeight) {
				(*outPtr)->distance = currNode->distance + *outWeight;
				if ((*outPtr)->flags == 0) {
					toExpand.push(*outPtr);
					(*outPtr)->flags = 1;
				}
			}
			//cout << (*outPtr)->ID<<endl;
			outPtr++;
			outWeight++;
		}
	}
}

float Graph::getDistance(int nodeID) {
	if (nodeID >= initdNodes)
		return -1.0f;

	return nodes[nodeID]->distance;
}
