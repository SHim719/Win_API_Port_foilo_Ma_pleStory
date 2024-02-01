#pragma once
#include "Scene.h"

class Scene_Totem :
    public Scene
{
public:
    Scene_Totem();
    ~Scene_Totem();

    void OnGameStart();
    void OnEnter()    override;
    void OnExit()     override;
};

