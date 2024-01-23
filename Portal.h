#pragma once
#include "GameObject.h"


class Portal :
    public GameObject
{
public:
	Portal();
	~Portal();

	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void Set_MovePos(const Vec2& _vPos) { m_vMovePos = _vPos; }
	void Set_PortalTex(JoTexture* const _pTex) { m_pPortalTex = _pTex; }
	void Set_SceneName(const wstring& _wsName) { m_wsSceneName = _wsName; }

	void OnCollisionStay(Collider* other) override;

private:
	void MoveTo(GameObject* _pObj);

private:
	JoTexture*	m_pPortalTex;
	Vec2		m_vMovePos;
	wstring		m_wsSceneName;
	

};

