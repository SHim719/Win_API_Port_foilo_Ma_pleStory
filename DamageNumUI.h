#pragma once
#include "MovableUI.h"


class DamageNumUI :
    public MovableUI
{
public:
    DamageNumUI();
    ~DamageNumUI();

	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;
	void Release()		override;

	bool KeyCheck()		override { return KeyMgr::GetKeyDown(eKeyCode::NUMPAD1); };
	void OnInActive()	override;
	void OnActive()		override;

private:
	bool Check_Number();
	bool Check_Mode();

private:
	Vec2 m_vFontSelOffset;
	Vec2 m_vModeSelOffset;

};

