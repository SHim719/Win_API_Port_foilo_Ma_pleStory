#include "Enemy.h"

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
