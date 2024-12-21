#pragma once
#include "Scene.h"
#include "joObject.h"



class Scene_Rutabyss :
    public Scene
{
public:
    Scene_Rutabyss();
    ~Scene_Rutabyss();

    void Initialize() override;
                    
    void OnEnter()    override;
    void OnExit()     override;
};

