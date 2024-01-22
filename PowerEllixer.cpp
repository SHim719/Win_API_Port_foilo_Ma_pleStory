#include "PowerEllixer.h"
#include "PlayerStats.h"
#include "SoundMgr.h"



PowerEllixer::PowerEllixer()
{
	SetName(L"ÆÄ¿ö ¿¤¸¯¼­");
}

PowerEllixer::~PowerEllixer()
{
}

void PowerEllixer::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"PowerEllixer", L"Resources/Item/PowerEllixer.png");
	m_pIconTex = m_pItemTex;

	m_iMaxCount = 9999;
	m_iSellPrice = 1000;

}

void PowerEllixer::Use()
{
	SoundMgr::Play(L"Use_Potion");
	if (s_pPlayerStats)
	{
		s_pPlayerStats->Set_FullHP();
		s_pPlayerStats->Set_FullMP();
		m_pRefSlot->Add_Count(-1);
	}
}
