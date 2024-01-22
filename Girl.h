#pragma once
#include "GameObject.h"

class JoTexture;

class Girl :
    public GameObject
{
public:
    Girl();
    ~Girl();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;

private:
	bool Check_Rect();

private:
	JoTexture* m_pTexture;
	JoTexture* m_pDialNameTex;
	JoTexture* m_pDialTex;

	vector<pair<wstring, int>> m_vecDials;

	RECT	   m_tRect;
};

