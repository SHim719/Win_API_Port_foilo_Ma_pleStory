#pragma once
#include "GameObject.h"


class VellumStone :
    public GameObject
{
public:
    VellumStone();
    ~VellumStone();

    void Initialize() override;
    void Update() override;
    void Render() override;

    void OnCollisionEnter(Collider* _pOther) override;

    void Play_Anim() const;
};

