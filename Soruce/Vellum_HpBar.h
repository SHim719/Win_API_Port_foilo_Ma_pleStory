#pragma once
#include "GameObject.h"

class Vellum;

class Vellum_HpBar :
    public GameObject
{
public:
    Vellum_HpBar();
    ~Vellum_HpBar();

   void Initialize()     override;
   void Render()         override;

   void SetVellum(Vellum* const _pVellum) { m_pVellum = _pVellum; }
   void SetActive(const bool& _b) { m_bActive = _b; }
private:
    JoTexture* m_pMainTex;
    JoTexture* m_pHpBarTex;
    Vellum* m_pVellum;

    bool m_bActive;

    Vec2 m_vHpRenderPos;
};

