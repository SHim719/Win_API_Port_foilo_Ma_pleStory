#include "JoBmp.h"
#include "MainGame.h"

extern MainGame g_MainGame;

JoBmp::JoBmp()
	: JoResource(eResourceType::Texture)
	, m_height(0)
	, m_width(0)
	, m_BmpDC(nullptr)
	, m_hBitmap(nullptr)
{
}

JoBmp::~JoBmp()
{
}

HRESULT JoBmp::Load(const wstring& path)
{
	HDC	hDC = g_MainGame.GetMainDC();

	// CreateCompatibleDC : 현재 화면 dc와 호환되는 dc를 생성

	m_BmpDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_MainGame.GetHwnd(), hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			// 프로그램 인스턴스 핸들(우리는 파일로부터 읽어오기 때문에 NULL값을 전달)
		path.c_str(),		// 파일의 경로
		IMAGE_BITMAP,	// 어떤 타입을 읽어올지 전달(비트맵 , 커서, 아이콘 등등)
		0,				// 가로, 세로 사이즈
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일로부터 이미지를 불러오겠음 LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

	// SelectObject : gdi 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	auto oldBitmap = (HBITMAP)SelectObject(m_BmpDC, m_hBitmap);

	DeleteObject(oldBitmap);
	return S_OK;
}
