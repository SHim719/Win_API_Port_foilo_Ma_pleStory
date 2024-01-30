#pragma once
#include "GameObject.h"


class KillEffect :
    public GameObject
{
public:
    void Initialize(const int& _iNum, const Vec2& _vSize);
    void Update();
    void Render();

};

