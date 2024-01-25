#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Layer.h"
#include "Collider.h"


bitset<LAYER_END> CollisionMgr::m_collisionMatrix[LAYER_END]{};
unordered_map<UINT64, bool> CollisionMgr::m_mapCollision{};

void CollisionMgr::Initialize()
{
	SetCollisionEnabled(eLayerType::LT_MONSTER, eLayerType::LT_EFFECT, true);
	SetCollisionEnabled(eLayerType::LT_PLAYER, eLayerType::LT_OBJECT, true);
	SetCollisionEnabled(eLayerType::LT_PLAYER, eLayerType::LT_MONSTER, true);
}

void CollisionMgr::Update()
{
	Scene* curScene = SceneMgr::GetActiveScene();

	for (UINT row = 0; row < LAYER_END; ++row)
	{
		for (UINT col = 0; col < LAYER_END; ++col)
		{
			if (m_collisionMatrix[row][col])
			{
				CheckLayer(curScene, (eLayerType)row, (eLayerType)col);
			}

		}
	}
}

void CollisionMgr::SetCollisionEnabled(const eLayerType& left, const eLayerType& right, const bool& enabled)
{
	UINT row = 0;
	UINT col = 0;

	if (left <= right)
	{
		row = (UINT)left;
		col = (UINT)right;
	}
	else
	{
		row = (UINT)right;
		col = (UINT)left;
	}

	m_collisionMatrix[row][col] = enabled;
}

void CollisionMgr::CheckLayer(Scene* curScene, const eLayerType& left, const eLayerType& right)
{
	const list<GameObject*>& leftLayer = curScene->GetLayer(left)->GetGameObjects();
	const list<GameObject*>& rightLayer = curScene->GetLayer(right)->GetGameObjects();

	for (GameObject* leftObj : leftLayer)
	{
		if (leftObj->IsActive() == false) continue;

		Collider* leftCol = leftObj->GetCollider();
		if (leftCol == nullptr) continue;

		for (GameObject* rightObj : rightLayer)
		{
			if (rightObj->IsActive() == false) continue;

			Collider* rightCol = rightObj->GetCollider();
			if (rightCol == nullptr) continue;

			CheckCollision(leftCol, rightCol);
		}

		/*for (int i = 0; i < rightLayer.size(); ++i)
		{
			GameObject* rightObj = rightLayer[i];

			if (rightObj->IsActive() == false) continue;

			Collider* rightCol = rightObj->GetCollider();
			if (rightCol == nullptr) continue;
			if (!rightCol->IsCollisionOn()) continue;

			CheckCollision(leftCol, rightCol);
		}*/
		
	}
}

void CollisionMgr::CheckCollision(Collider* left, Collider* right)
{
	// 두 충돌체 번호를 가져온 ID를 확인해서 CollisionID값을 세팅
	CollisionID id = {};
	id.left = left->GetID();
	id.right = right->GetID();

	auto it = m_mapCollision.find(id.id);
	if (it == m_mapCollision.end())
	{
		m_mapCollision.insert({ id.id, false });
		it = m_mapCollision.find(id.id);
	}

	if (Intersect(left, right))
	{
		if (!it->second)
		{
			left->OnCollisionEnter(right);
			right->OnCollisionEnter(left);
			it->second = true;
		}
		else
		{
			left->OnCollisionStay(right);
			right->OnCollisionStay(left);
		}
	}
	else if (it->second)
	{
		left->OnCollisionExit(right);
		right->OnCollisionExit(left);
		it->second = false;
	}
}

bool CollisionMgr::Intersect(Collider* left, Collider* right)
{
	GameObject* leftObj = left->GetOwner();
	GameObject* rightObj = right->GetOwner();

	Vec2 leftPos = const_cast<Vec2&>(leftObj->GetPos()) + const_cast<Vec2&>(left->GetOffset());
	Vec2 rightPos = const_cast<Vec2&>(rightObj->GetPos()) + const_cast<Vec2&>(right->GetOffset());

	Vec2 leftSize = left->GetSize();
	Vec2 rightSize = right->GetSize();

	if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x * 0.5f + rightSize.x * 0.5f)
		&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y * 0.5f + rightSize.y * 0.5f))
	{
		return true;
	}

	return false;
}
