#pragma once
#include "Scene.h"
#include "joObject.h"
#include "MainCamera.h"



class Scene_Title :
    public Scene
{
public:
    Scene_Title();
    ~Scene_Title();

    void Initialize() override;
                    
    void OnEnter()    override;
    void OnExit()     override;

private:
    HDC m_pixelDC = nullptr;

 
};

