#pragma once

#include "GameObject.h"

class JoTexture;

class ShopBoy : public GameObject
{
public:
	ShopBoy();
	~ShopBoy();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;
private:
	JoTexture* m_pTexture;
};

