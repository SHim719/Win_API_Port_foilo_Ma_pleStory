#pragma once

#include "CommonInclude.h"

#define LAYER_END (UINT)eLayerType::LT_END

class Scene;
class Collider;

union CollisionID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 id;
};

class CollisionMgr
{
public:
	static void Initialize();
	static void Update();

	static void SetCollisionEnabled(const eLayerType& left, const eLayerType& right, const bool& enabled);
	static void ClearCollisionInfo() { m_mapCollision.clear(); }

private:
	static void CheckLayer(Scene* curScene, const eLayerType& left, const eLayerType& right);
	static void CheckCollision(Collider* left, Collider* right);
	static bool Intersect(Collider* left, Collider* right);

private:
	static bitset<LAYER_END> m_collisionMatrix[LAYER_END];
	static unordered_map<UINT64, bool> m_mapCollision;
};