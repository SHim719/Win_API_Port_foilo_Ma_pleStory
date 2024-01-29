#include "Animation.h"
#include "RenderMgr.h"
#include "TimeMgr.h"
#include "GameObject.h"
#include "Animator.h"
#include "Camera.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_SheetVec{}
	, m_iIndex(0)
	, m_fTime(0.f)
	, m_bEnd(false)
	, m_bNoTimeScale(false)
{
}

Animation::~Animation()
{
}


void Animation::Update()
{
	if (m_bEnd)
		return;
	
	if (m_bNoTimeScale)
		m_fTime += TimeMgr::DeltaTime_NoScale();
	else
		m_fTime += TimeMgr::DeltaTime();
		
		

	if (m_SheetVec[m_iIndex].duration <= m_fTime)
	{
		m_fTime = 0.0f;
		if (m_iIndex < m_SheetVec.size() - 1)
			m_iIndex++;
		else
			m_bEnd = true;

	}
}

void Animation::Render()
{
	if (m_bEnd) return;

	Sprite sprite = m_SheetVec[m_iIndex];

	GameObject* obj = m_pAnimator->GetOwner();
	Vec2 pos = obj->GetPos();

	pos = Camera::CalcRenderPos(pos);
	pos += sprite.offset;

	RenderMgr::RenderFrame(sprite.texture,
		pos.x - sprite.size.x * 0.5f, pos.y - sprite.size.y * 0.5f,
		pos.x + sprite.size.x * 0.5f, pos.y + sprite.size.y * 0.5f,
		sprite.leftTop.x, sprite.leftTop.y,
		sprite.leftTop.x + sprite.size.x, sprite.leftTop.y + sprite.size.y, m_fAlpha);
}

void Animation::Release()
{
}


void Animation::CreateAnimation(const wstring& name, JoTexture* spriteSheet, Vec2 leftTop, Vec2 size, Vec2 offset, UINT spriteLength, float duration, bool _bNoScale = false)
{
	for (UINT i = 0; i < spriteLength; ++i)
	{
		Sprite sprite = {};
		sprite.texture = spriteSheet;
		sprite.leftTop.x = leftTop.x + size.x * i;
		sprite.leftTop.y = leftTop.y;
		sprite.size = size;
		sprite.offset = offset;
		sprite.duration = duration;

		m_SheetVec.push_back(sprite);
	}

	m_bNoTimeScale = _bNoScale;
}

void Animation::CreateAnimation(const wstring& name, JoTexture* spriteSheet, Vec2 leftTop, Vec2 size, Vec2 offset, UINT spriteLength, UINT colCount, float duration, bool _bNoScale = false)
{
	UINT rowCount = spriteLength / colCount;

	for (UINT i = 0; i < spriteLength; ++i)
	{
		UINT row = i / colCount;
		UINT col = i % colCount;

		Sprite sprite = {};
		sprite.texture = spriteSheet;
		sprite.leftTop.x = leftTop.x + size.x * col;
		sprite.leftTop.y = leftTop.y + size.y * row;
		sprite.size = size;
		sprite.offset = offset;
		sprite.duration = duration;

		m_SheetVec.push_back(sprite);
	}

	m_bNoTimeScale = _bNoScale;
}



void Animation::Reset()
{
	m_fTime = 0.0f;
	m_iIndex = 0;
	m_bEnd = false;
}
