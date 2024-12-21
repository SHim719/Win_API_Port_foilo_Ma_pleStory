#pragma once
#include "MovableUI.h"

class Player;

class DeathUI :
    public MovableUI
{
public:
    DeathUI();
    ~DeathUI();

	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;
	void Release()		override;

	void OnInActive()	override;
	void OnActive()		override;

	void SetPlayer(Player* const _pPlayer) { m_pPlayer = _pPlayer; }
	void SetActive(bool _b) { m_bActive = _b; }
private:
	void Check_Button();

private:
	Player* m_pPlayer;

	bool m_bActive;
};

