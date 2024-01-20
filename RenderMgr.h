#pragma once
#include "CommonInclude.h"

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

using namespace D2D1;

class JoTexture;

class RenderMgr
{
public:
	static void Initialize();
	static void RenderImage(JoTexture* tex, float dstX, float dstY, float dstW, float dstH, float alpha = 1.f);
	static void RenderFrame(JoTexture* tex, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH, float alpha = 1.f);

	static void RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize = 12.f, COLORREF color = RGB(0, 0, 0));
	static void RenderText(wstring str, const WCHAR* font, float dstX, float dstY, float dstW, float dstH, float fontSize = 12.f, COLORREF color = RGB(0, 0, 0));
	static void RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f);
	static void RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float alpha = 1.f);
	static void RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f);
	static void RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));
	static void RenderLine(Vec2 startPoint, Vec2 endPoint, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f);

	static ID2D1Bitmap* GetBitmap() { return m_pBitmap; }
	static ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	static IWICImagingFactory* GetImageFactory() { return m_pImageFactory; }
	static IDWriteFactory* GetWriteFactory() { return m_pWriteFactory; }

private:
	static ID2D1Factory* m_pFactory;
	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static IDWriteFactory* m_pWriteFactory;
	static IWICImagingFactory* m_pImageFactory;
	static ID2D1Bitmap* m_pBitmap;
	static ID2D1SolidColorBrush* m_pBrush;
	static IDWriteTextFormat* m_pTextFormat;

};



