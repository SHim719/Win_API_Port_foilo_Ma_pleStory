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
	m_vOffset = Vec2(180.0f, 100.0f);

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"FlashJump_L");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"FlashJump_L", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.06f);
	m_pAnimator->CreateAnimation(L"FlashJump_L", m_pSkillTex, Vec2(0.0f, 400.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.06f);
}

void FJ_Obj::Update()
{
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
	if (!m_pOwner->isRight())
		m_pAnimator->PlayAnimation(L"FlashJump_L", false);
	else
		m_pAnimator->PlayAnimation(L"FlashJump_R", false);
	SoundMgr::Play(L"FJ_Use");
}
