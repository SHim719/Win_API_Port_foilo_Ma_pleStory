#pragma once
#include "Scene.h"


class Scene_Rudy :
    public Scene
{
public:
    void Initialize() override;
    void OnEnter()    override;
    void OnExit()     override;

private:
    void Init_Monster();
};

