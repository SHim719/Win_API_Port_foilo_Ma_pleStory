#pragma once
#include "GameObject.h"

class TotemBar;
class TS_GameMgr;

class Totem_Player :
    public GameObject
{
public:
    Totem_Player();
    ~Totem_Player();

    void Initialize()   override;
    void Update()       override;
    void Render()      override;

    void Set_TotemBar(TotemBar* _pBar) { m_pTotemBar = _pBar; }
    void Set_Manager(TS_GameMgr* _pMgr) { m_pMgr = _pMgr;  }
private:
    void Play_AlertAnim();
    
private:
    TotemBar* m_pTotemBar = nullptr;
    TS_GameMgr* m_pMgr = nullptr;
};

