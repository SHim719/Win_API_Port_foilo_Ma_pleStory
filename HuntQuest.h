#pragma once
#include "Quest.h"



class HuntQuest :
    public Quest
{
public:
    void Initialize();
    void Render();

    void Set_Objectives(int _iObjective) { m_iObjectives = _iObjective; }
    void Add_Hunt();
private:
    int m_iObjectives = 0;
    int m_iHuntCount = 0;

    Vec2 m_vNumberOffset[3] = { {50.f, 101.f}, m_vNumberOffset[0] + Vec2(11.f, 0.f),  m_vNumberOffset[1] + Vec2(11.f, 0.f) };
};

