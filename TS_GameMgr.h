#pragma once
#include "GameObject.h"


class Totem;

class TS_GameMgr :
    public GameObject
{
public:
	TS_GameMgr();
	~TS_GameMgr();

	void Initialize()	override;
	void Update()		override;

private:
	list<Totem*> m_TotemList = {};
};

