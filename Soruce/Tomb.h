#pragma once
#include "GameObject.h"

class JoTexture;
class Tomb :
    public GameObject
{
public:
	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void SetPlayer(Player* const _pPlayer) { m_pPlayer = _pPlayer; }
private:
	JoTexture* m_pTombTex = nullptr;
	Player* m_pPlayer = nullptr;

};

