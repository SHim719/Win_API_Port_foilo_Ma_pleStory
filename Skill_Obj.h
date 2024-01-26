#pragma once
#include "GameObject.h"
#include "TimeMgr.h"
#include "Player.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "HitInterface.h"


class Skill_Obj :
    public GameObject
{
public:
    Skill_Obj();
    ~Skill_Obj();

    virtual void Skill_Start() PURE;
    void SetSkillTex(JoTexture* const _pSkillTex) { m_pSkillTex = m_pSkillTex; }

	void SetOwner(Player* _pPlayer) { m_pOwner = _pPlayer; }
protected:
    Vec2 GetOverlappedRectPos(Collider* other) const;
  
protected:
    Player* m_pOwner;
    JoTexture* m_pSkillTex;
	JoTexture* m_pHitEffect;

    Vec2 m_vOffset;

    int m_iMaxEnemyCount;
    int m_iMaxHitCount;
    int m_iPerHitCount;

	vector<AttackInfo> m_vecAttInfo;
};

