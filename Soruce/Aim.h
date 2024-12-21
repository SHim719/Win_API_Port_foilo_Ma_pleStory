#pragma once
#include "GameObject.h"


class JoTexture;
class EG_GameMgr;

class Aim :
    public GameObject
{
public:
	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void OnCollisionStay(Collider* _pOther)	override;

	void Set_GameMgr(EG_GameMgr* _pMgr) { m_pGameMgr = _pMgr; }

private:
	EG_GameMgr* m_pGameMgr;
	JoTexture* m_pCursorTex = nullptr;
	bool m_bHit = false;
};

