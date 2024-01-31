#include "EventPortal.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "QuestMgr.h"
#include "MyDialogBox.h"
#include "UIMgr.h"
#include "HuntQuest.h"


EventPortal::EventPortal()
	: m_eState(PortalState::End)
{
	m_vecDials[0].push_back({L"주위의 몬스터들의 기운때문에 이동할 수 없다.", 0});
	m_vecDials[0].push_back({ L"몬스터들을 한번 정리해야겠다.", 0 });
	m_vecDials[1].push_back({L"기운이 약해졌어. 이제 이동할 수 있겠어.", 0});
}

void EventPortal::OnCollisionStay(Collider* other)
{

	if (KeyMgr::GetKeyDown(eKeyCode::Up))
	{
		switch (m_eState)
		{
		case EventPortal::PortalState::First:
			First();
			break;
		case EventPortal::PortalState::Second:
			Second();
			break;
		case EventPortal::PortalState::End:
			MoveTo(other->GetOwner());
			break;
		}
	}
}

void EventPortal::First()
{
	MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
	if (pDialBox == nullptr || pDialBox->IsActive())
		return;
	Quest* pQuest = QuestMgr::Get_NowQuest();
	if (pQuest == nullptr)
	{
		pQuest = new HuntQuest;
		static_cast<HuntQuest*>(pQuest)->Set_Objectives(100);
		pQuest->Initialize();
		pQuest->Set_QuestNumber(1);
		pQuest->SetPos({ 0.f, 170.f });
		pDialBox->Set_Quest(pQuest);
	}

	pDialBox->Set_Dialog(&m_vecDials[0]);
	pDialBox->SetActive(true);

	m_eState = PortalState::Second;
}

void EventPortal::Second()
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

