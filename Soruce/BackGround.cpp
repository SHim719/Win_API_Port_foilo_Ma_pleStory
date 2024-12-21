#include "BackGround.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "MainGame.h"

BackGround::BackGround()
	: m_pBgTexture(nullptr)
{
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
}

void BackGround::Update()
{
}

void BackGround::LateUpdate()
{
}

void BackGround::Render()
{
	float fWidth = Camera::GetCameraSize().x;
	float fHeight = Camera::GetCameraSize().y;

	Vec2 vLookAt = Camera::GetLookAt();

	Vec2 vLeftTop = {};
	vLeftTop.x = vLookAt.x - fWidth * 0.5f;
	vLeftTop.y = vLookAt.y - fHeight * 0.5f;

	Vec2 vRightBottom = {};
	vRightBottom.x = vLookAt.x + fWidth * 0.5f;
	vRightBottom.y = vLookAt.y + fHeight * 0.5f;


	RenderMgr::RenderFrame(m_pBgTexture,
		0, 0, fWidth, fHeight,
		vLeftTop.x, vLeftTop.y,
		vRightBottom.x, vRightBottom.y
	);
}
