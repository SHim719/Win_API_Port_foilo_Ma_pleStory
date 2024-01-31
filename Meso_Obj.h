#pragma once
#include "Item_Obj.h"

class Meso_Obj :
    public Item_Obj
{
public:
	void Initialize() override;
	void Render()       override;
	void SetMeso(const int& _iMeso) { m_iMeso = _iMeso; }

	void OnCollisionStay(Collider* _pOther);

	static void Set_MesoTex(JoTexture* _pMesoTex) { m_pMesoTex = _pMesoTex; }
private:
	static JoTexture* m_pMesoTex;

	int m_iMeso;
};

