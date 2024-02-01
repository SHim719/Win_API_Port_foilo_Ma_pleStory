#include "EventPortal2.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "QuestMgr.h"
#include "MyDialogBox.h"
#include "UIMgr.h"
#include "HuntQuest.h"

EventPortal2::EventPortal2()
	: m_eState(PortalState::First)
{
	m_vecDials[0].push_back({ L"여기도 마찬가지다.", 0 });
	m_vecDials[0].push_back({ L"몬스터를 정리하고오자.", 0 });
	m_vecDials[1].push_back({ L"기운이 약해졌어. 이제 이동할 수 있겠어.", 0 });
}

void EventPortal2::OnCollisionStay(Collider* other)
{
	if (KeyMgr::GetKeyDown(eKeyCode::Up))
	{
		switch (m_eState)
		{
		case EventPortal2::PortalState::First:
			First();
			break;
		case EventPortal2::PortalState::Second:
			Second();
			break;
		case EventPortal2::PortalState::End:
			MoveTo(other->GetOwner());
			break;
		}
	}
}

void EventPortal2::First()
{
	MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
	if (pDialBox == nullptr || pDialBox->IsActive())
		return;
	Quest* pQuest = QuestMgr::Get_NowQuest();
	if (pQuest == nullptr)
	{
		pQuest = new HuntQuest;
		static_cast<HuntQuest*>(pQuest)->Set_Objectives(30);
		pQuest->Set_MainTex(ResourceMgr::Find<JoTexture>(L"Hunt_Quest30"));
		pQuest->Set_QuestNumber(2);
		pQuest->SetPos({ 0.f, 340.f });
		pDialBox->Set_Quest(pQuest);
	}

	pDialBox->Set_Dialog(&m_vecDials[0]);
	pDialBox->SetActive(true);

	m_eState = PortalState::Second;
}

void EventPortal2::Second()
{
	MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
	if (pDialBox == nullptr || pDialBox->IsActive())
		return;

	Quest* pQuest = QuestMgr::Get_NowQuest();
	if (pQuest->IsSatisfied())
	{
		pQuest->Set_Clear(true);
		pDialBox->Set_Dialog(&m_vecDials[1]);
		pDialBox->SetActive(true);
		m_eState = PortalState::End;
	}
	else
	{
		pDialBox->Set_Dialog(&m_vecDials[0]);
		pDialBox->SetActive(true);
	}
}


