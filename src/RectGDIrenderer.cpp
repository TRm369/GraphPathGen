#include "RectGDIrenderer.h"
#include <string>

#define FILL_TILE(t, c) g->FillRectangle(&SolidBrush(c), Rect((t % w)*SQR_SIZE + 1, (t / w)*SQR_SIZE + 1, SQR_SIZE - 1, SQR_SIZE - 1))

RectGDIrenderer::RectGDIrenderer(int W, int H) : GDIrenderer() {
	w = W;
	h = H;
}

void RectGDIrenderer::createGrid() {
	bmp = new Bitmap(w*SQR_SIZE + 1, h*SQR_SIZE + 1, PixelFormat24bppRGB);
	g = Graphics::FromImage(bmp);

	//Draw grid
	g->Clear(Color::Black);
	for (int x = 0; x <= w; x++) {
		g->DrawLine(penWhite, Point(x*SQR_SIZE, 0), Point(x*SQR_SIZE, h*SQR_SIZE + 1));
	}
	for (int y = 0; y <= h; y++) {
		g->DrawLine(penWhite, Point(0, y*SQR_SIZE), Point(w*SQR_SIZE + 1, y*SQR_SIZE));
	}
}

void RectGDIrenderer::addOverlay(Graph& graph) {
	//Draw destination
	FILL_TILE(graph.getDestID(), Color::DarkRed);

	//Draw distances
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			g->DrawString(to_wstring(graph.getDistance(y*w + x)).c_str(), 4, font, PointF(x*SQR_SIZE + 5, y*SQR_SIZE + 10), brushWhite);
			//g->DrawString(to_wstring(graph.getNodeRoadID(y*w + x)).c_str(), -1, font, PointF(x*SQR_SIZE + 5, y*SQR_SIZE + 10), brushWhite);
		}
	}
}

void RectGDIrenderer::drawPath(vector<int>& path, Color color) {
	for (int tile : path) {
		FILL_TILE(tile, color);
	}
}
