#pragma once

#include "CommonInclude.h"
#include "Entity.h"

class GameObject;
class Layer;
class Player;

class Scene : public Entity
{
public:
	Scene();
	~Scene();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	void Release();

	virtual void OnEnter();
	virtual void OnExit();

	void Destroy();

	void AddObj(GameObject* obj, const eLayerType& type);

	Layer* GetLayer(const eLayerType& type) const { return m_vLayers[(UINT)type]; }

	void CalcAndSetCameraArea(const float& fTexWidth, const float& fTexHeight, const Vec2& vOffset);
	const Vec2& GetMinCameraPos() const { return m_vMinCameraPos; }
	const Vec2& GetMaxCameraPos() const { return m_vMaxCameraPos; }

	static void Delete_DonDestroy();
	void Set_PlayerPos(const Vec2& _vPos);
private:
	void createLayer();

protected:
	vector<Layer*> m_vLayers;

	Vec2 m_vMinCameraPos;
	Vec2 m_vMaxCameraPos;

	Vec2 m_vLimitPosX;

	HDC m_pixelDC = nullptr;

	static Player* s_pMainPlayer;
};

