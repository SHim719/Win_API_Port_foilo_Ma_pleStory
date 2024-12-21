#include "FJ_Obj.h"
#include "ResourceMgr.h"

FJ_Obj::FJ_Obj()
{
}

FJ_Obj::~FJ_Obj()
{
}

void FJ_Obj::Initialize()
{
	m_vOffset = Vec2(50.0f, 0.f);

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"FlashJump");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"FlashJump_L", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(236.f, 133.f), Vec2::Zero,
		8, 0.08f);
	m_pAnimator->CreateAnimation(L"FlashJump_R", m_pSkillTex, Vec2(0.0f, 133.f), Vec2(236.f, 133.f), Vec2::Zero,
		8, 0.08f);
}

void FJ_Obj::Update()
{
	if (m_pAnimator->IsEndAnim())
		Destroy(this);

	m_pAnimator->Update();
}

void FJ_Obj::LateUpdate()
{
}

void FJ_Obj::Render()
{
	m_pAnimator->Render();
}

void FJ_Obj::Skill_Start()
{
	Vec2 vRenderPos = m_pOwner->GetPos();
	if (!m_pOwner->isRight())
	{
		vRenderPos += m_vOffset;
		m_pAnimator->PlayAnimation(L"FlashJump_L", false);
	}
	else
	{
		vRenderPos += Vec2(-1.f, 1.f) * m_vOffset;
		m_pAnimator->PlayAnimation(L"FlashJump_R", false);
	}
	
	SetPos(vRenderPos);
	SoundMgr::Play(L"FJ_Use");
}
