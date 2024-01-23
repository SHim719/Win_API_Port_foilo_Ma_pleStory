#include "Camera.h"
#include "MainGame.h"

extern MainGame g_MainGame;

Vec2 Camera::m_vLookAt{};
Vec2 Camera::m_vSize{};
Vec2 Camera::m_vDistance{};
Vec2 Camera::m_vMinPos{};
Vec2 Camera::m_vMaxPos{};
Vec2 Camera::m_vPos{};
GameObject* Camera::m_pTarget = nullptr;

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
		m_vLookAt = m_vPos;
	}

	m_vLookAt.x = clamp(m_vLookAt.x, m_vMinPos.x, m_vMaxPos.x);
	m_vLookAt.y = clamp(m_vLookAt.y, m_vMinPos.y, m_vMaxPos.y);
	m_vPos = m_vLookAt;

	m_vDistance = m_vLookAt - (m_vSize / 2.0f);
}

void Camera::LateUpdate()
{
}

void Camera::Render()
{
}
