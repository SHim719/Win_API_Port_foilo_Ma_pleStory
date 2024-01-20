#pragma once

#include "Entity.h"
#include "Animation.h"

class JoTexture;
class GameObject;

struct Event
{
	void operator =(function<void()> func)
	{
		m_Event = move(func);
	}

	void operator ()()
	{
		if (m_Event)
			m_Event();
	}

	function<void()> m_Event = nullptr;
};

struct Events
{
	Events(size_t _frameCount) : frameCount(_frameCount) { frameEvents.resize(frameCount); }

	vector<Event> frameEvents = {};
	size_t frameCount = 0;
};

class Animator : public Entity
{
public:
	Animator();
	~Animator();

	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void CreateAnimation(const wstring& name,
		JoTexture* spriteSheet
		, Vec2 leftTop
		, Vec2 size
		, Vec2 offset
		, UINT spriteLength
		, float duration = 6000.0f);

	void CreateAnimation(const wstring& name,
		JoTexture* spriteSheet
		, Vec2 leftTop
		, Vec2 size
		, Vec2 offset
		, UINT spriteLength
		, UINT colCount
		, float duration = 6000.0f);

	Animation* FindAnimation(const wstring& name);
	void PlayAnimation(const wstring& name, bool loop = true);

	void SetActiveAnim(Animation* anim) { m_activeAnim = anim; }
	Animation* GetActiveAnim() const { return m_activeAnim; }

	bool IsEndAnim() { return m_activeAnim->IsEnd() && !m_bLoop; }
	UINT GetNowFrame() const;
	const bool& IsLoop() const { return m_bLoop; }

	void SetOwner(GameObject* _pOwner) {m_pOwner = _pOwner;}
	GameObject* GetOwner() const { return m_pOwner; }

	Events* GetEvents(const wstring& name);
private:
	map<wstring, Animation*> m_animations;
	Animation* m_activeAnim;
	bool m_bLoop;

	map<wstring, Events*> m_events;
	Events* m_pActiveEvents;

	UINT m_iNowFrame;

	GameObject* m_pOwner;
};

