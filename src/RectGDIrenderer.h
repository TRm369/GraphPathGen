#pragma once
#include "GDIrenderer.h"

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