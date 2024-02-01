#pragma once
#include "GameObject.h"

class JoTexture;
class Inventory;
class Item;
class MyDialogBox;

class Girl :
    public GameObject
{
	enum class Girl_State
	{
		First,
		Second,
		End,
	};


public:
    Girl();
    ~Girl();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;

	void SetInventory(Inventory* _pInventory) { m_pInventory = _pInventory; }

private:
	bool Check_Rect();

	void First(MyDialogBox* pDialBox);
	void Second(MyDialogBox* pDialBox);
	void End(MyDialogBox* pDialBox);

	void Set_Second() { m_eState = Girl_State::Second; }
	void Set_End() { m_eState = Girl_State::End; }

	void Change_Scene_Title();
private:
	JoTexture* m_pTexture;
	JoTexture* m_pDialNameTex;
	JoTexture* m_pDialTex;
	JoTexture* m_pNameBarTex;

	vector<pair<wstring, int>> m_vecDials;
	vector<pair<wstring, int>> m_vecDials2;
	vector<pair<wstring, int>> m_vecDials3;

	RECT	   m_tRect;

	Girl_State	m_eState;

	Inventory* m_pInventory;

	Item* m_pToken;
};

