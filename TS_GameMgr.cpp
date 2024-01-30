#include "TS_GameMgr.h"
#include "Totem.h"
#include "joObject.h"
#include "KillEffect.h"
#include "SlashEffect.h"
#include "SoundMgr.h"
#include "WhiteBuffer.h"

TS_GameMgr::TS_GameMgr()
{
}

TS_GameMgr::~TS_GameMgr()
{
}

void TS_GameMgr::Initialize()
{
	Vec2 vPos = { 693.f, 521.f };
	m_vBottomPos = vPos;

	for (int i = 0; i < 50; ++i)
	{
		Totem* pTotem = Instantiate<Totem>(eLayerType::LT_OBJECT); 
		pTotem->SetPos(vPos);
		m_TotemList.push_back(pTotem);
		vPos.y -= 190.f;
	}

	m_vKillRenderPos = Vec2(vPos.x + 200.f, 521.f - 280.f);
	m_fFallSpeed = 3000.f;
}

void TS_GameMgr::Update()
{
	if (m_bKillingTotem)
	{
		if (m_TotemList.empty())
			return;
		if (m_TotemList.front()->GetPos().y >= m_vBottomPos.y)
		{
			for (auto it = m_TotemList.begin(); it != m_TotemList.end(); ++it)
			{
				(*it)->GetRigidbody()->SetVelocity({ 0.f, 0.f });
			}
			m_bKillingTotem = false;
		}
	}
}

void TS_GameMgr::Slash_Totem(const int& iVal)
{
	instantiate_Kill(iVal);
	instantiate_Slash(iVal);

	if (iVal == 4)
	{
		Instantiate<WhiteBuffer>(eLayerType::LT_EFFECT)->Set_Fade(1.0f, 2.0f, false);
	}

	m_iSlashCnt = iVal;
}

void TS_GameMgr::Kill_Totem()
{
	float fSpeedX = 300.f;
	int iKillCount = 0;
	for (auto it = m_TotemList.begin(); iKillCount < m_iSlashCnt;)
	{
		if (m_TotemList.empty())
			return;

		Rigidbody* pRigid = (*it)->GetRigidbody();
		pRigid->SetVelocity(Vec2(fSpeedX, -500.f));
		pRigid->SetUseGravity(true);
		iKillCount++;

		it = m_TotemList.erase(it);
		fSpeedX += 100.f;
		SoundMgr::Play(L"Totem_Die_SFX");
	}

	for (auto it = m_TotemList.begin(); it != m_TotemList.end(); ++it)
	{
		if (m_TotemList.empty())
			return;
		(*it)->GetRigidbody()->SetVelocity({ 0.f, m_fFallSpeed });
	}
	m_bKillingTotem = true;
}

void TS_GameMgr::instantiate_Kill(int _iVal)
{
	if (_iVal > m_TotemList.size())
		_iVal = (int)m_TotemList.size();

	if (_iVal == 1 || _iVal == 3)
		return;

	Vec2 vSize = _iVal == 2 ? Vec2(364.f, 159.f) : Vec2(514.f, 296.f);

	KillEffect* pEffect = Instantiate_NoInit<KillEffect>(eLayerType::LT_UI);
	pEffect->Initialize(_iVal, vSize);
	pEffect->SetPos(m_vKillRenderPos);
}

void TS_GameMgr::instantiate_Slash(const int& _iVal)
{
	Vec2 vSize = Vec2::Zero;
	Vec2 vOffset = Vec2::Zero;
	UINT iLength = 0;

	switch (_iVal)
	{
	case 1:
		vSize = { 548.f, 187.f };
		iLength = 4;
		break;
	case 2:
		vSize = { 639.f, 401.f};
		vOffset = Vec2(0.f, -180.f);
		iLength = 8;
		break;
	case 4:
		vSize = { 721.f, 625.f };
		vOffset = Vec2(0.f, -180.f);
		iLength = 8;
		break;
	}
	SlashEffect* pSlashEffect = Instantiate_NoInit<SlashEffect>(eLayerType::LT_EFFECT);
	pSlashEffect->Set_GameMgr(this);
	pSlashEffect->Initialize(_iVal, vSize, vOffset, iLength);
	pSlashEffect->SetPos(m_vBottomPos);
}
