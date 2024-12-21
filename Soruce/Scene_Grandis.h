#pragma once
#include "Scene.h"

class Scene_Grandis :
    public Scene
{
public:
    Scene_Grandis();
    ~Scene_Grandis();

    void Initialize() override;
    void OnEnter()    override;
    void OnExit()     override;

private:
    void Init_Monster();

};

