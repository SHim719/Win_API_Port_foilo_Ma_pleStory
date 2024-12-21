#pragma once
#include "JoResource.h"


class JoBmp :
    public JoResource
{

public:
	JoBmp();
	~JoBmp();

	HRESULT			Load(const wstring& path) override;

	UINT			GetWidth() const { return m_width; }
	UINT			GetHeight() const { return m_height; }
	HDC Get_BmpDC() const { return m_BmpDC; }
private:
	HDC m_BmpDC;
	HBITMAP m_hBitmap;

	UINT m_width;
	UINT m_height;
};

