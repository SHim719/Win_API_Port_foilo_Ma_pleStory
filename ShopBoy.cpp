#include "ShopBoy.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "KeyMgr.h"
#include "ItemDatabase.h"
#include "SoundMgr.h"

ShopBoy::ShopBoy()
	: m_pTexture(nullptr)
	, m_tRect{}
	, m_vecSellItems{}
{
}

ShopBoy::~ShopBoy()
{
}

void ShopBoy::Initialize()
{
	m_pTexture = ResourceMgr::Find<JoTexture>(L"오코");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(86.f, 90.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	SetPos({ 1550.f, 387.f });

	m_tRect.left =	 LONG(GetPos().x - 43.f);
	m_tRect.right =	 LONG(GetPos().x + 43.f);
	m_tRect.top =	 LONG(GetPos().y - 45.f);
	m_tRect.bottom = LONG(GetPos().y + 45.f);

	m_vecSellItems.reserve(SHOP_SLOT);
	m_vecSellItems.push_back({ ItemDatabase::FindItemData(L"에테르넬 시프반다나"), 10000 });
	m_vecSellItems.push_back({ ItemDatabase::FindItemData(L"에테르넬 시프셔츠"), 10000 });
	m_vecSellItems.push_back({ ItemDatabase::FindItemData(L"에테르넬 시프팬츠"), 10000 });
	m_vecSellItems.push_back({ ItemDatabase::FindItemData(L"아케인셰이드 시프슈즈"), 10000 });
	m_vecSellItems.push_back({ ItemDatabase::FindItemData(L"리버스 페스카즈"), 999999 });
		
	
}

void ShopBoy::Update()
{
	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		ShopUI* pShopUI = UIMgr::Get_UI_Instance<ShopUI>(UI_Enums::UI_Shop);
		if (pShopUI == nullptr || pShopUI->IsActive())
			return;

		if (UIMgr::IsMouseUsed() == false)
		{	
			bool bFocused = Check_Rect();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				SoundMgr::Play(L"Bt_Click");
				pShopUI->SetActive(true);
				pShopUI->Set_SellItems(&m_vecSellItems);
				pShopUI->Update_Slot();
			}
		}

	}

	m_pAnimator->Update();
}

void ShopBoy::LateUpdate()
{
}

void ShopBoy::Render()
{
	m_pAnimator->Render();
}

void ShopBoy::Release()
{
}

bool ShopBoy::Check_Rect()
{
	Vec2 vMousePos = KeyMgr::GetWorldMousePos();

	if (vMousePos.x >=	  m_tRect.left
		&& vMousePos.y >= m_tRect.top
		&& vMousePos.x <= m_tRect.right
		&& vMousePos.y <= m_tRect.bottom)
	{
		return true;
	}

	return false;
}
