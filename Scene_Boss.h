#pragma once
#include "Scene.h"
class Scene_Boss :
    public Scene
{
public:
    Scene_Boss();
    ~Scene_Boss();

    void Initialize() override;

    void OnEnter()    override;
    void OnExit()     override;
};

