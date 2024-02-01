#include "Camera.h"
#include "MainGame.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"

extern MainGame g_MainGame;

Vec2 Lerp(Vec2& start, Vec2& end, float t)
{
	// t는 0에서 1 사이의 값입니다.
	// t가 0이면 start를 반환합니다.
	// t가 1이면 end를 반환합니다.

	if (t <= 0.0f)
		return start;
	else if (t >= 1.0f)
		return end;

	return start + (end - start) * 6.f * TimeMgr::DeltaTime_NoScale();
}

Vec2 Camera::m_vLookAt{};
Vec2 Camera::m_vSize{};
Vec2 Camera::m_vDistance{};
Vec2 Camera::m_vMinPos{};
Vec2 Camera::m_vMaxPos{};
Vec2 Camera::m_vOriginPos{};
CameraState Camera::m_eState = CameraState::Normal;
float Camera::m_fShakingTime = 0.f;
float Camera::m_fIntensity = 0.f;
bool Camera::m_bNoLimit = false;
GameObject* Camera::m_pTarget = nullptr;
JoTexture* Camera::m_pBlackBuffer = nullptr;
JoTexture* Camera::m_pWhiteBuffer = nullptr;
float Camera::m_fFadeSpeed = 0.f;
float Camera::m_fAlpha = 0.f;
bool Camera::m_bBlack = false;

void Camera::Initialize()
{
	m_vSize.x = (float)g_MainGame.GetWidth();
	m_vSize.y = (float)g_MainGame.GetHeight();

	m_vDistance = m_vLookAt - (m_vSize / 2.0f);

	m_eState = CameraState::Normal;

	m_pBlackBuffer = ResourceMgr::Find<JoTexture>(L"BlackBuffer");
	m_pWhiteBuffer = ResourceMgr::Find<JoTexture>(L"WhiteBuffer");
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
	case CameraState::FadeOut:
		FadeOut();
		break;
	case CameraState::FadeIn:
		FadeIn();
		break;
	}

	if (m_bNoLimit == false)
	{
		m_vLookAt.x = clamp(m_vLookAt.x, m_vMinPos.x, m_vMaxPos.x);
		m_vLookAt.y = clamp(m_vLookAt.y, m_vMinPos.y, m_vMaxPos.y);
	}
	m_vDistance = m_vLookAt - (m_vSize / 2.0f);
}

void Camera::LateUpdate()
{
}

void Camera::Render()
{
	if (IsFadeIn() || IsFadeOut())
	{
		if (m_bBlack)
		{
			RenderMgr::RenderImage(m_pBlackBuffer,
				0.f, 0.f, m_vSize.x, m_vSize.y,
				m_fAlpha);
		}
		else
		{
			RenderMgr::RenderImage(m_pWhiteBuffer,
				0.f, 0.f, m_vSize.x, m_vSize.y,
				m_fAlpha);
		}
	}
}

void Camera::Set_Shaking(const float& _fTime, const float& _fIntensity)
{
	m_fShakingTime = _fTime;
	m_fIntensity = _fIntensity;
	m_vOriginPos = m_vLookAt;
	m_eState = CameraState::Shaking;
}

void Camera::Set_FadeIn(const float& _fSpeed, const float& _fAlpha, bool _bBlack)
{
	m_fFadeSpeed = _fSpeed;
	m_fAlpha = _fAlpha;
	m_bBlack = _bBlack;

	m_eState = CameraState::FadeIn;
}

void Camera::Set_FadeOut(const float& _fSpeed, const float& _fAlpha, bool _bBlack)
{
	m_fFadeSpeed = _fSpeed;
	m_fAlpha = _fAlpha;
	m_bBlack = _bBlack;

	m_eState = CameraState::FadeOut;
}

void Camera::Normal_State()
{
	if (m_pTarget != nullptr)
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_vLookAt = Lerp(m_vLookAt, vTargetPos, 0.5f);
		//m_vLookAt = m_pTarget->GetPos();
	}
}

void Camera::Shaking()
{
	static float fNowTime = 0.f;

	if (m_pTarget != nullptr)
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_vLookAt = Lerp(m_vLookAt, vTargetPos, 0.5f);
	}

	fNowTime += TimeMgr::DeltaTime_NoScale();

	if (fNowTime >= m_fShakingTime)
	{
		fNowTime = 0.f;
		m_eState = CameraState::Normal;
		if (m_pTarget == nullptr)
		{
			m_vLookAt = m_vOriginPos;
		}
		return;
	}

	float fTheta = float(rand() % 360);
	float fRadian = fTheta * 3.141592f / 180.f;

	Vec2 vRandPos = Vec2(cosf(fRadian), sinf(fRadian));

	m_vLookAt += vRandPos * m_fIntensity;
}

void Camera::FadeIn()
{
	m_fAlpha -= m_fFadeSpeed * TimeMgr::DeltaTime_NoScale();
	if (m_fAlpha < 0.f)
		m_eState = CameraState::Normal;
	
}

void Camera::FadeOut()
{
	m_fAlpha += m_fFadeSpeed * TimeMgr::DeltaTime_NoScale();
	if (m_fAlpha > 1.f)
		m_eState = CameraState::Normal;
}
