#pragma once
#include "Skill_Obj.h"

class BT_Obj :
    public Skill_Obj
{
public:
    BT_Obj();
    ~BT_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

    void SetDir(const float& _fDir) { m_fDir = _fDir; }
private:
    void Play_LoopAnim();

private:
    JoTexture* m_pLoopTex;

    float m_fSpeed; 
    float m_fMoveDis;
    float m_fNowMoveDis;
    float m_fDir;
    float m_fLoopTime;
    float m_fNowTime;

    bool m_bLooping;
};

