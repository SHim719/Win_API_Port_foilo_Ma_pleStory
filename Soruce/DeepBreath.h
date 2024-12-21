#pragma once
#include "GameObject.h"


class DeepBreath :
    public GameObject
{
public:
    DeepBreath();
    ~DeepBreath();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

    void OnCollisionEnter(Collider* _pOther)    override;

    void Play_BreathAnim(const bool& _bRight);
    void Play_EndAnim(const bool& _bRight);

};

