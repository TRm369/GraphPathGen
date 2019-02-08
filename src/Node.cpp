#include "Node.h"

Node::Node(uint16_t inCount, uint16_t outCount) {
	incoming = new Node*[inCount];
	incomingWeight = new float[inCount];
	outgoing = new Node*[outCount];
	outgoingWeight = new float[outCount];
	for (int i = 0; i < inCount; i++) {
		incoming[i] = nullptr;
		incomingWeight[i] = -1.0f;
	}
	for (int i = 0; i < outCount; i++) {
		outgoing[i] = nullptr;
		outgoingWeight[i] = -1.0f;
	}

	roadID = ROAD_EMPTY;
}

Node::~Node() {
	delete[] incoming;
	delete[] incomingWeight;
	delete[] outgoing;
	delete[] outgoingWeight;
}

//On adding the edges to nodes, they should check for overflows.
//But I'm not sure if I want to spend the extra 2*2 bytes per node to keep the max count :D
//Is this dumb? Well, it's dangerous af, but I save 4 bytes! That's 4 MB for the target 1M nodes!
//So probably yes, it's super dumb.

void Node::addIncoming(Node* other, float weight) {
	incoming[incomingCount] = other;
	incomingWeight[incomingCount] = weight;
	incomingCount++;
}

void Node::addOutgoing(Node* other, float weight) {
	outgoing[outgoingCount] = other;
	outgoingWeight[outgoingCount] = weight;
	outgoingCount++;
}
