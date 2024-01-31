#pragma once
#include "GameObject.h"


class Esfesia :
    public GameObject
{
	enum class Esfesia_State
	{
		First,
		Second,
		End,
	};

public:
	Esfesia();
	~Esfesia();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;

private:
	bool Check_Rect();
	void First(class MyDialogBox* _pBox);
	void Second(MyDialogBox* _pBox);
	void End(MyDialogBox* _pBox);

private:
	JoTexture* m_pTexture;
	JoTexture* m_pDialNameTex;
	JoTexture* m_pDialTex;

	vector<pair<wstring, int>> m_vecDials;
	vector<pair<wstring, int>> m_vecDials2;

	RECT	   m_tRect;

	bool		m_bSuccessed;

	Esfesia_State m_eState;

	function<void()> ChangeScene_ToGame;
};

