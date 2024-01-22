#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "RenderMgr.h"

MyDialogBox::MyDialogBox()
	: m_pPlayerNameTex(nullptr)
	, m_pNpcNameTex(nullptr)
	, m_pPlayerTex(nullptr)
	, m_pNpcTex(nullptr)
	, m_pVecDialog(nullptr)
	, m_wsNowDialog(L"")
	, m_iNowIdx(0)
	, m_iRenderIdx(0)
	, m_fNowTime(0.f)
	, m_fTextRenderGap(0.03f)
	, m_bActive(false)
	, m_vPlayerRenderPos{}
	, m_vPlayerNameRenderPos{}
	, m_vNpcRenderPos{}
	, m_vNpcNameRenderPos{}
{	 
}	 

MyDialogBox::~MyDialogBox()
{
}

void MyDialogBox::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"DialogBox", L"Resources/UI/Dialog/DialogBox.png");
	m_pPlayerNameTex = ResourceMgr::Load<JoTexture>(L"Dial_Player_Name", L"Resources/UI/Dialog/DialogName_Player.png");
	m_pPlayerTex = ResourceMgr::Load<JoTexture>(L"Dial_Player", L"Resources/UI/Dialog/Dialog_Player.png");

	m_vPos = Vec2(120.f, 600.f);

	m_vPlayerRenderPos = Vec2(54.f, -68.f);
	m_vPlayerNameRenderPos = Vec2(15.f, 119.f);

	m_vNpcRenderPos = Vec2(582.f, -100.f);
	m_vNpcNameRenderPos = Vec2(580.f, 119.f);
}

void MyDialogBox::Update()
{
	if (!m_bActive || m_pVecDialog == nullptr)
		return;

	const wstring& wsOriginNowDial = (*m_pVecDialog)[m_iNowIdx].first;
	if (KeyMgr::GetKeyDown(eKeyCode::Enter))
	{
		if (wsOriginNowDial.size() == m_iRenderIdx)
		{
			m_iNowIdx++;
			if ((*m_pVecDialog).size() == m_iNowIdx)
			{
				m_wsNowDialog.clear();
				m_iRenderIdx = 0;
				m_iNowIdx = 0;
				m_bActive = false;
				return;
			}
			else
			{
				m_wsNowDialog.clear();
				m_iRenderIdx = 0;
			}	
		}	
	}

	if (wsOriginNowDial.size() == m_iRenderIdx)
		return;

	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= m_fTextRenderGap)
	{
		m_fNowTime = 0.f;
		m_wsNowDialog.push_back(wsOriginNowDial[m_iRenderIdx++]);
	}


}

void MyDialogBox::LateUpdate()
{
}

void MyDialogBox::Render()
{
	if (!m_bActive)
		return;

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + (float)m_pMainTex->GetWidth(), m_vPos.y + (float)m_pMainTex->GetHeight());

	Vec2 vRenderPos;
	if ((*m_pVecDialog)[m_iNowIdx].second == 0)
	{
		vRenderPos = m_vPos + m_vPlayerRenderPos;

		RenderMgr::RenderImage(m_pPlayerTex, vRenderPos.x, vRenderPos.y,
			vRenderPos.x + (float)m_pPlayerTex->GetWidth(), vRenderPos.y + (float)m_pPlayerTex->GetHeight());

		vRenderPos = m_vPos + m_vPlayerNameRenderPos;
		RenderMgr::RenderImage(m_pPlayerNameTex, vRenderPos.x, vRenderPos.y,
			vRenderPos.x + (float)m_pPlayerNameTex->GetWidth(), vRenderPos.y + (float)m_pPlayerNameTex->GetHeight());

		vRenderPos = m_vPos + Vec2(250.f, 40.f);

		RenderMgr::RenderText_L(m_wsNowDialog, vRenderPos.x, vRenderPos.y
			, vRenderPos.x + 500.f, vRenderPos.y + 200.f, 20.f, RGB(230, 230, 230));
	}
	else
	{
		vRenderPos = m_vPos + m_vNpcRenderPos;
		RenderMgr::RenderImage(m_pNpcTex, vRenderPos.x, vRenderPos.y,
			vRenderPos.x + (float)m_pNpcTex->GetWidth(), vRenderPos.y + (float)m_pNpcTex->GetHeight());

		vRenderPos = m_vPos + m_vNpcNameRenderPos;
		RenderMgr::RenderImage(m_pNpcNameTex, vRenderPos.x, vRenderPos.y,
			vRenderPos.x + (float)m_pNpcNameTex->GetWidth(), vRenderPos.y + (float)m_pNpcNameTex->GetHeight());

		vRenderPos = m_vPos + Vec2(40.f, 40.f);

		RenderMgr::RenderText_L(m_wsNowDialog, vRenderPos.x, vRenderPos.y
			, vRenderPos.x + 500.f, vRenderPos.y + 200.f, 20.f, RGB(230, 230, 230));
	}
}

void MyDialogBox::Release()
{
}
