#pragma once
#include "GameObject.h"


class LevelUp :
    public GameObject
{
public:
    void Initialize()   override;
    void Update()   override;
    void Render()   override;

    void OnCollisionEnter(Collider* _pOther) override;

    void SetOwner(GameObject* const _pObj) { m_pOwner = _pObj; }
private:
    JoTexture* m_pLevelUpTex = nullptr;
    GameObject* m_pOwner = nullptr;
};

