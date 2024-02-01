#include "Stone.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"
#include "ItemDatabase.h"
#include "Item_Obj.h"
#include "joObject.h"
#include "TimeMgr.h"
#include "WhiteBuffer.h"

Stone::Stone()
	: m_pTexture(nullptr)
	, m_tRect{}
{
}

Stone::~Stone()
{
}

void Stone::Initialize()
{
	SetPos({ 2057.f, 402.f });
	m_pTexture = ResourceMgr::Find<JoTexture>(L"조형물");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(87.f, 132.f), Vec2::Zero, 11, 0.2f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	m_tRect.left = LONG(GetPos().x - 87.f);
	m_tRect.right = LONG(GetPos().x + 87.f);
	m_tRect.top = LONG(GetPos().y - 132.f);
	m_tRect.bottom = LONG(GetPos().y + 132.f);

	m_vecDials.push_back({ L"돌이네." , 0 });
	m_vecDials.push_back({ L"돌에는 이렇게 쓰여있다." , 0 });
	m_vecDials.push_back({ L"시련을 극복한 자에게 징표를.." , 0 });

	m_pTokenItem = ItemDatabase::FindItemData(L"시련의 증표");
}

void Stone::Update()
{

	switch (m_eState)
	{
	case Stone::State::First:
		First();
		break;
	case Stone::State::Second:
		Second();
		break;
	}
	
	m_pAnimator->Update();
}

void Stone::LateUpdate()
{
}

void Stone::Render()
{
	m_pAnimator->Render();
}


bool Stone::Check_Rect()
{
	Vec2 vMousePos = KeyMgr::GetWorldMousePos();

	if (vMousePos.x >= m_tRect.left
		&& vMousePos.y >= m_tRect.top
		&& vMousePos.x <= m_tRect.right
		&& vMousePos.y <= m_tRect.bottom)
	{
		return true;
	}

	return false;
}

void Stone::Drop_Item()
{
	//WhiteBuffer
	Item_Obj* pObj = Instantiate<Item_Obj>(eLayerType::LT_ITEM);
	pObj->SetPos(GetPos());
	pObj->SetItem(m_pTokenItem);
	pObj->SetCount(1);
	m_pObj = pObj;
	SoundMgr::Play(L"Release_Item");
	m_eState = State::Second;
}

void Stone::Slow_Time()
{
	static float m_fNowTime = 0.f;
}

void Stone::First()
{
	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsActiveUIs())
			return;
		MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
		if (pDialBox == nullptr || pDialBox->IsActive())
			return;

		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Rect();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				SoundMgr::Play(L"Bt_Click");
				pDialBox->SetActive(true);
				pDialBox->Set_Dialog(&m_vecDials);
				pDialBox->Set_Function(bind(&Stone::Drop_Item, this));
			}
		}

	}
}

void Stone::Second()
{
	static float fNowTime = 0.f;

	fNowTime += TimeMgr::DeltaTime();

	if (fNowTime >= 2.f)
	{
		WhiteBuffer* pBuffer = Instantiate<WhiteBuffer>(eLayerType::LT_UI);
		pBuffer->Set_Fade(0.f, 0.3f, true, true);
		SoundMgr::Play(L"Light");

		fNowTime = 0.f;
		m_vecDials.clear();
		m_vecDials.push_back({ L"징표를 줍자 하얀 빛이 몸을 감쌌다.", 0 });
		MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
		pDialBox->SetActive(true);
		pDialBox->Set_Dialog(&m_vecDials);
		pDialBox->Set_Function(bind(&Stone::Change_Scene, this));
		m_eState = State::End;
	}
}

void Stone::Change_Scene()
{
	SceneMgr::Reservation_ChangeScene(L"Scene_Rutabyss", { 500.f, 830.f });
}
