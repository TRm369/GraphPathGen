#include "GDIrenderer.h"

GDIrenderer::GDIrenderer() {
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	GetEncoderClsid(L"image/png", &pngClsid);
	penWhite = new Pen(Color::White);
	brushWhite = new SolidBrush(Color::White);
	font = new Font(L"Dontcare", 10);
}

GDIrenderer::~GDIrenderer() {
	delete g;
	delete bmp;
	delete penWhite;
	delete brushWhite;
	delete font;

	GdiplusShutdown(gdiplusToken);
}

void GDIrenderer::saveImage(const WCHAR* file) {
	bmp->Save(file, &pngClsid);
}

//https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-retrieving-the-class-identifier-for-an-encoder-use
int GDIrenderer::GetEncoderClsid(const WCHAR * format, CLSID * pClsid) {
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}
