#include "Enemy.h"

Player* Enemy::m_pTarget = nullptr;

Enemy::Enemy()
	: m_iHp(0)
	, m_iMaxHp(0)
{
}


Enemy::~Enemy()
{
}
