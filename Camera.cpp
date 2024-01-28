#include "Camera.h"
#include "MainGame.h"
#include "TimeMgr.h"

extern MainGame g_MainGame;

Vec2 Camera::m_vLookAt{};
Vec2 Camera::m_vSize{};
Vec2 Camera::m_vDistance{};
Vec2 Camera::m_vMinPos{};
Vec2 Camera::m_vMaxPos{};
Vec2 Camera::m_vPos{};
CameraState Camera::m_eState = CameraState::Normal;
float Camera::m_fShakingTime = 0.f;
float Camera::m_fIntensity = 0.f;
GameObject* Camera::m_pTarget = nullptr;

void Camera::Initialize()
{
	m_vSize.x = (float)g_MainGame.GetWidth();
	m_vSize.y = (float)g_MainGame.GetHeight();

	m_vDistance = m_vLookAt - (m_vSize / 2.0f);

	m_eState = CameraState::Normal;
}

void Camera::Update()
{
	switch (m_eState)
	{
	case CameraState::Normal:
		Normal_State();
		break;
	case CameraState::Shaking:
		Shaking();
		break;
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

void Camera::Set_Shaking(const float& _fTime, const float& _fIntensity)
{
	m_fShakingTime = _fTime;
	m_fIntensity = _fIntensity;
	m_eState = CameraState::Shaking;
}

void Camera::Normal_State()
{
	if (m_pTarget != nullptr)
	{
		m_vLookAt = m_pTarget->GetPos();
	}
	else
	{
		m_vLookAt = m_vPos;
	}
}

void Camera::Shaking()
{
	static float fNowTime = 0.f;

	if (m_pTarget != nullptr)
	{
		m_vLookAt = m_pTarget->GetPos();
	}
	else
	{
		m_vLookAt = m_vPos;
	}

	fNowTime += TimeMgr::DeltaTime();

	if (fNowTime >= m_fShakingTime)
	{
		fNowTime = 0.f;
		m_eState = CameraState::Normal;
		return;
	}

	float fTheta = float(rand() % 360);
	float fRadian = fTheta * 3.141592f / 180.f;

	Vec2 vRandPos = Vec2(cosf(fRadian), sinf(fRadian));

	m_vLookAt += vRandPos * m_fIntensity;
}
