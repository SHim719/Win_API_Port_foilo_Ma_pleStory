#include "JoTexture.h"
#include "MainGame.h"
#include "RenderMgr.h"

JoTexture::JoTexture()
	: JoResource(eResourceType::Texture)
	, m_height(0)
	, m_width(0)
	, m_pBitmap(nullptr)
{
}

JoTexture::~JoTexture()
{
	m_pBitmap->Release();
}

HRESULT JoTexture::Load(const wstring& path)
{
	IWICBitmapDecoder* p_decoder;		// 압축된 이미지를 해제할 객체
	IWICBitmapFrameDecode* p_frame;		// 특정 그림을 선택한 객체
	IWICFormatConverter* p_converter;	// 이미지 변환 객체

	// WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
	if (S_OK != RenderMgr::GetImageFactory()->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
	if (S_OK != RenderMgr::GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
	ID2D1Bitmap* bitmap = RenderMgr::GetBitmap();
	if (S_OK != RenderMgr::GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// 성공적으로 생성한 경우
	m_pBitmap = bitmap;

	m_width = UINT(m_pBitmap->GetSize().width);
	m_height = UINT(m_pBitmap->GetSize().height);

	p_converter->Release();		// 이미지 변환 객체 제거
	p_frame->Release();			// 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
	p_decoder->Release();		// 압축을 해제하기 위해 생성한 객체 제거

	return S_OK;
}

