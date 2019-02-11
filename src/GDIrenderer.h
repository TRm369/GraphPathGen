#pragma once
#include <objidl.h>
#include <gdiplus.h>
#include "Graph.h"

#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

class GDIrenderer {
public:
	GDIrenderer();
	~GDIrenderer();

	void saveImage(const WCHAR* file);
protected:
	Bitmap* bmp;
	Graphics* g;

	ULONG_PTR gdiplusToken;
	CLSID pngClsid;
	Pen* penWhite;
	Brush* brushWhite;
	Font* font;

	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};