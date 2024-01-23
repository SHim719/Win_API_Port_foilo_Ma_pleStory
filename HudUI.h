#pragma once
#include "UI.h"

class PlayerStats;

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

	void SetPlayerStats(PlayerStats* const _Stats) { m_pPlayerStats = _Stats; }
private:
	PlayerStats*	m_pPlayerStats;
	JoTexture*		m_pHpBarTex;
	JoTexture*		m_pMpBarTex;

	Vec2			m_vHpBarPos;
	Vec2			m_vMpBarPos;

	float			m_fNowHp;
	float			m_fNowMp;
	float			m_fRenderHp;
	float			m_fRenderMp;

	float			m_fHpSpeed;
	float			m_fMpSpeed;
};

