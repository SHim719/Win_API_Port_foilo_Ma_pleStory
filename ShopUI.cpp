#include "ShopUI.h"
#include "RenderMgr.h"
#include "Item.h"
#include "SoundMgr.h"
#include "UIMgr.h"

ShopUI::ShopUI()
	: m_vecSellItems{}
	, m_pInventory(nullptr)
	, m_pPlayerSelTex(nullptr)
	, m_pSellerSelTex(nullptr)
	, m_pShopTabTex(nullptr)
	, m_iBuyIdx(-1)
	, m_iSellIdx(-1)
	, m_iFocusedTab(0)
	, m_vArrTabPos{}
	, m_vSellButtonPos{}
	, m_vMesoPos{}
	, m_vExitButtonPos{}
	, m_vArrPlayerSelPos{}
	, m_vArrSellerSelPos{}
	, m_bActive(false)
	, m_vecNowTabInven{}
	, m_vArrPlayerNamePos{}
	, m_vArrSellerNamePos{}
{
}

ShopUI::~ShopUI()
{
}

void ShopUI::Initialize()
{
	m_vPos = { 200.f, 200.f };

	m_pMainTex = ResourceMgr::Find<JoTexture>(L"ShopUI");
	m_pPlayerSelTex = ResourceMgr::Find<JoTexture>(L"플레이어_선택");
	m_pSellerSelTex = ResourceMgr::Find<JoTexture>(L"상인_선택");
	m_pShopTabTex = ResourceMgr::Find<JoTexture>(L"Shop_Tab");

	Vec2 m_vTabPos = { 283.f, 100.f };
	float m_fGap = 36.f;
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
		m_vArrTabPos[i] = m_vTabPos + Vec2(m_fGap * i, 0.f);

	m_vSellButtonPos = { 435.f, 72.f };
	m_vBuyButtonPos = { 202.f, 72.f };
	m_vMesoPos = { 390.f, 54.f };
	m_vExitButtonPos = { 202.f, 54.f };

	Vec2 m_vPlayerSelPos = { 321.f, 122.f };
	Vec2 m_vSellerSelPos = { 47.f, 122.f };
	m_fGap = 42.f;
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrPlayerSelPos[i] = m_vPlayerSelPos + Vec2(0.f, m_fGap * i);
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrSellerSelPos[i] = m_vSellerSelPos + Vec2(0.f, m_fGap * i);

	Vec2 m_vPlayerIconPos = { 286.f, 112.f };
	Vec2 m_vSellerIconPos = { 12.f, 112.f };

	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrPlayerIconPos[i] = m_vPlayerIconPos + Vec2(0.f, m_fGap * i);
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrSellerIconPos[i] = m_vSellerIconPos + Vec2(0.f, m_fGap * i);

	Vec2 m_vPlayerNamePos = { 325.f, 112.f };
	Vec2 m_vSellerNamePos = { 51.f, 113.f };

	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrPlayerIconPos[i] = m_vPlayerNamePos + Vec2(0.f, m_fGap * i);
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrSellerIconPos[i] = m_vSellerNamePos + Vec2(0.f, m_fGap * i);


}

void ShopUI::Update()
{
	if (!m_bActive)
		return;

	m_vPrevMousePos = m_vMousePos;
	m_vMousePos = KeyMgr::GetMousePos();

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Focused();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				Check_Tab();
				Check_PlayerSlot();
				Check_SellerSlot();
			}
		}
	}
}

void ShopUI::Render()
{
	if (!m_bActive) 
		return;

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

	//35 19
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
	{
		if (m_iFocusedTab == i)
		{
			Vec2 vRenderPos = m_vPos + m_vArrTabPos[i] + Vec2(0.f, -2.f);
			RenderMgr::RenderFrame(m_pShopTabTex, vRenderPos.x, vRenderPos.y,
				vRenderPos.x + 35.f, vRenderPos.y + 19.f, 35.f * (float)i, 0.f, 35.f * (float)(i + 1), 19.f);
			break;
		}
	}
	
	if (m_iSellIdx >= 0)
	{
		Vec2 vRenderPos = m_vPos + m_vArrPlayerSelPos[m_iSellIdx];
		RenderMgr::RenderImage(m_pPlayerSelTex,
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + 165.f,
			vRenderPos.y + 35.f);
	}
	else if (m_iBuyIdx >= 0)
	{
		Vec2 vRenderPos = m_vPos + m_vArrSellerSelPos[m_iBuyIdx];
		RenderMgr::RenderImage(m_pSellerSelTex,
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + 208.f,
			vRenderPos.y + 35.f);
	}
}

void ShopUI::Release()
{
}

void ShopUI::Update_Slot()
{
	if (m_pInventory == nullptr)
		return;

	m_vecNowTabInven.clear();
	m_vecNowTabInven.reserve(SHOP_SLOT);
	
	Slot* arrInven = m_pInventory->Get_Inventory(m_iFocusedTab);

	if (arrInven == nullptr)
		return;

	for (int i = 0; i < INVEN_MAX; ++i)
	{
		if (arrInven[i].iCount > 0)
			m_vecNowTabInven.push_back(arrInven[i]);
		
		if (m_vecNowTabInven.size() == SHOP_SLOT)
			break;
	}
}

void ShopUI::Check_Tab()
{
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
	{
		Vec2 buttonPos = m_vPos + m_vArrTabPos[i];

		if (m_vMousePos.x >= buttonPos.x
			&& m_vMousePos.y >= buttonPos.y
			&& m_vMousePos.x <= buttonPos.x + 35.f
			&& m_vMousePos.y <= buttonPos.y + 17.f)
		{
			m_iFocusedTab = i;
			SoundMgr::Play(L"Tab_Click");
			return;
		}
	}
}

void ShopUI::Check_PlayerSlot()
{
	for (UINT i = 0; i < SHOP_SLOT; ++i)
	{
		Vec2 vPos = m_vPos + m_vArrPlayerSelPos[i];
		if (m_vMousePos.x >= vPos.x
			&& m_vMousePos.y >= vPos.y
			&& m_vMousePos.x <= vPos.x + m_pPlayerSelTex->GetWidth()
			&& m_vMousePos.y <= vPos.y + m_pPlayerSelTex->GetHeight()
			)
		{
			SoundMgr::Play(L"Bt_Click");
			m_iSellIdx = (int)i;
			m_iBuyIdx = -1;
			return;
		}
	}
	m_iSellIdx = -1;
}

void ShopUI::Check_SellerSlot()
{
	if (m_iSellIdx > 0) 
		return;
	
	for (UINT i = 0; i < SHOP_SLOT; ++i)
	{
		Vec2 vPos = m_vPos + m_vArrSellerSelPos[i];

		if (m_vMousePos.x >=	vPos.x
			&& m_vMousePos.y >= vPos.y
			&& m_vMousePos.x <= vPos.x + m_pSellerSelTex->GetWidth()
			&& m_vMousePos.y <= vPos.y + m_pSellerSelTex->GetHeight()
			)
		{
			SoundMgr::Play(L"Bt_Click");
			m_iBuyIdx = (int)i;
			m_iSellIdx = -1;
			return;
		}
	}
	m_iBuyIdx = -1;
}
