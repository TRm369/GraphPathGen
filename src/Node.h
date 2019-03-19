#pragma once
#include "GPGsettings.h"

//Logic assumes ROAD_INVALID > ROAD_EMPTY
#define ROAD_EMPTY -1
#define ROAD_INVALID 0

//Type used for flags, unsigned integer type
typedef uint8_t flags_t;

/*Flags bit table
BIT | DESCRIPTION
0   | Queued (Distance calculation)
1   | Distance invalidated
2   |
3   |
4   |
5   |
6   |
7   |
*/
#define FLAG_QUEUED (flags_t)1
#define FLAG_DIST_INVALID (flags_t)2
//#define FLAG_BIT_2 4
//#define FLAG_BIT_3 8
//#define FLAG_BIT_4 16
//#define FLAG_BIT_5 32
//#define FLAG_BIT_6 64
//#define FLAG_BIT_7 128

class Node {
public:
	Node(edgeCount_t inCount, edgeCount_t outCount);
	//Can be used to initialize default values instead of constructor. TODO: Doesn't seem too elegant. Change (override new?)
	void init(edgeCount_t inCount, edgeCount_t outCount);
	~Node();

	ID_t ID;
	//ID of the road on this node. Anything greater than ROAD_INVALID is a valid value
	roadID_t roadID;
	//Iteration on which the roadID was assigned. Used to undo steps.
	iterCounter_t assignedOnIter;
	//Flags
	flags_t flags = 0;

	float distance = REALLY_HIGH_NUMBER;
	edgeCount_t incomingCount = 0;
	edgeCount_t outgoingCount = 0;
	Node** outgoing;
	float* outgoingWeight;
	Node** incoming;
	float* incomingWeight;
	void addIncoming(Node* other, float weight);
	void addOutgoing(Node* other, float weight);
	void setRoadID(roadID_t id, iterCounter_t iter);
	void resetRoadID();
}; 