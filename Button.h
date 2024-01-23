#pragma once
#include "GameObject.h"

class JoTexture;

class Button :
    public GameObject
{
public:
    Button();
    ~Button();

    void Update();
    void Render();

    virtual void Press_Button() = 0;

protected:
    bool Check_Area();

protected:
    JoTexture*  m_pButtonTex;
    JoTexture*  m_pOnButtonTex;

    bool        m_bOnButton;
};

