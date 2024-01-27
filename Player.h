#pragma once
#include "GameObject.h"
#include "KeyMgr.h"
#include "HitInterface.h"

enum class Restriction
{
	NoJump,
	NoMove,
};


class SkillStats;
class PlayerStats;
class QuickStats;
class Inventory;
class EquipStats;

class Player :
    public GameObject, public HitInterface
{
	enum class eActionKey
	{
		Right,
		Left,
		Up,
		Down,
		Jump,
		End,
	};

public:
	enum class PlayerState
	{
		Idle,
		Walk,
		Air,
		Prone,
		Rope,
		Channeling,
		Stun,
		Dead,
		End,
	};

    Player();
    ~Player();

public:
	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;

	void SetPixelDC(HDC _dc) { m_pixelDC = _dc; }

	void SetLimitPosX(const Vec2& _v) { m_vLimitPosX = _v; }
	
	const PlayerState& GetPlayerState() const { return m_eState; }

	PlayerStats* GetPlayerStats() const { return m_pPlayerStats; }
	SkillStats* GetSkillStats() const { return m_pSkillStats; }

	void SetState_Channeling(const unsigned char& _cRestriction);
	void SetState_Stun();
	void Skill_End();

	const bool& isRight() const { return m_bRight; }
	bool isStunning() const { return m_eState == PlayerState::Stun; }
	bool isDeadState() const { return m_eState == PlayerState::Dead; }
	bool isChanneling() const { return m_eState == PlayerState::Channeling;}

	void Hit(const HitInfo& _hitInfo) override;

	void Revive();
private:
	void Init_Anim();
	void Init_FrameBind();

	void Idle_State();
	void Walk_State();
	void Air_State();
	void Rope_State();
	void Prone_State();
	void Channeling_State();
	void Stun_State();
	void Dead_State();

	void SetState_Idle();
	void SetState_Walk();
	void SetState_Air();
	void SetState_Rope();
	void SetState_Prone();
	void SetState_Dead();

	void Jump();
	void FlashJump();

	bool CheckRope(const bool& _bCheckUp);
	void CheckGround();
	void CheckYellowGround();
	
	void Invincible();

	void debug_check();
private:
	PlayerStats* m_pPlayerStats;
	SkillStats* m_pSkillStats;
	QuickStats* m_pQuickStats;
	Inventory* m_pInventory;
	EquipStats* m_pEquipStats;

private:
	bool m_bDownJumping;
	Timer m_tDownJumpTimer;

	bool m_bFlashJumping;

	bool m_bRight;
	float m_fMoveSpeed;
	float m_fJumpVelocity;
	Vec2 m_vLimitPosX;

	bool m_bMagenta = false;
	bool m_bYellow = false;

	bool m_bChannelingIdle;
	bool m_bChannelingWalk;
	bool m_bChannelingAir;

	bool m_bInvincible;
	float m_fInvincibleTime;

	PlayerState m_eState;
	unsigned char m_cRestriction;
	HDC m_pixelDC;

	eKeyCode m_ArrKeyAction[(UINT)eActionKey::End];

	COLORREF m_ColorGround = RGB(255, 0, 255);
	COLORREF m_ColorRope = RGB(255, 0, 0);
	COLORREF m_ColorYellow = RGB(255, 255, 0);

	Vec2 m_vOriginPos;
};

