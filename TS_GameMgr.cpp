#include "TS_GameMgr.h"
#include "Totem.h"
#include "joObject.h"

TS_GameMgr::TS_GameMgr()
{
}

TS_GameMgr::~TS_GameMgr()
{
}

void TS_GameMgr::Initialize()
{
	Vec2 vPos = { 693.f, 521.f };
	for (int i = 0; i < 5; ++i)
	{
		Totem* pTotem = Instantiate<Totem>(eLayerType::LT_OBJECT); 
		pTotem->SetPos(vPos);
		m_TotemList.push_back(pTotem);
		vPos.y -= 190.f;
	}
	
}

void TS_GameMgr::Update()
{
}
