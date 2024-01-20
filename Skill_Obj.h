#pragma once
#include "GameObject.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SoundMgr.h"

struct HitTimer
{
	float fPrevTime = 0.f;
	float fNowTime = 0.f;

	bool Time_Elapsed(float _fGap)
	{
		if (fNowTime - fPrevTime >= _fGap)
		{
			fPrevTime = fNowTime;
			return true;
		}
		return false;
	}
};

struct HitInfo
{
	GameObject* pObj = nullptr;
	vector<Vec2> m_vecEffectPos = {};
	HitTimer tTimer{};
	int iHitCount = 0;
};

class Skill_Obj :
    public GameObject
{
public:
    Skill_Obj();
    ~Skill_Obj();

    virtual void Skill_Start() PURE;
    void SetOwner(Player* _pPlayer) { m_pOwner = _pPlayer; }
    void SetSkillTex(JoTexture* const _pSkillTex) { m_pSkillTex = m_pSkillTex; }

protected:
    Vec2 GetOverlappedRectPos(Collider* other) const;
  
protected:
    Player* m_pOwner;
    JoTexture* m_pSkillTex;
	JoTexture* m_pHitEffect;

    Vec2 m_vOffset;

    int m_iMaxEnemyCount;
    int m_iMaxHitCount;

	vector<HitInfo> m_vecHitInfo;
};

