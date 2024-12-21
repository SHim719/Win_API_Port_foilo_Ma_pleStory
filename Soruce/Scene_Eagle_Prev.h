#pragma once
#include "Scene.h"


class Scene_Eagle_Prev :
    public Scene
{
public:
    Scene_Eagle_Prev();
    ~Scene_Eagle_Prev();

    void Initialize()   override;
    void OnEnter()    override;
    void OnExit()     override;

private:

};

