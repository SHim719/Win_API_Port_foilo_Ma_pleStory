#pragma once
#include "GameObject.h"

class Item;

class Item_Obj :
    public GameObject
{
public:
    enum class State
    {
        Appear,
        Loop,
        Obtain,
    };

    Item_Obj();
    ~Item_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

    void SetItem(Item* const _pItem) { m_pItem = _pItem; }
    void SetCount(const UINT& _iCount) { m_iCount = _iCount; }

    void CheckGround();

    void OnCollisionStay(Collider* _pOther) override;

    static void SetPixel(HDC _dc) { m_Pixel = _dc; }

protected:
    void Appear();
    void Loop();
    void Obtain();
protected:
    static HDC m_Pixel;

    Item* m_pItem;
    UINT  m_iCount;

    float m_fNowTime = 0.f;
    float m_fSpeed = 5.f;
    float m_fAlpha = 1.0f;

    State m_eState = State::Appear;
};

