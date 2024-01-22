#include "Player.h"
#include "RenderMgr.h"
#include "MainCamera.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"
#include "SkillStats.h"
#include "PlayerStats.h"
#include "UIMgr.h"
#include "SkillUI.h"
#include "QuickSlotUI.h"
#include "QuickStats.h"
#include "Skill.h"
#include "FJ_Obj.h"
#include "joObject.h"
#include "SoundMgr.h"
#include "Inventory.h"
#include "InvenUI.h"
#include "EquipStats.h"
#include "EquipUI.h"
#include "ItemDatabase.h"
#include "StatUI.h"
#include "ShopUI.h"
#include "Consumable.h"

Player::Player()
	: m_bDownJumping(false)
	, m_eState(PlayerState::Air)
	, m_pixelDC(nullptr)
	, m_bRight(true)
	, m_ArrKeyAction{}
	, m_fMoveSpeed(250.f)
	, m_fJumpVelocity(-420.f)
	, m_bFlashJumping(false)
	, m_vLimitPosX{}
	, m_pSkillStats(nullptr)
	, m_pPlayerStats(nullptr)
	, m_pQuickStats(nullptr)
	, m_cRestriction(0)
	, m_bChannelingIdle(false)
	, m_bChannelingWalk(false)
	, m_bChannelingAir(false)
	, m_pInventory(nullptr)
	, m_pEquipStats(nullptr)
{

}

Player::~Player()  
{
	Release();
}

void Player::Initialize()
{
	Skill::SetOwner(this);

	m_pSkillStats = new SkillStats;
	UIMgr::Get_UI_Instance<SkillUI>(UI_Enums::UI_Skill)->SetSkillStats(m_pSkillStats);

	m_pPlayerStats = new PlayerStats;
	UIMgr::Get_UI_Instance<StatUI>(UI_Enums::UI_Stat)->SetPlayerStats(m_pPlayerStats);

	m_pQuickStats = new QuickStats;
	UIMgr::Get_UI_Instance<QuickSlotUI>(UI_Enums::UI_QuickSlot)->SetQuickStats(m_pQuickStats);

	m_pInventory = new Inventory;
	UIMgr::Get_UI_Instance<InvenUI>(UI_Enums::UI_Inven)->SetInventory(m_pInventory);

	m_pEquipStats = new EquipStats;
	UIMgr::Get_UI_Instance<EquipUI>(UI_Enums::UI_Equip)->SetEquipStats(m_pEquipStats);
	m_pEquipStats->Set_PlayerStats(m_pPlayerStats);

	UIMgr::Get_UI_Instance<ShopUI>(UI_Enums::UI_Shop)->Set_Inventory(m_pInventory);
	Consumable::SetPlayerStats(m_pPlayerStats);

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(20.f, 50.f));

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetGravity(Vec2(0.f, 1200.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_ArrKeyAction[(UINT)eActionKey::Right] = eKeyCode::Right;
	m_ArrKeyAction[(UINT)eActionKey::Left] = eKeyCode::Left;
	m_ArrKeyAction[(UINT)eActionKey::Up] = eKeyCode::Up;
	m_ArrKeyAction[(UINT)eActionKey::Down] = eKeyCode::Down;
	m_ArrKeyAction[(UINT)eActionKey::Jump] = eKeyCode::Space;

	Init_Anim();
	Init_FrameBind();

	m_pAnimator->PlayAnimation(L"Air_R");
}

void Player::Update()
{
	debug_check();

	if (m_bDownJumping)
	{
		m_tDownJumpTimer.m_fNowTime += TimeMgr::DeltaTime();
		if (m_tDownJumpTimer.m_fNowTime >= 0.3f)
		{
			m_bDownJumping = false;
			m_tDownJumpTimer.m_fNowTime = 0.f;
		}
	}

	m_pQuickStats->Key_Check();

	switch (m_eState)
	{
	case Player::PlayerState::Idle:
		Idle_State();
		break;
	case Player::PlayerState::Walk:
		Walk_State();
		break;
	case Player::PlayerState::Air:
		Air_State();
		break;
	case Player::PlayerState::Prone:
		Prone_State();
		break;
	case Player::PlayerState::Rope:
		Rope_State();
		break;
	case Player::PlayerState::Channeling:
		Channeling_State();
		break;
	default:
		break;
	}

	m_pRigidbody->Update();


	if (PlayerState::Rope != m_eState)
	{
		CheckGround();
		CheckYellowGround();
	}
		
	m_pAnimator->Update();

	/*if (RGB(0, 0, 255) == GetPixel(m_pixelDC, (int)(GetPos().x - 11.f), int(GetPos().y))
		&& m_pRigidbody->GetVelocity().x < 0.f)
	{
		while (RGB(0, 0, 255) == GetPixel(m_pixelDC, (int)(GetPos().x - 11.f), int(GetPos().y)))
		{
			m_pRigidbody->SetVelocityX(0.f);
			m_tTransform.vPos.x += 1.f;
		}
	}

	if (RGB(0, 0, 255) == GetPixel(m_pixelDC, (int)(GetPos().x + 11.f), int(GetPos().y))
		&& m_pRigidbody->GetVelocity().x > 0.f)
	{
		while (RGB(0, 0, 255) == GetPixel(m_pixelDC, (int)GetPos().x + 11.f, int(GetPos().y)))
		{
			m_pRigidbody->SetVelocityX(0.f);
			m_tTransform.vPos.x -= 1.f;
		}
	}*/
	

	m_tTransform.vPos.x = clamp(m_tTransform.vPos.x, m_vLimitPosX.x, m_vLimitPosX.y);
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void Player::Release()
{
	Safe_Delete<SkillStats*>(m_pSkillStats);
	Safe_Delete<PlayerStats*>(m_pPlayerStats);
	Safe_Delete<QuickStats*>(m_pQuickStats);
	Safe_Delete<Inventory*>(m_pInventory);
	Safe_Delete<EquipStats*>(m_pEquipStats);
}

void Player::Init_Anim()
{
	JoTexture* playerTex = ResourceMgr::Find<JoTexture>(L"Player");
	m_pAnimator->CreateAnimation(L"Idle_L", playerTex, Vec2(0.0f, 0.0f), Vec2(160.f, 160.f), Vec2::Zero, 4, 0.5f);
	m_pAnimator->CreateAnimation(L"Idle_R", playerTex, Vec2(0.0f, 640.0f), Vec2(160.f, 160.f), Vec2::Zero, 4, 0.5f);
	m_pAnimator->CreateAnimation(L"Walk_L", playerTex, Vec2(640.0f, 0.0f), Vec2(160.f, 160.f), Vec2::Zero, 3, 0.3f);
	m_pAnimator->CreateAnimation(L"Walk_R", playerTex, Vec2(640.0f, 640.0f), Vec2(160.f, 160.f), Vec2::Zero, 4, 0.3f);
	m_pAnimator->CreateAnimation(L"Air_L", playerTex, Vec2(480.0f, 480.0f), Vec2(160.f, 160.f), Vec2::Zero, 1);
	m_pAnimator->CreateAnimation(L"Air_R", playerTex, Vec2(160.0f, 800.0f), Vec2(160.f, 160.f), Vec2::Zero, 1);
	m_pAnimator->CreateAnimation(L"Rope_Pause", playerTex, Vec2(1280.f, 0.f), Vec2(160.f, 160.f), Vec2::Zero, 1);
	m_pAnimator->CreateAnimation(L"Rope_Loop", playerTex, Vec2(1280.f, 0.f), Vec2(160.f, 160.f), Vec2::Zero, 2, 0.3f);
	m_pAnimator->CreateAnimation(L"Prone_L", playerTex, Vec2(640.f, 480.f), Vec2(160.f, 160.f), Vec2::Zero, 1);
	m_pAnimator->CreateAnimation(L"Prone_R", playerTex, Vec2(800.f, 480.f), Vec2(160.f, 160.f), Vec2::Zero, 1);
	m_pAnimator->CreateAnimation(L"PhantomBlow_L", playerTex, Vec2(0.0f, 160.0f), Vec2(160.f, 160.f), Vec2::Zero, 8, 0.09f);
	m_pAnimator->CreateAnimation(L"PhantomBlow_R", playerTex, Vec2(360.f, 800.0f), Vec2(160.f, 160.f), Vec2(30.f, 0.f), 8, 0.09f);
}

void Player::Init_FrameBind()
{
	function<void()> skillEnd = bind(&Player::Skill_End, this);
	m_pAnimator->GetEvents(L"PhantomBlow_L")->frameEvents[7] = skillEnd;
	m_pAnimator->GetEvents(L"PhantomBlow_R")->frameEvents[7] = skillEnd;
}

void Player::Idle_State()
{
	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Left]))
	{
		m_bRight = false;
		SetState_Walk();
	}
	else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Right]))
	{
		m_bRight = true;
		SetState_Walk();
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
	{
		Jump();
		SetState_Air();
	}

	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Up]))
	{
		if (CheckRope(true))
			SetState_Rope();
	}
	else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		if (CheckRope(false))
			SetState_Rope();
		else
			SetState_Prone();
	}
}

void Player::Walk_State()
{
	if (KeyMgr::GetKeyNone(m_ArrKeyAction[(UINT)eActionKey::Right]) && 
		KeyMgr::GetKeyNone(m_ArrKeyAction[(UINT)eActionKey::Left]))
	{
		SetState_Idle();
		return;
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Left]))
	{
		m_bRight = false;
		m_pRigidbody->SetVelocity(Vec2(-m_fMoveSpeed, 0.0f));
		m_pAnimator->PlayAnimation(L"Walk_L", true);
	}
	else if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Right]))
	{
		m_bRight = true;
		m_pRigidbody->SetVelocity(Vec2(m_fMoveSpeed, 0.0f));
		m_pAnimator->PlayAnimation(L"Walk_R", true);
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
	{
		Jump();
		SetState_Air();
	}

	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Up]))
	{
		if (CheckRope(true))
			SetState_Rope();
	}
	else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		if (CheckRope(false))
			SetState_Rope();
		else
			SetState_Prone();
	}
}

void Player::Air_State()
{
	if (!m_bFlashJumping)
	{
		Vec2 vVelocity = m_pRigidbody->GetVelocity();
		if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Left]) && m_bRight)
		{
			//m_bRight = false;
			vVelocity.x = max(vVelocity.x - m_fMoveSpeed * TimeMgr::DeltaTime(), 0.0f);
		}
		else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Right]) && !m_bRight)
		{
			//m_bRight = true;
			vVelocity.x = min(vVelocity.x + m_fMoveSpeed * TimeMgr::DeltaTime(), 0.0f);
		}
		m_pRigidbody->SetVelocity(vVelocity);
	}
	


	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Up]))
	{
		if (CheckRope(true))
			SetState_Rope();
	}
	else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		if (CheckRope(false))
			SetState_Rope();
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
	{
		if (!m_bFlashJumping)
		{
			FlashJump();
		}
	}
}

void Player::Rope_State()
{
	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Up]))
	{
		m_pAnimator->PlayAnimation(L"Rope_Loop", true);
		m_pRigidbody->SetVelocityY(-200.f);

		if (m_ColorRope != GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f + 1.f))
			&& m_ColorRope != GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y - m_pCollider->GetSize().y * 0.5f - 1.f)))
		{
			m_pRigidbody->SetUseGravity(true);
			SetState_Idle();
		}
	}
	else if (KeyMgr::GetKeyUp(m_ArrKeyAction[(UINT)eActionKey::Up]))
	{
		m_pAnimator->PlayAnimation(L"Rope_Pause", true);
		m_pRigidbody->SetVelocity(Vec2::Zero);
	}

	if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		m_pAnimator->PlayAnimation(L"Rope_Loop", true);
		m_pRigidbody->SetVelocityY(200.f);

		if (m_ColorRope != GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f + 8.f))
			&& m_ColorRope != GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y - m_pCollider->GetSize().y * 0.5f - 1.f)))
		{
			m_pRigidbody->SetUseGravity(true);
			SetState_Air();
		}
	}
	else if (KeyMgr::GetKeyUp(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		m_pAnimator->PlayAnimation(L"Rope_Pause", true);
		m_pRigidbody->SetVelocity(Vec2::Zero);
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
	{
		if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Right]))
		{
			m_bRight = true;
			m_pRigidbody->SetVelocityX(m_fMoveSpeed);
		}
		else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Left]))
		{
			m_bRight = false;
			m_pRigidbody->SetVelocityX(-m_fMoveSpeed);
		}
		Jump();
		SetState_Air();
	}
}

void Player::Prone_State()
{
	if (KeyMgr::GetKeyUp(m_ArrKeyAction[(UINT)eActionKey::Down]))
	{
		SetState_Idle();
	}

	if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
	{
		if (m_pRigidbody->IsGround())
		{
			m_bDownJumping = true;
			m_pRigidbody->SetGround(false);
			m_pRigidbody->SetVelocityY(-100.f);
			SetState_Air();
		}
	}
	
}

void Player::Channeling_State()
{
	if (!(m_cRestriction & 1) && m_pRigidbody->IsGround())
	{
		if (KeyMgr::GetKeyNone(m_ArrKeyAction[(UINT)eActionKey::Right]) &&
			KeyMgr::GetKeyNone(m_ArrKeyAction[(UINT)eActionKey::Left]))
		{
			m_bChannelingWalk = false;
			m_pRigidbody->SetVelocity(Vec2(0.0f, 0.0f));
		}
		if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Left]))
		{
			m_bChannelingWalk = true;
			m_bRight = false;
			m_pRigidbody->SetVelocity(Vec2(-m_fMoveSpeed, 0.0f));
		}
		else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Right]))
		{
			m_bRight = true;
			m_bChannelingWalk = true;
			m_pRigidbody->SetVelocity(Vec2(m_fMoveSpeed, 0.0f));
		}
	}
	
	if (!(m_cRestriction & (1 << 1)))
	{
		if (KeyMgr::GetKeyDown(m_ArrKeyAction[(UINT)eActionKey::Jump]))
		{
			if (m_pRigidbody->IsGround())
			{
				Jump();
			}
				
			else if (!m_bFlashJumping)
			{
				FlashJump();
			}
		}
	}

	if (m_pRigidbody->IsGround() && m_pRigidbody->GetVelocity().y > 0.f)
		m_pRigidbody->SetVelocity(Vec2::Zero);

}

void Player::SetState_Idle()
{
	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Idle_R", true);
	else
		m_pAnimator->PlayAnimation(L"Idle_L", true);
	

	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_eState = PlayerState::Idle;
}

void Player::SetState_Walk()
{
	if (m_bRight)
	{
		m_pAnimator->PlayAnimation(L"Walk_R");
		m_pRigidbody->SetVelocityX(m_fMoveSpeed);
	}
	else
	{
		m_pAnimator->PlayAnimation(L"Walk_L");
		m_pRigidbody->SetVelocityX(-m_fMoveSpeed);
	}

	m_eState = PlayerState::Walk;
}

void Player::SetState_Air()
{
	if (PlayerState::Air == m_eState) return;

	if (m_bRight)
	{
		m_pAnimator->PlayAnimation(L"Air_R");
	}
	else
	{
		m_pAnimator->PlayAnimation(L"Air_L");
	}
	
	m_bFlashJumping = false;
	m_eState = PlayerState::Air;
} 

void Player::SetState_Rope()
{
	// PlayAnimation

	m_pAnimator->PlayAnimation(L"Rope_Pause");

	m_eState = PlayerState::Rope;
}

void Player::SetState_Prone()
{
	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Prone_R");
	else
		m_pAnimator->PlayAnimation(L"Prone_L");

	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_eState = PlayerState::Prone;
}

void Player::SetState_Channeling(const unsigned char& _cRestriction)
{
	m_cRestriction = _cRestriction;

	m_bChannelingIdle = true;
	m_eState = PlayerState::Channeling;
}

void Player::Jump()
{
	SoundMgr::Play(L"Player_Jump");
	m_pRigidbody->SetVelocityY(m_fJumpVelocity);
	m_pRigidbody->SetUseGravity(true);
	m_pRigidbody->SetGround(false);
}

void Player::FlashJump()
{
	auto fj = Instantiate<FJ_Obj>(eLayerType::LT_EFFECT);
	fj->SetOwner(this);
	fj->Skill_Start();

	float fXDir = {};
	m_bFlashJumping = true;

	if (m_bRight) fXDir = 1.f;
	else fXDir = -1.f;

	Vec2 vVelocity = m_pRigidbody->GetVelocity();
	vVelocity.y -= 100.0f;
	vVelocity.x = fXDir * (abs(vVelocity.x) + 400.0f);
	m_pRigidbody->SetVelocity(vVelocity);
}

bool Player::CheckRope(const bool& _bCheckUp)
{
	// UpÅ°¸¦ ´­·¶À»¶§ ·ÎÇÁ Ã¼Å©
	if (_bCheckUp)
	{
		if (m_ColorRope == GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y)))
		{
			m_pRigidbody->SetVelocity(Vec2::Zero);
			m_pRigidbody->SetUseGravity(false);
			return true;
		}
	}
	// DownÅ°
	else
	{
		if (m_pRigidbody->IsGround() && 
			m_ColorRope == GetPixel(m_pixelDC, int(GetPos().x), int(GetPos().y + m_pCollider->GetSize().y * 0.5f + 10.f)))
		{
			m_pRigidbody->SetVelocity(Vec2::Zero);
			m_pRigidbody->SetGround(false);
			m_pRigidbody->SetUseGravity(false);
			return true;
		}
	}
	return false;
}

void Player::CheckGround()
{
	if (m_ColorGround == GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f + 1.f)))
	{
		if (m_pRigidbody->IsGround() || m_bDownJumping || m_pRigidbody->GetVelocity().y < 0.f)
			return;

		m_bMagenta = true;
		m_pRigidbody->SetGround(true);
		while (m_ColorGround == GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f)))
		{
			m_tTransform.vPos.y -= 1.f;
		}
		m_bFlashJumping = false;

		if (m_eState != PlayerState::Channeling)
			SetState_Idle();
	}
	else
	{
		m_bMagenta = false;
	}
}

void Player::CheckYellowGround()
{
	if (m_bMagenta) return;

	if (m_eState == PlayerState::Walk || m_bChannelingWalk)
	{
		float fCheckStart = GetPos().y - m_pCollider->GetSize().y * 0.5f;
		float fCheckEnd = GetPos().y + m_pCollider->GetSize().y * 0.5f + 20.f;

		while (fCheckStart <= fCheckEnd)
		{
			if (m_ColorYellow == GetPixel(m_pixelDC, (int)GetPos().x, (int)fCheckStart))
			{
				m_pRigidbody->SetGround(true);
				m_tTransform.vPos.y = fCheckStart - m_pCollider->GetSize().y * 0.5f - 1.f;
				return;
			}
			fCheckStart += 1.0f;
		}
		m_pRigidbody->SetGround(false);
		if (m_eState != PlayerState::Channeling)
			SetState_Air();
		return;
	}


	if (m_ColorYellow == GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f + 1.f)))
	{
		if (m_pRigidbody->IsGround() || m_bDownJumping || m_pRigidbody->GetVelocity().y < 0.f)
			return;

		m_pRigidbody->SetGround(true);
		while (m_ColorYellow == GetPixel(m_pixelDC, (int)GetPos().x, int(GetPos().y + m_pCollider->GetSize().y * 0.5f)))
		{
			m_tTransform.vPos.y -= 1.f;
		}
		m_bFlashJumping = false;
		if (m_eState != PlayerState::Channeling)
			SetState_Idle();
	}
	else if (!m_bMagenta)
	{
		m_pRigidbody->SetGround(false);
		if (m_eState != PlayerState::Channeling)
			SetState_Air();
	}
}

void Player::Skill_End()
{
	if (m_pRigidbody->IsGround())
	{
		if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Left]))
		{
			m_bRight = false;
			SetState_Walk();
		}
		else if (KeyMgr::GetKey(m_ArrKeyAction[(UINT)eActionKey::Right]))
		{
			m_bRight = true;
			SetState_Walk();
		}
		else
			SetState_Idle();
	}
		
	else
		SetState_Air();

	m_bChannelingIdle = false;
	m_bChannelingWalk = false;
	m_bChannelingAir = false;
	m_cRestriction = 0;

	m_fMoveSpeed = 250.f;
}

void Player::debug_check()
{
	if (KeyMgr::GetKeyDown(eKeyCode::NUMPAD0))
	{
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"¿¡Å×¸£³Ú ½ÃÇÁ¹Ý´Ù³ª"), 1);
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"¿¡Å×¸£³Ú ½ÃÇÁ¼ÅÃ÷"), 1);
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"¿¡Å×¸£³Ú ½ÃÇÁÆÒÃ÷"), 1);
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"¾ÆÄÉÀÎ¼ÎÀÌµå ½ÃÇÁ½´Áî"), 1);
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"¸®¹ö½º Æä½ºÄ«Áî"), 1);
		m_pInventory->Insert_Item(ItemDatabase::FindItemData(L"ÆÄ¿ö ¿¤¸¯¼­"), 10);
	}

	if (KeyMgr::GetKeyDown(eKeyCode::N))
		SetPos({ 300, 200 });
}

