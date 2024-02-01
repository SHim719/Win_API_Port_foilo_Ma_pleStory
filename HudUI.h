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
	void render_level();
	
private:
	PlayerStats*	m_pPlayerStats;
	JoTexture*		m_pHpBarTex;
	JoTexture*		m_pMpBarTex;
	JoTexture*		m_pExpBarTex;
	JoTexture*		m_pExpBarMaxTex;
	JoTexture*		m_pLevelTex;

	Vec2			m_vHpBarPos;
	Vec2			m_vMpBarPos;
	Vec2			m_vExpBarPos;
	Vec2			m_vLevelPos;

	int				m_iNowLevel;
	string			m_sNowLevel;

	float			m_fNowHp;
	float			m_fNowMp;
	float			m_fNowExp;
	float			m_fRenderHp;
	float			m_fRenderMp;
	float			m_fRenderExp;

	float			m_fHpSpeed;
	float			m_fMpSpeed;
	float			m_fExpSpeed;

};

