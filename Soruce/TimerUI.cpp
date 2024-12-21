#include "TimerUI.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "RenderMgr.h"

TimerUI::TimerUI()
{
}

TimerUI::~TimerUI()
{
}

void TimerUI::Initialize()
{
	m_pTimerTex = ResourceMgr::Find<JoTexture>(L"Timer");
	m_pNumberTex = ResourceMgr::Find<JoTexture>(L"Timer_Num");
}

void TimerUI::Update()
{
	if (m_fTime > 0.f)
		m_fTime -= TimeMgr::DeltaTime();
	else
		m_fTime = 0.f;
}


void TimerUI::Render()
{
	Vec2 vLeftTop = { 406.f, 25.f };
	RenderMgr::RenderImage(m_pTimerTex
		, vLeftTop.x, vLeftTop.y
		, vLeftTop.x + m_pTimerTex->GetWidth(), vLeftTop.y + m_pTimerTex->GetHeight());

	vLeftTop += { 97.f, 20.f };

	int iMinute = (int)m_fTime / 60;
	string sSecond = to_string((int)m_fTime % 60);

	RenderMgr::RenderFrame(m_pNumberTex
		, vLeftTop.x, vLeftTop.y
		, vLeftTop.x + 17.f, vLeftTop.y + 30.f
		, 17.f * iMinute, 0.f
		, 17.f * iMinute + 17.f, 30.f);

	vLeftTop.x += 45.f;

	if (sSecond.size() == 2)
	{
		RenderMgr::RenderFrame(m_pNumberTex
			, vLeftTop.x, vLeftTop.y
			, vLeftTop.x + 17.f, vLeftTop.y + 30.f
			, 17.f * (sSecond[0] - '0'), 0.f
			, 17.f * (sSecond[0] - '0') + 17.f, 30.f);

		vLeftTop.x += 25.f;

		RenderMgr::RenderFrame(m_pNumberTex
			, vLeftTop.x, vLeftTop.y
			, vLeftTop.x + 17.f, vLeftTop.y + 30.f
			, 17.f * (sSecond[1] - '0'), 0.f
			, 17.f * (sSecond[1] - '0') + 17.f, 30.f);
	}
	else
	{
		vLeftTop.x += 25.f;

		RenderMgr::RenderFrame(m_pNumberTex
			, vLeftTop.x, vLeftTop.y
			, vLeftTop.x + 17.f, vLeftTop.y + 30.f
			, 17.f * (sSecond[0] - '0'), 0.f
			, 17.f * (sSecond[0] - '0') + 17.f, 30.f);
	}
}
