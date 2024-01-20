#pragma once
#include "GameObject.h"

class Camera :
    public GameObject
{
public:
    Camera();
    ~Camera();

    void Initialize()   override;
    void Update()       override;
    void LateUpdate()   override;
    void Render()       override;

    void SetTarget(GameObject* target) { m_pTarget = target; }

    Vec2 CalcRenderPos(Vec2& pos) { return pos - m_vDistance;}

    const Vec2& GetCameraSize() const { return m_vSize; }

    void SetLookAt(const Vec2& _vLookAt) { m_vLookAt = _vLookAt; }
    const Vec2& GetLookAt() const { return m_vLookAt; }

    const Vec2& GetDistance() const { return m_vDistance; }

    void SetMinCameraPos(const Vec2& _vArea) { m_vMinPos = _vArea; }
    void SetMaxCameraPos(const Vec2& _vArea) { m_vMaxPos = _vArea; }
private:
    Vec2 m_vLookAt;
    Vec2 m_vSize;
    Vec2 m_vDistance;
    Vec2 m_vMinPos;
    Vec2 m_vMaxPos;

    GameObject* m_pTarget;
};

