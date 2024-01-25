#pragma once
#include "GameObject.h"

class Vellum;

class VellumTrigger :
    public GameObject
{
public:
    VellumTrigger();
    ~VellumTrigger();

    void Initialize() override;
    void Update()   override;
    void Render()   override;

    void Set_Vellum(Vellum* const _pVellum) { m_pVellum = _pVellum; }
private:
    Vellum* m_pVellum;
};

