#pragma once
#include "GDIrenderer.h"

#define SQR_SIZE 40

class SquareGDIrenderer : public GDIrenderer {
public:
	SquareGDIrenderer(int w, int h);
	void createGrid();
	void addOverlay(Graph& graph);
	//void drawPath(vector<int>& path, Color color);

protected:
	int w;
	int h;
};