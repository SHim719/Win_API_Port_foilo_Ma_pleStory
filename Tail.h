#pragma once
#include "Enemy.h"

class Vellum;

class Tail :
    public Enemy
{
public:
    Tail();
    ~Tail();

    void Initialize();
    void Update();
    void Render();

    void Hit(const HitInfo& _hitInfo);

    void OnCollisionEnter(Collider* _pOther) override;

    void PlayAnim(const bool& _bRight);

    void SetOwner(Vellum* _pVellum) { m_pOwner = _pVellum; }
private:
    Vellum* m_pOwner;

};

