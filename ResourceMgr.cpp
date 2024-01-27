#include "ResourceMgr.h"

map<wstring, JoResource*> ResourceMgr::m_resources{};


void ResourceMgr::Initialize()
{
	//ResourceMgr::Load<JoTexture>(L"BG_Chew1", L"Resources/Map/Chew/Chew1.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew2", L"Resources/Map/Chew/Chew2.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew3", L"Resources/Map/Chew/Chew3.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew4", L"Resources/Map/Chew/Chew4.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew5", L"Resources/Map/Chew/Chew5.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew6", L"Resources/Map/Chew/Chew6.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew7", L"Resources/Map/Chew/Chew7.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew8", L"Resources/Map/Chew/Chew8.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew9", L"Resources/Map/Chew/Chew9.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew10", L"Resources/Map/Chew/Chew10.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew11", L"Resources/Map/Chew/Chew11.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew12", L"Resources/Map/Chew/Chew12.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew13", L"Resources/Map/Chew/Chew13.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew14", L"Resources/Map/Chew/Chew14.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew15", L"Resources/Map/Chew/Chew15.png");
	//ResourceMgr::Load<JoTexture>(L"BG_Chew16", L"Resources/Map/Chew/Chew16.png");

	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot1", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot1.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot2", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot2.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot3", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot3.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot4", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot4.png");
	ResourceMgr::Load<JoBmp>(L"GiantRoot_Pixel", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot_Pixel.bmp");

	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave1", L"Resources/Map/AbyssCave/심연의동굴1.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave2", L"Resources/Map/AbyssCave/심연의동굴2.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave3", L"Resources/Map/AbyssCave/심연의동굴3.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave4", L"Resources/Map/AbyssCave/심연의동굴4.png");
	ResourceMgr::Load<JoTexture>(L"AbyssCave_Minimap", L"Resources/Map/AbyssCave/AbyssCave_Minimap.png");
	ResourceMgr::Load<JoBmp>(L"AbyssCave_Pixel", L"Resources/Map/AbyssCave/AbyssCave_Pixel.bmp");

	ResourceMgr::Load<JoTexture>(L"의문의 소녀", L"Resources/Npc/소녀.png");
	ResourceMgr::Load<JoTexture>(L"의문의 소녀_이름", L"Resources/UI/Dialog/DialogName_Girl.png");
	ResourceMgr::Load<JoTexture>(L"의문의 소녀_대화", L"Resources/UI/Dialog/Dialog_Girl.png");
	ResourceMgr::Load<JoTexture>(L"오코", L"Resources/Npc/오코.png");

	ResourceMgr::Load<JoTexture>(L"PhantomBlow", L"Resources/Skill/PhantomBlow/phantomblow.png");
	ResourceMgr::Load<JoTexture>(L"PB_Hit", L"Resources/Skill/PhantomBlow/phantomblow_hit.png");
	ResourceMgr::Load<JoTexture>(L"KarmaFury", L"Resources/Skill/KarmaFury/karma_fury.png");
	ResourceMgr::Load<JoTexture>(L"KF_Hit", L"Resources/Skill/KarmaFury/kf_hit.png");
	ResourceMgr::Load<JoTexture>(L"BladeTornado_Create", L"Resources/Skill/BladeTornado/bladeTornado_create.png");
	ResourceMgr::Load<JoTexture>(L"BladeTornado_Loop", L"Resources/Skill/BladeTornado/bladeTornado_loop.png");
	ResourceMgr::Load<JoTexture>(L"BT_Hit", L"Resources/Skill/BladeTornado/BT_Hit.png");
	ResourceMgr::Load<JoTexture>(L"BladeStorm_L", L"Resources/Skill/BladeStorm/BladeStorm_L.png");
	ResourceMgr::Load<JoTexture>(L"BladeStorm_R", L"Resources/Skill/BladeStorm/BladeStorm_R.png");
	ResourceMgr::Load<JoTexture>(L"BS_Hit", L"Resources/Skill/BladeStorm/BS_Hit.png");
	ResourceMgr::Load<JoTexture>(L"Asura_Loop", L"Resources/Skill/Asura/Asura.png");
	ResourceMgr::Load<JoTexture>(L"Asura_Bottom", L"Resources/Skill/Asura/AS_Bottom.png");
	ResourceMgr::Load<JoTexture>(L"AS_Hit", L"Resources/Skill/Asura/AS_Hit.png");

	ResourceMgr::Load<JoTexture>(L"FlashJump", L"Resources/Skill/FlashJump/FlashJump.png");

	ResourceMgr::Load<JoTexture>(L"Cursor", L"Resources/UI/Cursor.png");
	ResourceMgr::Load<JoTexture>(L"ShopUI", L"Resources/UI/Shop/ShopUI.png");
	ResourceMgr::Load<JoTexture>(L"플레이어_선택", L"Resources/UI/Shop/Shop_Selected.png");
	ResourceMgr::Load<JoTexture>(L"상인_선택", L"Resources/UI/Shop/Shop_Selected_상인.png");
	ResourceMgr::Load<JoTexture>(L"Shop_Tab", L"Resources/UI/Shop/Shop_Tab.png");
	ResourceMgr::Load<JoTexture>(L"Item_Number", L"Resources/UI/Item_Num.png");
	ResourceMgr::Load<JoTexture>(L"TitleScreen", L"Resources/TitleScreen.png");
	ResourceMgr::Load<JoTexture>(L"Title_Button", L"Resources/Title_Button.png");
	ResourceMgr::Load<JoTexture>(L"Title_Button_On", L"Resources/Title_Button_On.png");
	ResourceMgr::Load<JoTexture>(L"MiniMap_Player", L"Resources/UI/MiniMap_Player.png");
	ResourceMgr::Load<JoTexture>(L"Portal", L"Resources/Map/Portal/Portal.png");

	ResourceMgr::Load<JoTexture>(L"Damage_Num", L"Resources/UI/DamageNum/damage_num.png");
	ResourceMgr::Load<JoTexture>(L"Damage_Num_Critical", L"Resources/UI/DamageNum/damage_num_critical.png");
	ResourceMgr::Load<JoTexture>(L"Damaged_Num", L"Resources/UI/DamageNum/damaged_num.png");

	ResourceMgr::Load<JoTexture>(L"StunEffect", L"Resources/Effect/StunEffect.png");
	ResourceMgr::Load<JoTexture>(L"Player", L"Resources/Player/Player.png");

	ResourceMgr::Load<JoTexture>(L"Tomb", L"Resources/Obj/Tomb.png");

	ResourceMgr::Load<JoTexture>(L"Vellum_Appear_L", L"Resources/Enemy/Vellum/Vellum_Appear.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Appear_R", L"Resources/Enemy/Vellum/Vellum_Appear_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack1_L", L"Resources/Enemy/Vellum/Vellum_Attack1.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack1_R", L"Resources/Enemy/Vellum/Vellum_Attack1_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack2_L", L"Resources/Enemy/Vellum/Vellum_Attack2.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack2_R", L"Resources/Enemy/Vellum/Vellum_Attack2_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack3_L", L"Resources/Enemy/Vellum/Vellum_Attack3.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack3_R", L"Resources/Enemy/Vellum/Vellum_Attack3_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack3_R", L"Resources/Enemy/Vellum/Vellum_Attack3_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack4_L", L"Resources/Enemy/Vellum/Vellum_Attack4.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Attack4_R", L"Resources/Enemy/Vellum/Vellum_Attack4_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Start_L", L"Resources/Enemy/Vellum/Vellum_Breath.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Start_R", L"Resources/Enemy/Vellum/Vellum_Breath_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Loop_L", L"Resources/Enemy/Vellum/Vellum_Breath_Loop.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Loop_R", L"Resources/Enemy/Vellum/Vellum_Breath_Loop_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Loop_End_L", L"Resources/Enemy/Vellum/Vellum_Breath_Loop_End.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_Loop_End_R", L"Resources/Enemy/Vellum/Vellum_Breath_Loop_End_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Dig_L", L"Resources/Enemy/Vellum/Vellum_Dig.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Dig_R", L"Resources/Enemy/Vellum/Vellum_Dig_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_LowNeck_L", L"Resources/Enemy/Vellum/Vellum_LowNeck.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_LowNeck_R", L"Resources/Enemy/Vellum/Vellum_LowNeck_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Die_L", L"Resources/Enemy/Vellum/Vellum_Die.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Die_R", L"Resources/Enemy/Vellum/Vellum_Die_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Move", L"Resources/Enemy/Vellum/Vellum_Move.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Stone", L"Resources/Enemy/Vellum/Vellum_Stone.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Stone_End", L"Resources/Enemy/Vellum/Vellum_Stone_End.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_L", L"Resources/Enemy/Vellum/Breath_L.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_R", L"Resources/Enemy/Vellum/Breath_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_End_L", L"Resources/Enemy/Vellum/Breath_End_L.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Breath_End_R", L"Resources/Enemy/Vellum/Breath_End_R.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Tail_L", L"Resources/Enemy/Vellum/Vellum_Tail_L.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Tail_R", L"Resources/Enemy/Vellum/Vellum_Tail_R.png");

	ResourceMgr::Load<JoTexture>(L"Vellum_HpBar", L"Resources/UI/Boss/Vellum_HpBar.png");
	ResourceMgr::Load<JoTexture>(L"Boss_Hp", L"Resources/UI/Boss/bossHP.png");
	ResourceMgr::Load<JoTexture>(L"Breath_Text", L"Resources/UI/Boss/Breath_Text.png");
}

void ResourceMgr::Release()
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		Safe_Delete<JoResource*>(it->second);
	}

	m_resources.clear();
}
