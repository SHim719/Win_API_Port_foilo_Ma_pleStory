#pragma once
#include "Skill_Obj.h"


class AS_Obj :
    public Skill_Obj
{
public:
    AS_Obj();
    ~AS_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

private:
    float m_fGap;
    float m_fXOffset;

    JoTexture* m_pBottomTex;

    Animator* m_pBottomAnimator;

};

