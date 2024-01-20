#pragma once

#include "Entity.h"


class JoTexture;
class Animator;

struct Sprite
{
	JoTexture* texture;
	Vec2 leftTop;
	Vec2 size;
	Vec2 offset;
	float duration;

	Sprite()
		: texture(nullptr)
		, leftTop(Vec2::Zero)
		, size(Vec2::Zero)
		, offset(Vec2::Zero)
		, duration(0.0f)
	{}
};


class Animation : public Entity
{
public:
	Animation();
	~Animation();

	void Reset();
	
	void Update();
	void Render();
	void Release();

	void CreateAnimation(const wstring& name,
		JoTexture* spriteSheet
		, Vec2 leftTop
		, Vec2 size
		, Vec2 offset
		, UINT spriteLength
		, float duration);

	void CreateAnimation(const wstring& name,
		JoTexture* spriteSheet
		, Vec2 leftTop
		, Vec2 size
		, Vec2 offset
		, UINT spriteLength
		, UINT colCount
		, float duration);

	bool IsEnd() { return m_bEnd; }
	void SetAnimator(Animator* animator) { m_pAnimator = animator; }

	const UINT& GetSpriteIdx() const { return m_iIndex; }

	const float& GetAlpha() const { return m_fAlpha; }
	void SetAlpha(const float& alpha) { m_fAlpha = alpha; }

private:
	Animator* m_pAnimator;

	vector<Sprite> m_SheetVec;
	UINT m_iIndex;
	float m_fTime;
	bool m_bEnd;

	float m_fAlpha = 1.0f;
};


