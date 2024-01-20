#pragma once
#include "UI.h"


class HudUI :
    public UI
{
public:
    HudUI();
    ~HudUI();

	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;
	void Release()		override;

private:
	JoTexture* m_pHpBarTex;
	JoTexture* m_pMpBarTex;

	Vec2 m_vHpBarPos;
	Vec2 m_vMpBarPos;

};

