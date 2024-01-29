#pragma once
#include "Scene.h"



class Scene_Eagle :
    public Scene
{

public:
    Scene_Eagle();
    ~Scene_Eagle();

    void Initialize() override;
    void OnEnter()    override;
    void OnExit()     override;
};

