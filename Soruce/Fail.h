#pragma once
#include "GameObject.h"
class Fail :
    public GameObject
{
public:
    Fail();
    ~Fail();

    void Initialize();
    void Update();
    void Render();
};

