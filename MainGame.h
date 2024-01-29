#pragma once

#include "CommonInclude.h"

class JoTexture;
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

	void Initialize(HWND _hwnd, UINT _width, UINT _height);
	void Update();
	void LateUpdate();
	void Render();

	HWND GetHwnd() const { return m_hwnd; }
	HDC GetMainDC() const { return m_dc; }
	const UINT& GetWidth() const { return m_width; }
	const UINT& GetHeight() const { return m_height; }

	void SetCursorRender(bool _b) { m_bCursorRender = _b; }
private:
	void adjustWindowRect();
	void render_cursor();

private:
	HWND	m_hwnd;
	HDC		m_dc;

	UINT	m_width;
	UINT	m_height;

	JoTexture* m_pCursorTex;
	bool m_bCursorRender = true;
};

