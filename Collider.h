#pragma once

#include "Entity.h"

class GameObject;

class Collider : public Entity
{
public:
	Collider();
	~Collider();

	void Initialize();
	void Update();
	void LateUpdate();
	void Render();

	void OnCollisionEnter(Collider* other);
	void OnCollisionStay(Collider* other);
	void OnCollisionExit(Collider* other);

	const Vec2& GetOffset() const { return m_vOffset; }
	void SetOffset(const Vec2& offset) { m_vOffset = offset; }

	const UINT32& GetID() const { return m_iID; }

	const Vec2& GetSize() const { return m_vSize; }
	void SetSize(const Vec2& size) { m_vSize = size; }

	const bool& IsCollisionOn() const { return m_bActiveColl; }
	void SetCollActive(const bool& b) { m_bActiveColl = b; }

	void SetCollisionActive() { m_bActiveColl = true; }
	void SetCollisionInactive() { m_bActiveColl = false; }

	void SetOwner(GameObject* _pOwner) { m_pOwner = _pOwner; }
	GameObject* GetOwner() const { return m_pOwner; }
private:
	static UINT32 s_CollisionID;
	UINT32 m_iID;
	Vec2 m_vOffset;
	Vec2 m_vSize;
	COLORREF m_renderColor;

	bool m_bActiveColl;

	GameObject* m_pOwner;
};

