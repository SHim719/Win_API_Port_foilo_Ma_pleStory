#include "Camera.h"
#include "MainGame.h"

extern MainGame g_MainGame;

Camera::Camera()
	: m_vLookAt{}
	, m_vSize{}
	, m_vDistance{}
	, m_pTarget(nullptr)
	, m_vMinPos{}
	, m_vMaxPos{}
{
	SetName(L"Camera");
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	m_vSize.x = (float)g_MainGame.GetWidth();
	m_vSize.y = (float)g_MainGame.GetHeight();

	m_vDistance = m_vLookAt - (m_vSize / 2.0f);
}

void Camera::Update()
{
	if (m_pTarget != nullptr)
	{
		m_vLookAt = m_pTarget->GetPos();
	}
	else
	{
		m_vLookAt = GetPos();
	}

	m_vLookAt.x = clamp(m_vLookAt.x, m_vMinPos.x, m_vMaxPos.x);
	m_vLookAt.y = clamp(m_vLookAt.y, m_vMinPos.y, m_vMaxPos.y);
	SetPos(m_vLookAt);

	m_vDistance = m_vLookAt - (m_vSize / 2.0f);
}

void Camera::LateUpdate()
{
}

void Camera::Render()
{
}
