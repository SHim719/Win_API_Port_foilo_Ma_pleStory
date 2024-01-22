#pragma once
#include "Item.h"
#include "Enrollable.h"
#include "Inventory.h"

class PlayerStats;

class Consumable :
    public Item, public Enrollable
{
public:
    Consumable();
    ~Consumable();

    void Render(const Vec2& vLeftTop)       override;
    void Key_Check(const eKeyCode& _key)    override;
    virtual void Use() {}

    static void SetPlayerStats(PlayerStats* const _pStats) { s_pPlayerStats = _pStats; }
    static void SetNumTex(JoTexture* const _pTex) { s_pNumTex = _pTex; }
protected:
   static PlayerStats* s_pPlayerStats;
   static JoTexture* s_pNumTex;

};

