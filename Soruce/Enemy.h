#pragma once
#include "GameObject.h"
#include "HitInterface.h"


class JoTexture;
class Player;
class AttackCollider;

class Enemy :
    public GameObject, public HitInterface
{
public:
    Enemy();
    ~Enemy();

    virtual void Hit(const HitInfo& _hitInfo) {};

    static void SetTarget(Player* const _pPlayer) { m_pTarget = _pPlayer; }

    void AddHp(int _iHp);
    int GetHp() { return m_iHp; }
    int GetMaxHp() { return m_iMaxHp; }

    virtual void SetState_Attack() {};
protected:
    int m_iHp;
    int m_iMaxHp;

    AttackCollider* m_pAttackColl;
    Vec2 m_vAttackCollOffset;

    static Player* m_pTarget;

    virtual void SetState_Dead();
};

