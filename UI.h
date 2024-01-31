#pragma once
#include "ResourceMgr.h"

enum UI_Enums
{
	UI_HUD,
	UI_QuickSlot,
	UI_Exp,
	UI_Skill,
	UI_Inven,
	UI_Equip,
	UI_Stat,
	UI_Shop,
	UI_Dialog,
	UI_Death,
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

	
	virtual void OnInActive() {}
	virtual void OnActive() {}
	virtual bool KeyCheck() { return false; }

	void SetPos(const Vec2& _vPos) { m_vPos = _vPos; }
protected:
	JoTexture*	m_pMainTex;
	Vec2		m_vPos;


};

