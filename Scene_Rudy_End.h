#pragma once
#include "Scene.h"
class Scene_Rudy_End :
    public Scene
{
public:
    void Initialize() override;
    void OnEnter()    override;
    void OnExit()     override;
};

