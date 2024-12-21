#pragma once
#include "GameObject.h"



class Totem :
    public GameObject
{
public:
    Totem();
    ~Totem();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

private:
    JoTexture* m_pTotemTex = nullptr;
};

