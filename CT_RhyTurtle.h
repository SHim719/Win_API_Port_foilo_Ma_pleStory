#pragma once
#include "Enemy.h"

class CT_RhyTurtle :
    public Enemy
{
    enum class State
    {
        Respawn,
        Idle,
        Move,
        Attack,
        Dead,
        End,
    };

public:
    CT_RhyTurtle();
    ~CT_RhyTurtle();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

    static void SetPixelDC(HDC _pPixel) { m_Pixel = _pPixel; }
    static void SetRespawnTime(float _fTime) { m_fRespawnTime = _fTime; }

    void OnCollisionStay(Collider* _pOther) override;

    void Hit(const HitInfo& _hitInfo);
    void SetRespawnPos(const Vec2& _vPos) { m_vRespawnPos = _vPos; SetPos(_vPos); }
private:
    void Idle();
    void Move();
    void Attack();
    void Dead();
    void Respawn();

    void SetState_Idle();
    void SetState_Move();
    void SetState_Dead()    override;
    void SetState_Attack() override;
    void SetState_Respawn();

    void Check_RightLeft();
private:
    static float m_fRespawnTime;
    static HDC m_Pixel;

    State m_eState;

    bool m_bRight;

    float m_fStateTime;
    float m_fNowTime;

    float m_fSpeed;

    Vec2 m_vRespawnPos;
};

