#pragma once
#include "GameObject.h"

class JoTexture;

class MiniMap :
    public GameObject
{
public:
    MiniMap();
   ~MiniMap();

   void Render()        override;

   void Set_MiniMapTex(JoTexture* const _pTex) { m_pMiniMapTex = _pTex; }
   void SetSize(const Vec2& _vSize) { m_vSize = _vSize; }
   void SetLeftTop(const Vec2& _vLeftTop) { m_vLeftTop = _vLeftTop; }
   void SetRealMapSize(const Vec2& _vSize) { m_vRealMapSize = _vSize; }

   static void Set_PlayerIconTex(JoTexture* const _pTex) { m_pPlayerIconTex = _pTex; }
   static void SetTarget(GameObject* const _pObj) { m_pTarget = _pObj; }
private:
    static GameObject* m_pTarget;
    static JoTexture* m_pPlayerIconTex;
    JoTexture* m_pMiniMapTex;

    Vec2 m_vLeftTop;
    Vec2 m_vSize;
    Vec2 m_vRealMapSize;
};

