#pragma once
#include "GameObject.h"

class JoTexture;

class HitEffect :
    public GameObject
{
public:
    HitEffect();
    ~HitEffect();

    void Initialize()   override;
    void Update()       override;
    void LateUpdate()   override;
    void Render()       override;

    void Set_EffectTex(JoTexture* _pEffectTex) { m_pEffectTex = _pEffectTex; }
    void SetSize(const Vec2& _vSize) { m_vSize = _vSize; }
    void SetOffset(const Vec2& _vOffset) { m_vOffset = _vOffset; }
    void Set_SpriteLength(const UINT& _iLength) { m_iSpriteLength = _iLength; }
    void SetDuration(const float& _fDuration) { m_fDuration = _fDuration; }

private:
    Vec2        m_vSize;
    JoTexture*  m_pEffectTex;
    Vec2        m_vOffset;
    UINT        m_iSpriteLength;
    float       m_fDuration;

};

