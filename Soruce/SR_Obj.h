#pragma once
#include "Skill_Obj.h"
class SR_Obj :
    public Skill_Obj
{
public:
    SR_Obj();
    ~SR_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

private:
    Animator* m_pBackAnimator = nullptr;
    JoTexture* m_pBackTex = nullptr;
};

