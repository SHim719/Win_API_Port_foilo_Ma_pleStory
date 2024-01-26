#pragma once
#include "GameObject.h"

class JoTexture;

class MiniMap :
    public GameObject
{
public:
    MiniMap();
   ~MiniMap();

   void Initialize()    override;
   void Update()        override;
   void Render()        override;

   void Set_MiniMapTex(JoTexture* _pTex) { m_pMiniMapTex = _pTex; }
private:
    JoTexture* m_pMiniMapTex;
};

