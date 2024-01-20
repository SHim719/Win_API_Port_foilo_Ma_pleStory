#pragma once
#include "Skill_Obj.h"


class FJ_Obj :
    public Skill_Obj
{
public:
    FJ_Obj();
    ~FJ_Obj();

    void Initialize()   override;
    void Update()       override;
    void LateUpdate()   override;
    void Render()       override;

    void Skill_Start()  override;
};

