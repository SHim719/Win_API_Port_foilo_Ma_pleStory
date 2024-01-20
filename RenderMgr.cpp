#include "RenderMgr.h"
#include "MainGame.h"
#include "JoTexture.h"

extern MainGame g_MainGame;

ID2D1Factory* RenderMgr::m_pFactory = nullptr;
ID2D1HwndRenderTarget* RenderMgr::m_pRenderTarget = nullptr;
IDWriteFactory* RenderMgr::m_pWriteFactory = nullptr;
IWICImagingFactory* RenderMgr::m_pImageFactory = nullptr;
ID2D1Bitmap* RenderMgr::m_pBitmap = nullptr;
ID2D1SolidColorBrush* RenderMgr::m_pBrush = nullptr;
IDWriteTextFormat* RenderMgr::m_pTextFormat = nullptr;

void RenderMgr::Initialize()
{
	HWND hWnd = g_MainGame.GetHwnd();

	RECT rc;
	GetClientRect(hWnd, &rc);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	m_pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, SizeU(rc.right, rc.bottom),
			D2D1_PRESENT_OPTIONS::D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget);

	if (S_OK == CoInitialize(nullptr))
	{

	}
	if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)))
	{

	}
	if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)))
	{

	}

	// 텍스트 포맷 생성
	m_pWriteFactory->CreateTextFormat(
		L"굴림",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"ko",
		&m_pTextFormat);
	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// 브러쉬 생성
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pBrush);
}

void RenderMgr::RenderImage(JoTexture* tex, float dstX, float dstY, float dstW, float dstH, float alpha)
{
	assert(tex);
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };

	m_pRenderTarget->DrawBitmap(tex->GetImage(), imgRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
}

void RenderMgr::RenderFrame(JoTexture* tex, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float alpha)
{
	assert(tex);
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	m_pRenderTarget->DrawBitmap(tex->GetImage(), imgRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
}

void RenderMgr::RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize, COLORREF color)
{
	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	if (m_pTextFormat->GetFontSize() != fontSize)
	{
		m_pTextFormat->Release();
		m_pWriteFactory->CreateTextFormat(
			L"HYGothic 중간",
			NULL,
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"ko",
			&m_pTextFormat);
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT)str.size(), m_pTextFormat,
		D2D1::RectF(dstX, dstY, dstW, dstH), m_pBrush);
}

void RenderMgr::RenderText(wstring str, const WCHAR* font, float dstX, float dstY, float dstW, float dstH, float fontSize, COLORREF color)
{
	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	if (m_pTextFormat->GetFontSize() != fontSize)
	{
		m_pTextFormat->Release();
		m_pWriteFactory->CreateTextFormat(
			font,
			NULL,
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"ko",
			&m_pTextFormat);
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT)str.size(), m_pTextFormat,
		D2D1::RectF(dstX, dstY, dstW, dstH), m_pBrush);
}

void RenderMgr::RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawRectangle(m_imgRect, m_pBrush, strokeWidth);
}

void RenderMgr::RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color, float alpha)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, alpha));
	m_pRenderTarget->FillRectangle(m_imgRect, m_pBrush);
}

void RenderMgr::RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawEllipse(m_imgRect, m_pBrush, strokeWidth);
}

void RenderMgr::RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->FillEllipse(m_imgRect, m_pBrush);
}

void RenderMgr::RenderLine(Vec2 startPoint, Vec2 endPoint, COLORREF color, float strokeWidth)
{
	D2D1_POINT_2F start = { startPoint.x, startPoint.y };
	D2D1_POINT_2F end = { endPoint.x, endPoint.y };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawLine(start, end, m_pBrush, strokeWidth);
}

