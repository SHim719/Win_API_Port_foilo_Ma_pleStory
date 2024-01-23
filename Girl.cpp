#include "Girl.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

Girl::Girl()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_vecDials{}
	, m_tRect{}
{ 
}

Girl::~Girl()
{
}

void Girl::Initialize()
{
	m_pTexture = ResourceMgr::Find<JoTexture>(L"의문의 소녀");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(99.f, 114.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"의문의 소녀_이름");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"의문의 소녀_대화");

	SetPos({ 1241.f, 813.f });

	m_tRect.left = LONG(GetPos().x - 99.f);
	m_tRect.right = LONG(GetPos().x + 99.f);
	m_tRect.top = LONG(GetPos().y - 114.f);
	m_tRect.bottom = LONG(GetPos().y + 114.f);

	m_vecDials.push_back({ L"하위 헬로 \n쥬신게임아카데미 143기 심재욱 테스트\n메아리 소리가 들려오는 계곡 속의 흐르는 물찾아 그 곳으로 여행을 떠나요" , 1 });
	m_vecDials.push_back({ L"가나다라 마바사아자차\n카타파하 라라랄라\n후회하고있어요 우리 다투던 그 날 괜한 자존심 때문에 끝내자고 말을 해버린거야" , 0 });

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
				SoundMgr::Play(L"Bt_Click");
				pDialBox->SetActive(true);
				pDialBox->Set_Dialog(&m_vecDials);
				pDialBox->Set_NpcTex(m_pDialTex);
				pDialBox->Set_NpcNameTex(m_pDialNameTex);
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
