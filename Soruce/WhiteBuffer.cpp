#include "WhiteBuffer.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "TimeMgr.h"
#include "joObject.h"

void WhiteBuffer::Initialize()
{
	m_pWhiteBuffer = ResourceMgr::Find<JoTexture>(L"WhiteBuffer");
}

void WhiteBuffer::Update()
{
	m_fAlpha += m_fSpeed * TimeMgr::DeltaTime_NoScale();
	m_fAlpha = clamp(m_fAlpha, 0.f, 1.f);

	if (m_bNoDestroy)
		return;

	if (m_fAlpha <= 0.f || m_fAlpha >= 1.f)
		Destroy(this);
}

void WhiteBuffer::Render()
{
	RenderMgr::RenderImage(m_pWhiteBuffer, 0.f, 0.f, 1024.f, 768.f, m_fAlpha);
}

void WhiteBuffer::Set_Fade(float _fInitAlpha, float _fSpeed, bool _bIncrease, bool _bNoDestroy)
{
	m_fAlpha = _fInitAlpha;
	m_fSpeed = _fSpeed;
	if (!_bIncrease)
		m_fSpeed = -m_fSpeed;
	m_bNoDestroy = _bNoDestroy;
}
