#pragma once
#include "UI.h"
#include "KeyMgr.h"


class MovableUI :
    public UI
{
protected:
    Vec2 m_vMousePos = {};
    Vec2 m_vPrevMousePos = {};

    bool m_bIsMoving = false;

    bool Check_Focused();
    void Check_moveTab(const float& _fHeight);
};

