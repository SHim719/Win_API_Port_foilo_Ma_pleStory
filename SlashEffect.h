#pragma once
#include "GameObject.h"

class TS_GameMgr;

class SlashEffect : 
    public GameObject
{
public:
    void Initialize(const int& _iNum, const Vec2& _vSize, const Vec2& _vOffset, const UINT& _iLength);
    void Update();
    void Render();

    void Set_GameMgr(TS_GameMgr* _pMgr) { m_pGameMgr = _pMgr; }

private:
    void End_Anim();

private:
    TS_GameMgr* m_pGameMgr = nullptr;
};

