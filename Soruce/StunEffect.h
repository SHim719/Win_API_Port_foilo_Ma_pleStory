#pragma once
#include "GameObject.h"
class StunEffect :
    public GameObject
{
public:
    StunEffect();
    ~StunEffect();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

    void SetOwner(GameObject* _pOwner) { m_pOwner = _pOwner; }
private:
    GameObject* m_pOwner;


};

