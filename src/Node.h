#pragma once

#include "../stdafx.h"

#define ROAD_EMPTY -1
#define ROAD_INVALID 0
#define REALLY_HIGH_NUMBER 1e20f

typedef uint16_t edgeCount_t;

/*
Incoming nodes aren't used. At this point I'm not sure if they're going to be needed, but when I implemented Node,
I decided to inculde them. I'll keep them until I decide if I need them.
*/

class Node {
public:
	Node(edgeCount_t inCount, edgeCount_t outCount);
	~Node();

	int ID;
	///<summary>
	///ID of the road on this node. Anything greater than ROAD_INVALID is a valid value
	///</summary>
	int roadID;
	uint8_t flags = 0;
	float distance = REALLY_HIGH_NUMBER;
	edgeCount_t incomingCount = 0;
	edgeCount_t outgoingCount = 0;
	Node** outgoing;
	float* outgoingWeight;
	Node** incoming;
	float* incomingWeight;
	void addIncoming(Node* other, float weight);
	void addOutgoing(Node* other, float weight);
};

