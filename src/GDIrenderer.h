#pragma once
#include <objidl.h>
#include <gdiplus.h>

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
	
	Pen* penWhite;
	Brush* brushWhite;
	Font* font;

private:
	CLSID pngClsid;
	ULONG_PTR gdiplusToken;

	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};