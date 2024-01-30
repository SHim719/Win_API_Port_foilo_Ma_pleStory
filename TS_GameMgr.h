#pragma once
#include "GameObject.h"


class Totem;

class TS_GameMgr :
    public GameObject
{
public:
	TS_GameMgr();
	~TS_GameMgr();

	void Initialize()	override;
	void Update()		override;

	void Slash_Totem(const int& iVal);
	void Kill_Totem();
private:
	void instantiate_Kill(int _iVal);
	void instantiate_Slash(const int& _iVal);
	
private:
	list<Totem*> m_TotemList = {};

	Vec2 m_vKillRenderPos{};
	Vec2 m_vBottomPos{};

	bool m_bKillingTotem = false;

	float m_fFallSpeed = 0.f;

	int m_iSlashCnt = 0;
};

