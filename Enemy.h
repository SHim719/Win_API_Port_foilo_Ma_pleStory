#pragma once
#include "GameObject.h"
#include "HitInterface.h"

class JoTexture;

class Enemy :
    public GameObject, public HitInterface
{
public:
    Enemy();
    ~Enemy();

    void Hit(const HitInfo& _hitInfo) {}

protected:
    int m_iHp;

};

