#include "Girl.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "SceneMgr.h"


Girl::Girl()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_pNameBarTex(nullptr)
	, m_vecDials{}
	, m_tRect{}
	, m_eState(Girl_State::First)
	, m_pInventory(nullptr)
	, m_pToken(nullptr)
{ 
}

Girl::~Girl()
{
}

void Girl::Initialize()
{
	m_pToken = ItemDatabase::FindItemData(L"시련의 증표");

	m_pTexture = ResourceMgr::Find<JoTexture>(L"의문의 소녀");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(99.f, 114.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"의문의 소녀_이름");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"의문의 소녀_대화");
	m_pNameBarTex = ResourceMgr::Find<JoTexture>(L"의문의 소녀_Bar");

	SetPos({ 1241.f, 813.f });

	m_tRect.left = LONG(GetPos().x - 99.f);
	m_tRect.right = LONG(GetPos().x + 99.f);
	m_tRect.top = LONG(GetPos().y - 114.f);
	m_tRect.bottom = LONG(GetPos().y + 114.f);

	m_vecDials.push_back({ L"저기..?", 0 });
	m_vecDials.push_back({ L"넌 누구야? 여기에 어떻게 들어왔어?", 1 });
	m_vecDials.push_back({ L"슬리피우드에서 길을 헤매다가 어떤 구멍에 빠졌는데 여기로 통하는 구멍이였어.", 0 });
	m_vecDials.push_back({ L"그렇구나. 그런데 여기는 자력으로 나갈 수 없어.", 1 });
	m_vecDials.push_back({ L"뭐?", 0 });
	m_vecDials.push_back({ L"여기는 나의 공간이야. 나의 마력을 이용해서 바깥으로 내보낼 수 있어.", 1 });
	m_vecDials.push_back({ L"아 그래? 그럼 어서 나를 내보내줘.", 0 });
	m_vecDials.push_back({ L"그게..", 1 });
	m_vecDials.push_back({ L"운이 나쁘게도 지금은 나의 마력이 고갈 된 상태야.", 1 });
	m_vecDials.push_back({ L"??.. 그럼 너의 마력은 언제 회복되는데?", 0 });
	m_vecDials.push_back({ L"지금으로부터 깊은 잠에 들면 1000년정도 뒤일거라고 생각해..", 1 });
	m_vecDials.push_back({ L"뭐?? 그럼 나보고 여기서 늙어 죽으라는 거야?", 0 });
	m_vecDials.push_back({ L"방법은 있어.", 1 });
	m_vecDials.push_back({ L"여기 4개의 포탈이 보이지? 포탈이 연결된 곳에서 시련의 증표를 획득해서 나에게 가져다 줘야해.", 1 });
	m_vecDials.push_back({ L"그 증표를 가져다 주면?", 0 });
	m_vecDials.push_back({ L"내가 그 증표의 마력을 이용해 너를 밖으로 내보낼 수 있어.", 1 });
	m_vecDials.push_back({ L"여기서 늙어죽을 순 없으니까 이 방법밖에 없는건가..", 0 });
	m_vecDials.push_back({ L"알았어. 너에게 증표를 가져다 줄게.", 0 });
	m_vecDials.push_back({ L"각각의 포탈은 이계로 연결되어 있어. 그곳엔 어떤 위험들이 도사리고 있을지 몰라. 조심해.", 1 });

	m_vecDials2.push_back({ L"아직 증표 4개가 모이지 않았어.", 1 });

	m_vecDials3.push_back({ L"증표 4개를 모아 왔어!", 0 });
	m_vecDials3.push_back({ L"고생했어. 증표의 힘을 이용해서 너를 바깥으로 보내줄게.", 1 });
	m_vecDials3.push_back({ L"드디어 집에 갈수있당 ㅎ", 0 });


}

void Girl::Update()
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
				if (m_eState == Girl_State::Second)
				{
					if (m_pInventory->FindItem(m_pToken) == 4)
						Set_End();
				}
				SoundMgr::Play(L"Bt_Click");
				pDialBox->SetActive(true);
				pDialBox->Set_NpcTex(m_pDialTex);
				pDialBox->Set_NpcNameTex(m_pDialNameTex);

				switch (m_eState)
				{
				case Girl::Girl_State::First:
					First(pDialBox);
					break;
				case Girl::Girl_State::Second:
					Second(pDialBox);
					break;
				case Girl::Girl_State::End:
					End(pDialBox);
					break;
				}
			}
		}
	}

	m_pAnimator->Update();
}

void Girl::LateUpdate()
{
}

void Girl::Render()
{
	m_pAnimator->Render();
	
	Vec2 vPos = GetPos();
	vPos = Camera::CalcRenderPos(vPos);

	vPos.y += 70.f;
	RenderMgr::RenderImage(m_pNameBarTex,
		vPos.x - m_pNameBarTex->GetWidth() * 0.5f, vPos.y - m_pNameBarTex->GetHeight() * 0.5f
		, vPos.x + m_pNameBarTex->GetWidth() * 0.5f, vPos.y + m_pNameBarTex->GetHeight() * 0.5f);
}

void Girl::Release()
{
}

bool Girl::Check_Rect()
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

void Girl::First(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials);
	pDialBox->Set_Function(bind(&Girl::Set_Second, this));
}

void Girl::Second(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials2);
}

void Girl::End(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials3);
	pDialBox->Set_Function(bind(&Girl::Change_Scene_Title, this));
}

void Girl::Change_Scene_Title()
{
	SoundMgr::Play(L"Light");
	SceneMgr::Reservation_ChangeScene(L"Scene_Title", Vec2(-1.f, -1.f));
}

