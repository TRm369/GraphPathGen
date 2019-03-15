#pragma once
#include "GDIrenderer.h"
#include "Graph.h"

//Size of the square representing each node
//TODO: Not hardcode
#define SQR_SIZE 40

class RectGDIrenderer : public GDIrenderer {
public:
	RectGDIrenderer(int w, int h);
	void createGrid();
	void addOverlay(Graph& graph);
	void drawPath(vector<int>& path, Color color);

protected:
	int w;
	int h;
};