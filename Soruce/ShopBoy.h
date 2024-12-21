#pragma once

#include "GameObject.h"
#include "ShopUI.h"


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
	bool Check_Rect();

private:
	JoTexture* m_pTexture;
	JoTexture* m_pNameBarTex;

	RECT m_tRect;
	vector<SellItem> m_vecSellItems;

};

