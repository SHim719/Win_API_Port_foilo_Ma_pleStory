#pragma once
#include "GameObject.h"

class JoTexture;

class AnimBG :
    public GameObject
{
public:
    AnimBG();
    ~AnimBG();

   void Initialize()    override;
   void Update()        override;
   void LateUpdate()    override;
   void Render()        override;
   void Release()       override;
protected:
   vector<JoTexture*> m_vecBgTex{};
   UINT m_iNowFrame = 0;
   UINT m_iMaxFrame;

   float m_fFrameGap = 0.2f;
   float m_fNowTime = 0.f;
};

