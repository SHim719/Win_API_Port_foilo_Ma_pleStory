#pragma once
#include "GameObject.h"
#include "HitInterface.h"

class JoTexture;
class Player;

class Enemy :
    public GameObject, public HitInterface
{
public:
    Enemy();
    ~Enemy();

    void Hit(const HitInfo& _hitInfo) {}

    static void SetTarget(Player* const _pPlayer) { m_pTarget = _pPlayer; }

    void AddHp(int _iHp);
protected:
    int m_iHp;
    int m_iMaxHp;
    
    static Player* m_pTarget;

    virtual void SetState_Dead() {}
};

