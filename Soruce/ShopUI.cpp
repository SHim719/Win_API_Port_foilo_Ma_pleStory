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
	, m_pItemNumTex(nullptr)
{
}

ShopUI::~ShopUI()
{
}

void ShopUI::Initialize()
{
	m_vPos = { 250.f, 150.f };

	m_pMainTex = ResourceMgr::Find<JoTexture>(L"ShopUI");
	m_pPlayerSelTex = ResourceMgr::Find<JoTexture>(L"플레이어_선택");
	m_pSellerSelTex = ResourceMgr::Find<JoTexture>(L"상인_선택");
	m_pShopTabTex = ResourceMgr::Find<JoTexture>(L"Shop_Tab");
	m_pItemNumTex = ResourceMgr::Find<JoTexture>(L"Item_Number");

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

	Vec2 m_vPlayerIconPos = { 286.f, 122.f };
	Vec2 m_vSellerIconPos = { 12.f, 122.f };

	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrPlayerIconPos[i] = m_vPlayerIconPos + Vec2(0.f, m_fGap * i);
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrSellerIconPos[i] = m_vSellerIconPos + Vec2(0.f, m_fGap * i);

	Vec2 m_vPlayerNamePos = { 325.f, 122.f }; //482 157
	Vec2 m_vSellerNamePos = { 51.f, 123.f };

	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrPlayerNamePos[i] = m_vPlayerNamePos + Vec2(0.f, m_fGap * i);
	for (UINT i = 0; i < SHOP_SLOT; ++i)
		m_vArrSellerNamePos[i] = m_vSellerNamePos + Vec2(0.f, m_fGap * i);
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
				Check_ExitButton();
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

	for (size_t i = 0; i < m_vecNowTabInven.size(); ++i)
	{
		Vec2 vRenderPos = m_vPos + m_vArrPlayerIconPos[i];
		RenderMgr::RenderImage(m_vecNowTabInven[i]->item->GetItemTex(),
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + 32.f,
			vRenderPos.y + 32.f);

		if (m_iFocusedTab > 0)
		{
			vRenderPos.y += 21.f;

			string sNum = format("{}", m_vecNowTabInven[i]->iCount);

			for (size_t i = 0; i < sNum.size(); ++i)
			{
				int iNum = sNum[i] - '0';

				RenderMgr::RenderFrame(m_pItemNumTex
					, vRenderPos.x, vRenderPos.y
					, vRenderPos.x + 8.f, vRenderPos.y + 11.f
					, 8.f * iNum, 0.f
					, 8.f * iNum + 8.f, 11.f);

				if (iNum == 1)
					vRenderPos.x += 5.f;
				else
					vRenderPos.x += 8.f;
			}
		}

		vRenderPos = m_vPos + m_vArrPlayerNamePos[i];
		RenderMgr::RenderText(m_vecNowTabInven[i]->item->GetName()
			, vRenderPos.x
			, vRenderPos.y
			, vRenderPos.x + 157.f
			, vRenderPos.y + 16.f
			, 12.f, RGB(60, 60, 60));

		vRenderPos = m_vPos + m_vArrPlayerNamePos[i] + Vec2(0.f, 18.f);
		wstring wsMesoText = to_wstring(m_vecNowTabInven[i]->item->GetSellPrice()) + L" 메소";
		RenderMgr::RenderText(wsMesoText
			, vRenderPos.x
			, vRenderPos.y
			, vRenderPos.x + 157.f
			, vRenderPos.y + 16.f
			, 12.f, RGB(60, 60, 60));
	}

	for (size_t i = 0; i < m_vecSellItems->size(); ++i)
	{
		Vec2 vRenderPos = m_vPos + m_vArrSellerIconPos[i];
		RenderMgr::RenderImage((*m_vecSellItems)[i].pItem->GetItemTex(),
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + 32.f,
			vRenderPos.y + 32.f);

		vRenderPos = m_vPos + m_vArrSellerNamePos[i];
		RenderMgr::RenderText((*m_vecSellItems)[i].pItem->GetName()
			, vRenderPos.x
			, vRenderPos.y
			, vRenderPos.x + 157.f
			, vRenderPos.y + 16.f
			, 12.f, RGB(60, 60, 60));

		vRenderPos = m_vPos + m_vArrSellerNamePos[i] + Vec2(0.f, 18.f);
		wstring wsMesoText = to_wstring((*m_vecSellItems)[i].iPrice) + L" 메소";
		RenderMgr::RenderText(wsMesoText
			, vRenderPos.x
			, vRenderPos.y
			, vRenderPos.x + 157.f
			, vRenderPos.y + 16.f
			, 12.f, RGB(60, 60, 60));
	}

	wstring wsPlayerMesoText = to_wstring(m_pInventory->Get_Meso());
	RenderMgr::RenderText_R(wsPlayerMesoText
		, m_vPos.x + 410.f
		, m_vPos.y + 56.f
		, m_vPos.x + 498.f
		, m_vPos.y + 69.f
		, 12.f, RGB(60, 60, 60));
		
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
			m_vecNowTabInven.push_back(&arrInven[i]);
		
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
			Update_Slot();
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
			if (m_iSellIdx != i)
			{
				SoundMgr::Play(L"Bt_Click");
				m_iSellIdx = (int)i;
			}
			else
			{
				Sell(i);
			}
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
			if (m_iBuyIdx != i)
			{
				SoundMgr::Play(L"Bt_Click");
				m_iBuyIdx = (int)i;
			}
			else
			{
				Buy(i);
			}
			m_iSellIdx = -1;
			return;
		}
	}
	m_iBuyIdx = -1;
}

void ShopUI::Check_ExitButton()
{
	Vec2 vPos = m_vPos + m_vExitButtonPos;

	if (m_vMousePos.x >= vPos.x
		&& m_vMousePos.y >= vPos.y
		&& m_vMousePos.x <= vPos.x + 64.f
		&& m_vMousePos.y <= vPos.y + 16.f)
	{
		SoundMgr::Play(L"Bt_Click");
		m_bActive = false;
	}
}

void ShopUI::Buy(const UINT& _iSlotIdx)
{
	if ((*m_vecSellItems).size() <= (size_t)_iSlotIdx)
		return;

	int iMeso = m_pInventory->Get_Meso();
	if (iMeso < (*m_vecSellItems)[_iSlotIdx].iPrice)
		return;
	SoundMgr::Play(L"esc");

	m_pInventory->Add_Meso(-(*m_vecSellItems)[_iSlotIdx].iPrice);
	m_pInventory->Insert_Item((*m_vecSellItems)[_iSlotIdx].pItem, 1);

	Update_Slot();
}

void ShopUI::Sell(const UINT& _iSlotIdx)
{
	if (m_vecNowTabInven.size() <= (size_t)_iSlotIdx)
		return;

	Slot* pSlot = m_vecNowTabInven[_iSlotIdx];
	if (pSlot == nullptr)
		return;
	SoundMgr::Play(L"esc");

	m_pInventory->Add_Meso(pSlot->item->GetSellPrice());
	pSlot->Add_Count(-1);

	Update_Slot();
}
