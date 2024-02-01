#pragma once
#include "GameObject.h"


class RapidStream :
    public GameObject
{
public:
    RapidStream();
    ~RapidStream();

    void Initialize()   override;

    void OnCollisionEnter(Collider* _pOther)    override;
    void OnCollisionStay(Collider* _pOther)     override;
    void OnCollisionExit(Collider* _pOther)     override;
private:
    float m_fAddVelocityX;

};

