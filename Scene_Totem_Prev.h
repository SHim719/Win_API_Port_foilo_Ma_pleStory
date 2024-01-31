#pragma once
#include "Scene.h"
class Scene_Totem_Prev :
    public Scene
{
public:
    Scene_Totem_Prev();
    ~Scene_Totem_Prev();

    void Initialize()   override;
    void OnEnter()    override;
    void OnExit()     override;

private:

};

