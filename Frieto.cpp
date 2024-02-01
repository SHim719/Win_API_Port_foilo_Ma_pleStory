#include "Frieto.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"
#include "Item_Obj.h"
#include "joObject.h"
#include "ItemDatabase.h"

Frieto::Frieto()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_vecDials{}
	, m_vecDials2{}
	, m_tRect{}
	, m_bSuccessed(false)
	, m_eState(Frieto_State::First)
	, ChangeScene_ToGame(nullptr)
{
}

Frieto::~Frieto()
{
}

void Frieto::Initialize()
{
    SetPos({ 993.f, 608.f });

	m_pTexture = ResourceMgr::Find<JoTexture>(L"프리토");
	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"프리토_이름");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"프리토_대화");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(98.f, 81.f), Vec2::Zero, 6, 0.2f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	ChangeScene_ToGame = [&]() ->void {  SceneMgr::Reservation_ChangeScene(L"Scene_Eagle", { -100.f, -100.f }); };
	
	m_tRect.left = LONG(GetPos().x - 98.f);
	m_tRect.right = LONG(GetPos().x + 98.f);
	m_tRect.top = LONG(GetPos().y - 81.f);
	m_tRect.bottom = LONG(GetPos().y + 81.f);

	m_vecDials.push_back({ L"나랑 내기하자! 네가 이기면 시련의 증표를 주지!" , 1 });
	m_vecDials.push_back({ L"20초안에 대머리가 아닌 독수리를 모두 잡으면 돼." , 1 });
	m_vecDials.push_back({ L"그럼 바로 시작!" , 1 });
	m_vecDials.push_back({ L"거절이란 옵션은 없는건가.." , 0});

	m_vecDials2.push_back({ L"다시 도전할게." , 0 });
	m_vecDials2.push_back({ L"잘좀해봐!" , 1 });

	m_vecDials3.push_back({ L"오호 너 좀 하는데? 약속대로 증표를 줄게.", 1});
	m_vecDials3.push_back({ L"또 보자!", 1 });
}

void Frieto::Update()
{

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsActiveUIs())
			return;
		MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
		if (pDialBox == nullptr || pDialBox->IsActive())
			return;

		if (m_eState != Frieto_State::End)
		{
			Quest* _pQuest = QuestMgr::Get_NowQuest();
			if (_pQuest)
			{
				if (_pQuest->IsSatisfied())
				{
					_pQuest->Set_Clear(true);
					m_eState = Frieto_State::Third;
				}
					
			}
		}

		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Rect();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				SoundMgr::Play(L"Bt_Click");
				switch (m_eState)
				{
				case Frieto_State::First:
					First(pDialBox);
					break;
				case Frieto_State::Second:
					Second(pDialBox);
					break;
				case Frieto_State::Third:
					Third(pDialBox);
					break;
				}
			}
		}
	}

	m_pAnimator->Update();
}

void Frieto::LateUpdate()
{
}

void Frieto::Render()
{
	m_pAnimator->Render();
}

void Frieto::Release()
{
}

bool Frieto::Check_Rect()
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

void Frieto::First(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(ChangeScene_ToGame);

	if (QuestMgr::Get_NowQuest() == nullptr)
	{
		Quest* pQuest = new Quest;
		pQuest->Set_QuestNumber(2);
		QuestMgr::Set_NowQuest(pQuest);
	}

	m_eState = Frieto_State::Second;
}

void Frieto::Second(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials2);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(ChangeScene_ToGame);
}

void Frieto::Third(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials3);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(bind(&Frieto::Drop_Item, this));
}

void Frieto::Drop_Item()
{
	Item* pItem = ItemDatabase::FindItemData(L"시련의 증표");
	Item_Obj* pObj = Instantiate<Item_Obj>(eLayerType::LT_ITEM);
	pObj->SetPos(GetPos());
	pObj->SetItem(pItem);
	pObj->SetCount(1);
	SoundMgr::Play(L"Release_Item");
	m_eState = Frieto_State::End;
}

