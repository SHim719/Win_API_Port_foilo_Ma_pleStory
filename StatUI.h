#pragma once
#include "MovableUI.h"

class PlayerStats;

enum class eStatSequence
{
	STR,
	DEX,
	INT,
	LUK,
};

class StatUI :
    public MovableUI
{
public:
    StatUI();
    ~StatUI();

	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;
	void Release()		override;

	bool KeyCheck()		override { return KeyMgr::GetKeyDown(eKeyCode::T); };
	void OnInActive()	override;
	void OnActive()		override;

	void SetPlayerStats(PlayerStats* const _pStats) { m_pPlayerStats = _pStats; }
	PlayerStats* GetPlayerStats(PlayerStats* _pStats) const { return m_pPlayerStats; }

private:
	void Check_Buttons();
	
private:
    PlayerStats* m_pPlayerStats;

	JoTexture* m_pActiveButtonTex;
	JoTexture* m_pInActiveButtonTex;

	vector<Vec2> m_vec_BtRenderPos;
    
};

