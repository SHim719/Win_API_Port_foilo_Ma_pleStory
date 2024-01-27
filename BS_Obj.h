#pragma once
#include "Skill_Obj.h"


class BS_Obj :
    public Skill_Obj
{
public:
    BS_Obj();
    ~BS_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

    void SetDir(const Vec2& _vDir) { m_vDir = _vDir; }

private:
    Vec2 m_vDir;
    float m_fGap;
    float m_fXOffset;
};

