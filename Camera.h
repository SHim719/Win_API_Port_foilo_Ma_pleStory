#pragma once
#include "GameObject.h"

enum class CameraState
{
    Normal,
    Shaking,
    FadeOut,
    FadeIn,
};

class Camera 
{
public:
    static void Initialize();
    static void Update();
    static void LateUpdate();
    static void Render();

    static void SetTarget(GameObject* target) 
    {
        m_pTarget = target; 
    }

    static Vec2 CalcRenderPos(Vec2& pos) { return pos - m_vDistance;}
    
    static const Vec2& GetCameraSize()  { return m_vSize; }

    static void SetLookAt(const Vec2& _vLookAt) { m_vLookAt = _vLookAt; }
    static const Vec2& GetLookAt() { return m_vLookAt; }
    static const Vec2& GetDistance()  { return m_vDistance; }

    static void SetMinCameraPos(const Vec2& _vArea) { m_vMinPos = _vArea; }
    static void SetMaxCameraPos(const Vec2& _vArea) { m_vMaxPos = _vArea; }

    static void Set_Shaking(const float& _fTime, const float& _fIntensity);
    static void Set_FadeIn(const float& _fSpeed, const float& _fAlpha, bool _bBlack);
    static void Set_FadeOut(const float& _fSpeed, const float& _fAlpha, bool _bBlack);

    static void Set_NoLimit(bool _b) { m_bNoLimit = _b; }

    static bool IsFadeOut() { return m_eState == CameraState::FadeOut; }
    static bool IsFadeIn() { return m_eState == CameraState::FadeIn; }
private:
    static void Normal_State();
    static void Shaking();
    static void FadeIn();
    static void FadeOut();

private:
    static  Vec2 m_vOriginPos;
    static  Vec2 m_vLookAt;
    static  Vec2 m_vSize;
    static  Vec2 m_vDistance;
    static  Vec2 m_vMinPos;
    static  Vec2 m_vMaxPos;
    static  GameObject* m_pTarget;
    static  CameraState m_eState;

    static float m_fShakingTime;
    static float m_fIntensity;

    static bool m_bNoLimit;

    static JoTexture* m_pBlackBuffer;
    static JoTexture* m_pWhiteBuffer;

    static float m_fFadeSpeed;
    static float m_fAlpha;
    static bool m_bBlack;

};

