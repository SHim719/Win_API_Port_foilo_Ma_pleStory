#pragma once

#include "JoResource.h"

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

class JoTexture : public JoResource
{
public:
	JoTexture();
	~JoTexture();

	HRESULT			Load(const wstring& path) override;

	UINT			GetWidth() const { return m_width; }
	UINT			GetHeight() const { return m_height; }
	ID2D1Bitmap* GetImage() const { return m_pBitmap; }
private:
	ID2D1Bitmap* m_pBitmap;

	UINT m_width;
	UINT m_height;

};

