#include "PathGen.h"
#include "CircQueue.h"
#include "FILOcontainer.h"
#include "Log.h"
#include <ctime> //seed for rng

void PathGen::calculateDistances() {
	if (destID == -1)
		return;

	graph[destID]->distance = 0.0f;
	CircQueue<Node*> toExpand(graph.capacity());
	toExpand.push(graph[destID]);

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
				if ((other->flags & FLAG_QUEUED) == (uint8_t)0) {
					toExpand.push(currNode->outgoing[i]);
					(other)->flags |= (uint8_t)FLAG_QUEUED;
				}
			}
		}
	}
}

bool PathGen::isRoadCandidate(Node* node, float maxDist) {
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

/* updateDistance
Recalculates the distance of a node to the destination node.
Basically an A* with a few tweeks:
Branch ends with any node with valid distance which is then added to the distance of the nodes in the branch
Node objects themselves are used to store some of the information regarding search progress (like whether the node has been qequed)
*/
void PathGen::updateDistance(Node* node) {
	//Reset node flags
	graph.clearFlags(FLAG_QUEUED);

	//List of nodes to expand and their distances to the node whose distance is being calculated
	FILOcontainer<pair<Node*, float>> toExpand(graph.size());
	toExpand.push_back(pair<Node*, float>(node, 0.0f));
	node->flags |= FLAG_QUEUED;

	float bestPathLength = REALLY_HIGH_NUMBER;
	FILOcontainer<pair<Node*, float>> bestPath(graph.size()); //TODO: Mem optimalization?

	float lowestHeuristic = REALLY_HIGH_NUMBER;
	int lowestHeuristicIndex = -1;

	while (toExpand.size() > 0) {
		pair<Node*, float> current = toExpand.back();

		//If this node has valid distance, end this branch of DFS
		if ((current.first->flags & FLAG_DIST_INVALID) == false) {
			if (current.second + current.first->distance < bestPathLength) {
				bestPathLength = current.second + current.first->distance;
				bestPath.copyFrom(toExpand);
				continue;
			}
		}

		//Find neighbor with lowest heuristic
		lowestHeuristicIndex = -1;
		for (int i = 0; i < current.first->outgoingCount; i++) {
			if (current.first->outgoing[i] == nullptr)
				break;

			//Here we also disallow going through already placed roads
			if (((current.first->outgoing[i]->flags & FLAG_QUEUED) == 0) && current.first->outgoing[i]->roadID == ROAD_EMPTY) {
				if (current.first->outgoing[i]->distance < lowestHeuristic) {
					lowestHeuristic = current.first->outgoing[i]->distance;
					lowestHeuristicIndex = i;
				}
			}
		}

		//Remove this node from the toExpand list if there's nowhere to go from here
		if (lowestHeuristicIndex == -1) {
			toExpand.pop_back();
			continue;
		}

		//If the neighbor's heuristic (lower or equal to the actual distance) + distance to it is greater than the best path's,
		//it is unnecessary to expand it. All other neighbors will also have this sum greater, so this node isn't in a better path.
		if (current.first->outgoing[lowestHeuristicIndex]->distance + current.first->outgoingWeight[lowestHeuristicIndex] + current.second > bestPathLength) {
			toExpand.pop_back();
			continue;
		}

		//Expand the neighbor
		toExpand.push_back(pair<Node*, float>(current.first->outgoing[lowestHeuristicIndex], current.second + current.first->outgoingWeight[lowestHeuristicIndex]));
		current.first->outgoing[lowestHeuristicIndex]->flags |= FLAG_QUEUED;
	}

	// Update the distances along the best path
	for (int i = 0; i < bestPath.size(); i++) {
		bestPath[i].first->distance = bestPathLength - bestPath[i].second;
		bestPath[i].first->flags &= ~FLAG_DIST_INVALID;
	}
}

vector<int> PathGen::genRandomPath(int startID, float maxLength) {
	if (startID < 0 || startID >= graph.size())
		return vector<int>();
	int roadID = 1;

	//Seed the RNG
	srand(time(NULL));

	//Path variables
	vector<int> path{ startID };
	Node* currNode = graph[startID];
	float lengthLeft = maxLength;

	//Valid nodes
	Node** validNodes = new Node*[graph.maxOutEdges()];
	int validNodesCount = 0;

	calculateDistances();

	//Setup and gen loop
	iterCounter_t iterCounter = 0;
	currNode->setRoadID(roadID, iterCounter);
	while (currNode->ID != destID) {
		//Check neighbors for valid road candidates
		validNodesCount = 0;
		for (int i = 0; i < currNode->outgoingCount; i++) {
			if (currNode->outgoing[i] == nullptr)
				break;
			if (currNode->outgoing[i]->flags & FLAG_DIST_INVALID) {
				updateDistance(currNode->outgoing[i]);
			}
			if (isRoadCandidate(currNode->outgoing[i], lengthLeft - currNode->outgoingWeight[i]))
				validNodes[validNodesCount++] = currNode->outgoing[i];
		}

		//Call onStep
		//It is called here to first let distances of neighboring nodes be recalculated
		if (onStep != nullptr) {
			//passing a copy of path, so that it can't be modified
			onStep(path);
		}

		//Handle dead ends
		if (validNodesCount == 0) {
			if (currNode->ID == startID) {
				//Path doesn't exist
				return vector<int>();
			} else {
				////Backtrack
				//Stepback
				Node* badNode = graph[path.back()];
				path.pop_back();
				currNode = graph[path.back()];
				iterCounter--;

				//Revalidate the nodes around the last node (only the ones which were invalidated last step)
				for (int i = 0; i < currNode->outgoingCount; i++) {
					if (currNode->outgoing[i] == nullptr)
						break;
					if (currNode->outgoing[i]->assignedOnIter == iterCounter) {
						currNode->outgoing[i]->resetRoadID();
					}
				}

				//Invalidate the node from which we're backtracking (because it doesn't lead to any valid path)
				//Using iterCounter-1 to allow further backtracking
				badNode->setRoadID(ROAD_INVALID, iterCounter - 1);

				//TODO: OPTIMIZE HERE
				//Recalculate the distances
				graph.resetDistances();
				calculateDistances();

				//Rinse and repeat
				continue;
			}
		}

		//Invalidate all nodes around current Node, our choosen candidate will override this
		for (int i = 0; i < currNode->outgoingCount; i++) {
			if (currNode->outgoing[i] == nullptr)
				break;
			currNode->outgoing[i]->setRoadID(ROAD_INVALID, iterCounter);
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
		//assignedOnIter was set during the invalidation, no need to do it again so directly setting roadID
		currNode->roadID = roadID;
		path.push_back(currNode->ID);

		graph.invalidateNodes(currNode->distance);

		iterCounter++;
	}

	delete[] validNodes;

	return path;
}

void PathGen::setOnStepCB(void(*CB)(vector<int>)) {
	onStep = CB;
}

bool PathGen::setDestID(int ID) {
	if (ID < 0 || ID >= graph.size())
		return false;

	destID = ID;
	return true;
}

int PathGen::getDestID() {
	return destID;
}
