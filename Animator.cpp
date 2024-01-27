#include "Animator.h"

Animator::Animator()
	: m_animations{}
	, m_activeAnim(nullptr)
	, m_bLoop(false)
	, m_events{}
	, m_pOwner(nullptr)
	, m_pActiveEvents(nullptr)
	, m_iNowFrame(0)
{
	SetName(L"Animator");
}

Animator::~Animator()
{
	Release();
}

void Animator::Initialize()
{
}

void Animator::Update()
{
	if (m_activeAnim != nullptr)
	{
		m_activeAnim->Update();
		
		if (m_iNowFrame != m_activeAnim->GetSpriteIdx())
		{
			m_iNowFrame = m_activeAnim->GetSpriteIdx();
			m_pActiveEvents->frameEvents[m_iNowFrame]();
		}

		if (m_activeAnim->IsEnd())
		{
			if (m_bLoop)
			{
				m_activeAnim->Reset();
				return;
			}
			m_pActiveEvents->EndEvent();
		}
	}
}
void Animator::LateUpdate()
{
}

void Animator::Render()
{
	if (m_activeAnim != nullptr)
		m_activeAnim->Render();
}

void Animator::Release()
{
	for (auto it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		Safe_Delete<Animation*>(it->second);
	}
	m_animations.clear();

	for (auto it = m_events.begin(); it != m_events.end(); ++it)
	{
		Safe_Delete<Events*>(it->second);
	}
	m_events.clear();
}

void Animator::CreateAnimation(const wstring& name, JoTexture* spriteSheet, Vec2 leftTop, Vec2 size, Vec2 offset, UINT spriteLength, float duration)
{
	Animation* anim = nullptr;
	anim = FindAnimation(name);
	if (anim != nullptr)
		return;

	anim = new Animation;
	anim->CreateAnimation(
		name,
		spriteSheet,
		leftTop,
		size,
		offset,
		spriteLength,
		duration);

	anim->SetAnimator(this);
	anim->SetName(name);

	Events* events = new Events(spriteLength);
	m_events.insert({ name, events });

	m_animations.insert({ name, anim });
}

void Animator::CreateAnimation(const wstring& name, JoTexture* spriteSheet, Vec2 leftTop, Vec2 size, Vec2 offset, UINT spriteLength, UINT colCount, float duration)
{
	Animation* anim = nullptr;
	anim = FindAnimation(name);
	if (anim != nullptr)
		return;

	anim = new Animation;
	anim->CreateAnimation(
		name,
		spriteSheet,
		leftTop,
		size,
		offset,
		spriteLength,
		colCount,
		duration);

	anim->SetAnimator(this);
	anim->SetName(name);

	Events* events = new Events(spriteLength);
	m_events.insert({ name, events });

	m_animations.insert({ name, anim });
}

Animation* Animator::FindAnimation(const wstring& name)
{
	auto it = m_animations.find(name);
	if (it == m_animations.end())
		return nullptr;

	return it->second;
}

void Animator::PlayAnimation(const wstring& name, bool loop)
{
	Animation* anim = FindAnimation(name);
	if (anim == nullptr)
		return;

	/*if (m_activeAnim == anim)
		return;*/

	m_activeAnim = anim;
	m_activeAnim->Reset();
	m_bLoop = loop;
	m_iNowFrame = 0;

	auto it = m_events.find(name);
	if (m_events.end() != it)
	{
		it->second->frameEvents[m_iNowFrame]();
		m_pActiveEvents = it->second;
	}
}

UINT Animator::GetNowFrame() const
{
	if (m_activeAnim == nullptr) 
		return 0;

	return m_activeAnim->GetSpriteIdx();
}

Events* Animator::GetEvents(const wstring& name)
{
	auto it = m_events.find(name);

	if (it == m_events.end()) 
		return nullptr;

	return it->second;
}
