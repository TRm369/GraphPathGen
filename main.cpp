// GraphPathGenv1.2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "src/PathGen.h"
#include "src/RectGDIrenderer.h"
#include <iostream>
#include "tests/GPGtester.h"
#include "src/Log.h"

#define COORD_TO_ID(x,y,a) (a)*(y)+(x)

void createSquare(int a, Graph& g) {
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

#define SIZE 200

Graph g(SIZE*SIZE);
RectGDIrenderer r(SIZE, SIZE);
wchar_t buffer[40];
int fileI = 0;

/*void onStep(vector<int> path) {
	r.createGrid();
	r.drawPath(path, Color::Yellow);
	r.addOverlay(g);
	swprintf_s(buffer,40, L"D:\\data\\GPG\\OUT%04d.png", fileI);
	r.saveImage(buffer);
	fileI++;
}*/

using namespace GPGtests;

int main(int argc, char** argv) {

	cout << g.continuousMemBlock() << endl;
	//Log::createLogFile("log.log", false);
	createSquare(SIZE,g);

	PathGen pg(g);
	pg.setDestID(0);
	
	//g.setOnStepCB(&onStep);
	vector<int> path;
	path = pg.genRandomPath(SIZE*SIZE-1, SIZE*SIZE/5);
	r.createGrid();
	r.drawPath(path, Color::Yellow);
	r.addOverlay(g);
	r.saveImage(L"D:\\OUT.png");

	//GPGtester::setVerboseLevel(VerboseLevel::progress, VerboseLevel::subtestSuccess, VerboseLevel::names);
	//GPGtester::setFileName("GPGtests.txt");
	//GPGtester::runTests();

	cin.ignore();
	return 0;
}
