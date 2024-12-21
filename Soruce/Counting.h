#pragma once
#include "GameObject.h"


class Counting :
    public GameObject
{
public:
    Counting();
    ~Counting();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
};

