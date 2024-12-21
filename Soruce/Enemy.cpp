#include "Enemy.h"
#include "QuestMgr.h"
#include "HuntQuest.h"
#include "Player.h"

Player* Enemy::m_pTarget = nullptr;

Enemy::Enemy()
	: m_iHp(0)
	, m_iMaxHp(0)
	, m_pAttackColl(nullptr)
{
}


Enemy::~Enemy()
{
}



void Enemy::AddHp(int _iHp)
{
	m_iHp = max(m_iHp + _iHp, 0);
	if (m_iHp == 0)
		SetState_Dead();
}

void Enemy::SetState_Dead()
{
	m_pTarget->Add_Exp(250);
	Quest* pQuest = QuestMgr::Get_NowQuest();
	if (pQuest == nullptr)
		return;

	HuntQuest* pHuntQuest = dynamic_cast<HuntQuest*>(pQuest);
	if (pHuntQuest)
	{
		pHuntQuest->Add_Hunt();
	}
}
