#pragma once
#include "GameObject.h"


class Totem;
class TimerUI;

class TS_GameMgr :
    public GameObject
{
	enum class GameState
	{
		Start,
		Loop,
		End,
	};
public:
	TS_GameMgr();
	~TS_GameMgr();

	void Initialize()	override;
	void Update()		override;

	void Slash_Totem(const int& iVal);
	void Kill_Totem();

	void SetTimerUI(TimerUI* _pTimerUI) { m_pTimerUI = _pTimerUI; }

	bool IsGameEnd() const { return m_eState == GameState::End; }
private:
	void instantiate_Kill(int _iVal);
	void instantiate_Slash(const int& _iVal);

	void StartGame();
	void LoopGame();
	void EndGame();
private:
	list<Totem*> m_TotemList = {};

	Vec2 m_vKillRenderPos{};
	Vec2 m_vBottomPos{};
	bool m_bKillingTotem = false;
	float m_fFallSpeed = 0.f;
	int m_iSlashCnt = 0;

	TimerUI* m_pTimerUI;
	GameState m_eState = GameState::Start;


};

