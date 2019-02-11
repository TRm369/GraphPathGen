#pragma once

#include "../stdafx.h"

#define ROAD_EMPTY -1
#define REALLY_HIGH_NUMBER 1e20f

class Node {
public:
	Node(uint16_t inCount, uint16_t outCount);
	~Node();

	int ID;
	int roadID;
	uint8_t flags = 0;
	float distance = REALLY_HIGH_NUMBER;
	uint16_t incomingCount = 0;
	uint16_t outgoingCount = 0;
	Node** outgoing;
	float* outgoingWeight;
	Node** incoming;
	float* incomingWeight;
	void addIncoming(Node* other, float weight);
	void addOutgoing(Node* other, float weight);
};

