// GraphPathGenv1.2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "src/Graph.h"
#include "src/RectGDIrenderer.h"
#include <iostream>
#include <ctime>

#define COORD_TO_ID(x,y,a) (a)*(y)+(x)

void createSquare(int a, Graph& g){
	for (int i = 0; i < a*a; i++) {
		g.initNewNode(4, 4);
	}

	for (int x = 0; x < a - 1; x++) {
		for (int y = 0; y < a; y++) {
			g.addBidirEdge(COORD_TO_ID(x, y, a), COORD_TO_ID(x + 1, y, a), 1.0f);
		}
	}

	for (int x = 0; x < a; x++) {
		for (int y = 0; y < a - 1; y++) {
			g.addBidirEdge(COORD_TO_ID(x, y, a), COORD_TO_ID(x, y + 1, a), 1.0f);
		}
	}
}

void printDistances(int a, Graph& g) {
	for (int y = 0; y < a; y++) {
		for (int x = 0; x < a; x++) {
			cout << g.getDistance(COORD_TO_ID(x, y, a)) << ",";
		}
		cout << endl;
	}
}

#define SIZE 20
int main(int argc, char** argv) {
	Graph g(SIZE*SIZE);
	createSquare(SIZE,g);
	clock_t begin = clock();
	g.setDestID(0);
	vector<int> path;
	int iters = 1;
	for (int i = 0; i < iters; i++) {
		path = g.genRandomPath(210, SIZE);
		//g.calculateDistances();
	}
	clock_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC / iters * 1000 << " ms per iteration" << endl;
	//printDistances(SIZE, g);
	RectGDIrenderer r(SIZE, SIZE);
	r.createGrid();
	r.drawPath(path, Color::Yellow);
	r.addOverlay(g);
	r.saveImage(L"D:\\OUT.png");
	cin.ignore();
	return 0;
}
