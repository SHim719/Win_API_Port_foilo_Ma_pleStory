#pragma once
#include "GameObject.h"

class Vellum;
class StoneSpawner;

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
    void Set_Spawnwer(StoneSpawner* const _pSpawner) { m_pSpawner = _pSpawner; }
private:
    Vellum* m_pVellum;
    StoneSpawner* m_pSpawner;
};

