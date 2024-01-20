#include "ResourceMgr.h"

map<wstring, JoResource*> ResourceMgr::m_resources{};


void ResourceMgr::Initialize()
{
	ResourceMgr::Load<JoTexture>(L"BG_Chew1", L"Resources/Map/Chew/Chew1.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew2", L"Resources/Map/Chew/Chew2.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew3", L"Resources/Map/Chew/Chew3.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew4", L"Resources/Map/Chew/Chew4.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew5", L"Resources/Map/Chew/Chew5.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew6", L"Resources/Map/Chew/Chew6.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew7", L"Resources/Map/Chew/Chew7.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew8", L"Resources/Map/Chew/Chew8.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew9", L"Resources/Map/Chew/Chew9.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew10", L"Resources/Map/Chew/Chew10.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew11", L"Resources/Map/Chew/Chew11.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew12", L"Resources/Map/Chew/Chew12.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew13", L"Resources/Map/Chew/Chew13.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew14", L"Resources/Map/Chew/Chew14.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew15", L"Resources/Map/Chew/Chew15.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew16", L"Resources/Map/Chew/Chew16.png");

	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot1", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot1.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot2", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot2.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot3", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot3.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot4", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot4.png");
	ResourceMgr::Load<JoBmp>(L"GiantRoot_Pixel", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot_Pixel.bmp");


	ResourceMgr::Load<JoTexture>(L"PhantomBlow", L"Resources/Skill/PhantomBlow/phantomblow.png");
	ResourceMgr::Load<JoTexture>(L"PB_Hit", L"Resources/Skill/PhantomBlow/phantomblow_hit.png");

	ResourceMgr::Load<JoTexture>(L"FlashJump", L"Resources/Skill/FlashJump/FlashJump.png");

	ResourceMgr::Load<JoTexture>(L"Cursor", L"Resources/UI/Cursor.png");

	ResourceMgr::Load<JoTexture>(L"Player", L"Resources/Player/Player.png");
}

void ResourceMgr::Release()
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		Safe_Delete<JoResource*>(it->second);
	}

	m_resources.clear();
}
