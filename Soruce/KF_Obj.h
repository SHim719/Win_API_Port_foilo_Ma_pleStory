#pragma once
#include "Skill_Obj.h"


class KF_Obj :
    public Skill_Obj
{
public:
    KF_Obj();
    ~KF_Obj();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

private:
    void Camera_Shake();
};

