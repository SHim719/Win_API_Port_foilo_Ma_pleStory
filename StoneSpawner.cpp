#include "StoneSpawner.h"
#include "VellumStone.h"
#include "joObject.h"
#include "TimeMgr.h"
#include "Player.h"
#include "Vellum.h"


void StoneSpawner::Initialize()
{
	m_vecStones.reserve(m_iSpawnCount);
	for (int i = 0; i < m_iSpawnCount; ++i)
	{
		m_vecStones.push_back(Instantiate<VellumStone>(eLayerType::LT_MONSTER_EFFECT));
		m_vecStones[i]->SetActive(false);
	}
	
}

void StoneSpawner::Update()
{
	if (m_pVellum->IsDeadState())
		Destroy(this);
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_fNowTime >= m_fSpawnTime)
	{
		float fRand = m_fSpawnStart + float(rand() % 5 * 10);
		m_fNowSpawnPosX = fRand;
		m_fNowTime = 0.f;
		
		float fTargetPosX = m_pPlayer->GetPos().x;
		for (int i = 0; i < m_iSpawnCount; ++i)
		{
			if (m_fNowSpawnPosX > 3055.f)
				return;

			if (abs(m_fNowSpawnPosX - fTargetPosX) < 100.f)
			{
				m_fNowSpawnPosX += m_fSpawnGap;
				continue;
			}
			m_vecStones[i]->SetActive(true);
			m_vecStones[i]->SetPos({ m_fNowSpawnPosX, -230.f });
			m_vecStones[i]->Play_Anim();
			m_fNowSpawnPosX += (m_fSpawnGap + float(rand() % 10) * 10.f);
		}
	}
	
}
