#pragma once

#include "MovableUI.h"
#include "Inventory.h"

#define SHOP_SLOT 9

struct SellItem
{
    Item* pItem = nullptr;
    int iPrice = 0;
};

class ShopUI :
    public MovableUI
{
public:
    ShopUI();
    ~ShopUI();

    void Initialize() override;
    void Update() override;
    void Render() override;
    void Release() override;

   void Set_Inventory(Inventory* _pInven) { m_pInventory = _pInven; }

    void Set_SellItems(const vector<SellItem>& _vecSellItems) { m_vecSellItems = _vecSellItems; }

    const bool& IsActive() const { return m_bActive; }
    void SetActive(const bool& _b) { m_bActive = _b; }

    void Update_Slot();
private:
    void Check_Tab();
    void Check_PlayerSlot();
    void Check_SellerSlot();

private:
    Inventory* m_pInventory;
    vector<SellItem> m_vecSellItems;
    vector<Slot&> m_vecNowTabInven;

    JoTexture* m_pPlayerSelTex;
    JoTexture* m_pSellerSelTex;
    JoTexture* m_pShopTabTex;

    UINT m_iFocusedTab;
    int m_iBuyIdx;
    int m_iSellIdx;

    Vec2 m_vArrTabPos[(UINT)ItemType::IT_END];
    Vec2 m_vSellButtonPos;
    Vec2 m_vBuyButtonPos;
    Vec2 m_vExitButtonPos;
    Vec2 m_vMesoPos;

    Vec2 m_vArrPlayerSelPos[SHOP_SLOT];
    Vec2 m_vArrSellerSelPos[SHOP_SLOT];

    Vec2 m_vArrPlayerIconPos[SHOP_SLOT];
    Vec2 m_vArrSellerIconPos[SHOP_SLOT];

    Vec2 m_vArrPlayerNamePos[SHOP_SLOT];
    Vec2 m_vArrSellerNamePos[SHOP_SLOT];

    bool m_bActive;

};

