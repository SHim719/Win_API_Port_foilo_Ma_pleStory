#include "animtest.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"

void animtest::Initialize()
{
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	JoTexture* pTest = ResourceMgr::Load<JoTexture>(L"Test", L"Resources/Enemy/Vellum/Vellum_Breath_Loop.png");
	
	//m_pAnimator->CreateAnimation(L"Vellum_Move", pTest, Vec2::Zero, Vec2(412.f, 206.f), Vec2(0.f, 280.f), 10, 0.12f);
	

	//	ResourceMgr::Load<JoTexture>(L"Test", L"Resources/Enemy/Vellum/Vellum_Attack1.png");
	//m_pAnimator->CreateAnimation(L"Vellum_Attack1", pTest, Vec2::Zero, Vec2(996.f, 776.f), Vec2(-8.f, 10.f), 33, 7, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Attack1_R", pTest, Vec2::Zero, Vec2(996.f, 776.f), Vec2(10.f, 10.f), 33, 7, 0.1f);
	// 
	// 
	//  ResourceMgr::Load<JoTexture>(L"Test", L"Resources/Enemy/Vellum/Vellum_Attack2.png")
	//m_pAnimator->CreateAnimation(L"Vellum_Attack2", pTest, Vec2::Zero, Vec2(1498.f, 859.f), Vec2(-541.f, -67.f), 28, 5, 0.065f);

	//m_pAnimator->CreateAnimation(L"Vellum_Attack3", pTest, Vec2::Zero, Vec2(1220.f, 868.f), Vec2(-400.f, -61.f), 27, 7, 0.065f);


	///m_pAnimator->CreateAnimation(L"Vellum_Dig", pTest, Vec2::Zero, Vec2(714.f, 776.f), Vec2(-96.f, 11.f), 13, 7, 0.1f);

	//m_pAnimator->CreateAnimation(L"Vellum_LowNeck", pTest, Vec2::Zero, Vec2(996.f, 720.f), Vec2(-47.f, 39.f), 33, 7, 0.08f);
	//m_pAnimator->CreateAnimation(L"Vellum_Attack4", pTest, Vec2::Zero, Vec2(1696.f, 720.f), Vec2(-500.f, 39.f), 32, 4, 0.1f);

	//m_pAnimator->CreateAnimation(L"Vellum_Appear", pTest, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(-288.f, -109.f), 21, 6, 0.1f);

	//m_pAnimator->CreateAnimation(L"Vellum_Breath", pTest, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(-288.f, -109.f), 32, 5, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop", pTest, Vec2::Zero, Vec2(1312.f, 876.f), Vec2(-346.f, -39.f), 12, 6, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_End", pTest, Vec2::Zero, Vec2(1177.f, 758.f), Vec2(-413.f, -22.f), 7, 0.1f);

	//m_pAnimator->CreateAnimation(L"Vellum_Die", pTest, Vec2::Zero, Vec2(1008.f, 793.f), Vec2(-14.f, 20.f), 61, 8, 0.1f);
	
	//m_pAnimator->CreateAnimation(L"Vellum_Attack2_R", pTest, Vec2::Zero, Vec2(1498.f, 859.f), Vec2(540.f, -67.f), 28, 5, 0.065f);
	//m_pAnimator->CreateAnimation(L"Vellum_Attack3_R", pTest, Vec2::Zero, Vec2(1220.f, 868.f), Vec2(400.f, -61.f), 27, 7, 0.065f);
	//m_pAnimator->CreateAnimation(L"Vellum_Dig_R", pTest, Vec2::Zero, Vec2(714.f, 776.f), Vec2(96.f, 11.f), 13, 7, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_LowNeck_R", pTest, Vec2::Zero, Vec2(996.f, 720.f), Vec2(47.f, 39.f), 33, 7, 0.08f);
	//m_pAnimator->CreateAnimation(L"Vellum_Attack4_R", pTest, Vec2::Zero, Vec2(1696.f, 720.f), Vec2(500.f, 39.f), 32, 4, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Appear_R", pTest, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(288.f, -109.f), 21, 6, 0.1f);

	//m_pAnimator->CreateAnimation(L"Vellum_Breath_R", pTest, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(288.f, -109.f), 31, 5, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_R", pTest, Vec2::Zero, Vec2(1312.f, 876.f), Vec2(346.f, -39.f), 12, 6, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_End_R", pTest, Vec2::Zero, Vec2(1177.f, 758.f), Vec2(413.f, -22.f), 7, 0.1f);
	//m_pAnimator->CreateAnimation(L"Vellum_Die_R", pTest, Vec2::Zero, Vec2(1008.f, 793.f), Vec2(14.f, 20.f), 61, 8, 0.1f);

	m_pAnimator->PlayAnimation(L"Vellum_Breath_Loop");
}

void animtest::Update()
{
	m_pAnimator->Update();
}

void animtest::Render()
{
	m_pAnimator->Render();
}
