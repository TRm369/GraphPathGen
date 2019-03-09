#pragma once
#include "../stdafx.h"

/*Type definitions for Node
Changing these types can affect memory usage as the nodes make the majority of memory usage
especially when there are many of them (100k+). Tune them to fit your requirements.
*/

//Unsigned types
typedef uint16_t edgeCount_t;
typedef uint16_t iterCounter_t;
typedef uint16_t ID_t;
//Signed types
typedef int16_t roadID_t;

//Must be set to a number greater than the longest possible distance in the graph.
#define REALLY_HIGH_NUMBER 1e20f

//DON'T TOUCH! Logic assumes ROAD_INVALID > ROAD_EMPTY
#define ROAD_EMPTY -1
#define ROAD_INVALID 0

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
#define FLAG_QUEUED (uint8_t)1
#define FLAG_DIST_INVALID (uint8_t)2
//#define FLAG_BIT_2 4
//#define FLAG_BIT_3 8
//#define FLAG_BIT_4 16
//#define FLAG_BIT_5 32
//#define FLAG_BIT_6 64
//#define FLAG_BIT_7 128

class Node {
public:
	Node(edgeCount_t inCount, edgeCount_t outCount);
	~Node();

	ID_t ID;
	//ID of the road on this node. Anything greater than ROAD_INVALID is a valid value
	roadID_t roadID;
	//Iteration on which the roadID was assigned. Used to undo steps.
	iterCounter_t assignedOnIter;
	//Flags
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
	void setRoadID(roadID_t id, iterCounter_t iter);
	void resetRoadID();
};