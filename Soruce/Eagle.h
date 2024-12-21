#pragma once
#include "Enemy.h"

class EG_GameMgr;

class Eagle :
    public Enemy
{
public:
	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void Hit(const HitInfo& _hitInfo) override;

	static void Set_GameMgr(EG_GameMgr* _pMgr) { s_pGameMgr = _pMgr; }

protected:
	void Reset_Dir();
	void Check_Area();

protected:
	static EG_GameMgr* s_pGameMgr;

	JoTexture* m_pEagleTex = nullptr;
	Vec2 m_vDir = Vec2::Zero;
	float m_fSpeed = 400.f;
	float m_fMoveTime = 0.f;

	bool m_bDie = false;
};

