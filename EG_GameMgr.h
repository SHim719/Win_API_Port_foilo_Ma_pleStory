#pragma once

#include "GameObject.h"

class TimerUI;

enum class GameState
{
	Start,
	Loop,
	End,
};

class EG_GameMgr
	: public GameObject
{
public:
	EG_GameMgr();
	~EG_GameMgr();

	 void Initialize()	override;
	 void Update()		override;

	 void StartGame();
	 void LoopGame();
	 void EndGame();

	 void Minus_BaldCnt() { m_iBaldCnt--; }
	 void Minus_EagleCnt() { m_iEagleCnt--; }

	 void SetTimerUI(TimerUI* _pTimerUI) { m_pTimerUI = _pTimerUI; }

	 bool IsGameEnd() const { return m_eGameState == GameState::End; }
private:
	GameState m_eGameState = GameState::Start;

	int m_iMaxBaldCnt = 0;
	int m_iMaxEagleCnt = 0;
	int m_iBaldCnt = 0;
	int m_iEagleCnt = 0;

	bool m_bSuccess = false;
	bool m_bFail = false;

	TimerUI* m_pTimerUI;
};

