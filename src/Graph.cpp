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

int Graph::initNewNode(uint16_t edgeInMaxCount, uint16_t edgeOutMaxCount) {
	if (initdNodes == nodeCount)
		return -1;

	nodes[initdNodes] = new Node(edgeInMaxCount, edgeOutMaxCount);
	nodes[initdNodes]->ID = initdNodes;
	if (maxOutEdges < edgeOutMaxCount)
		maxOutEdges = edgeOutMaxCount;
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

void Graph::calculateDistances() {
	if (destID == -1)
		return;

	nodes[destID]->distance = 0.0f;
	CircQueue<Node*> toExpand(nodeCount);
	toExpand.push(nodes[destID]);

	Node* currNode;
	while (toExpand.size() > 0) {
		currNode = toExpand.pop();
		currNode->flags = (uint8_t)0;

		for (int i = 0; i < currNode->outgoingCount; i++) {
			Node* other = currNode->outgoing[i];
			if (other->roadID == ROAD_INVALID) {
				//NOTE: Debating whether to just skip it or set it to REALLY_HIGH_NUMBER
				continue;
			}
			float temp = currNode->distance + currNode->outgoingWeight[i];
			if (other->distance > temp) {
				other->distance = temp;
				if (other->flags == (uint8_t)0) {
					toExpand.push(currNode->outgoing[i]);
					(other)->flags = (uint8_t)1;
				}
			}
		}
	}
}

float Graph::getDistance(int nodeID) {
	if (nodeID >= initdNodes)
		return -1.0f;

	return nodes[nodeID]->distance;
}

bool Graph::isRoadCandidate(Node* node, float maxDist) {
	/*
	Roads can't form loops. This is handled in the path gen algorithim itself,
	invalidaing all neighboring nodes when leaving a node.
	*/
	
	//Invalid or already assigned roads aren't valid
	if (node->roadID >= ROAD_INVALID)
		return false;

	//Don't exceed the max length
	if (node->distance > maxDist)
		return false;

	return true;
}

void Graph::resetDistances() {
	for (int i = 0; i < initdNodes; i++) {
		nodes[i]->distance = REALLY_HIGH_NUMBER;
	}
}

vector<int> Graph::genRandomPath(int startID, float maxLength) {
	if (startID < 0 || startID >= initdNodes)
		return vector<int>();
	int roadID = 1;

	//Seed the RNG
	srand(time(NULL));

	//Path variables
	vector<int> path{startID};
	Node* currNode = nodes[startID];
	float lengthLeft = maxLength;

	//Valid nodes
	Node** validNodes = new Node*[maxOutEdges];
	int validNodesCount = 0;

	calculateDistances();

	currNode->roadID = roadID;
	while (currNode->ID != destID) {
		//Check neighbors for valid road candidates
		validNodesCount = 0;
		for (int i = 0; i < currNode->outgoingCount; i++) {
			if (currNode->outgoing[i] == nullptr)
				break;
			if (isRoadCandidate(currNode->outgoing[i], lengthLeft-currNode->outgoingWeight[i]))
				validNodes[validNodesCount++] = currNode->outgoing[i];
		}

		//Handle dead ends
		if (validNodesCount == 0) {
			if (currNode->ID == startID) {
				//Path doesn't exist
				return vector<int>();
			} else {
				//TODO: backtracking
				return path;
			}
		}

		//Invalidate all nodes around current Node, our choosen candidate will override this
		for (int i = 0; i < currNode->outgoingCount; i++) {
			if (currNode->outgoing[i] == nullptr)
				break;
			currNode->outgoing[i]->roadID = ROAD_INVALID;
		}

		////Pick one valid candidate at random and make a step
		//Pick at random
		int next = rand() % validNodesCount;
		//Subtract the distance from length left
		for (int i = 0; i < currNode->outgoingCount; i++) {
			if (currNode->outgoing[i] == validNodes[next]) {
				lengthLeft -= currNode->outgoingWeight[i];
			}
		}
		//Make a step
		currNode = validNodes[next];
		currNode->roadID = roadID;
		path.push_back(currNode->ID);

		//Recalculate the distances
		resetDistances();
		calculateDistances();
	}

	return path;
}

bool Graph::setDestID(int ID) {
	if (ID < 0 || ID >= initdNodes)
		return false;

	destID = ID;
	return true;
}

int Graph::getDestID() {
	return destID;
}
