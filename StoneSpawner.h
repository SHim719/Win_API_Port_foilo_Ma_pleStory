#pragma once
#include "GameObject.h"

class VellumStone;
class Player;
class Vellum;

class StoneSpawner :
    public GameObject
{
public:
    void Initialize() override;
    void Update() override;

    void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
    void SetVellum(Vellum* _pVellum) { m_pVellum = _pVellum; }
private:
    vector<VellumStone*> m_vecStones = {};
    Player* m_pPlayer = nullptr;
    Vellum* m_pVellum = nullptr;

    float m_fSpawnTime = 5.f;
    float m_fNowTime = 0.f;
    float m_fSpawnGap = 230.f;

    float m_fSpawnStart = 120.f;
    float m_fNowSpawnPosX;

    int m_iSpawnCount = 13;
};

