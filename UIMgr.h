#pragma once

class UI;

class UIMgr
{
public:
	static void Initialize();
	static void Update();
	static void Render();
	static void Release();

	static void SetMouseUsed(const bool& b) { m_bMouseUsed = b; }
	static const bool& IsMouseUsed() { return m_bMouseUsed; }

	static UI* Get_UI_Instance(const UI_Enums& UI_Num) { return m_arrUIs[(UINT)UI_Num]; }
private:
	static void UIkeyCheck();

private:
	static UI* m_arrUIs[(UINT)UI_Enums::UI_End];
	static list<UI*> m_ActiveUIList;
	static list<UI*> m_inActiveUIList;
	static bool m_bMouseUsed;

};

