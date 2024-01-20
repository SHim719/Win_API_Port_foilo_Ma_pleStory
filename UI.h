#pragma once
#include "ResourceMgr.h"

enum UI_Enums
{
	UI_HUD,
	UI_QuickSlot,
	UI_Exp,
	UI_Skill,
	UI_End,

};


class UI : public Entity
{
public:
	UI();
	~UI();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	virtual bool KeyCheck() { return false; };
	virtual void OnInActive() {};
protected:
	JoTexture*	m_pMainTex;
	Vec2		m_vPos;


};

