#pragma once
#include "GameObject.h"

class Item;

class Stone :
    public GameObject
{
	enum class State
	{
		First,
		Second,
		End,
	};

public:
	Stone();
	~Stone();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;

private:
	bool Check_Rect();
	void Drop_Item();
	void Slow_Time();

	void First();
	void Second();

	void Change_Scene();

private:
	JoTexture* m_pTexture;
	vector<pair<wstring, int>> m_vecDials;
	RECT	   m_tRect;
	Item* m_pTokenItem = nullptr;
	bool m_bTimeSlow = false;

	Item_Obj* m_pObj = nullptr;

	State m_eState = State::First;
	
	bool m_bChange = false;
};

