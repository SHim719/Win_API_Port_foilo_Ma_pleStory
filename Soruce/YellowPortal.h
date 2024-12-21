#pragma once
#include "GameObject.h"


class YellowPortal :
    public GameObject
{
public:
	YellowPortal();
	~YellowPortal();

	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void OnCollisionStay(Collider* other) override;

	void Set_MovePos(const Vec2& _vPos) { m_vMovePos = _vPos; }
private:
	void MoveTo(GameObject* _pObj);


private:
	JoTexture* m_pPortalTex;
	Vec2		m_vMovePos;

};

