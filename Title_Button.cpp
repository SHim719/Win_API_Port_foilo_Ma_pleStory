#include "Title_Button.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"


Title_Button::Title_Button()
{
}

Title_Button::~Title_Button()
{
}

void Title_Button::Initialize()
{
	m_pButtonTex = ResourceMgr::Find<JoTexture>(L"Title_Button");
	m_pOnButtonTex = ResourceMgr::Find<JoTexture>(L"Title_Button_On");

}

void Title_Button::Press_Button()
{
	SceneMgr::Reservation_ChangeScene(L"Scene_Rutabyss", { 137.f, 117.f });
}
