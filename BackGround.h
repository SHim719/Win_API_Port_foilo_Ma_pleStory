#pragma once
#include "GameObject.h"

class JoTexture;

class BackGround :
    public GameObject
{
public:
	BackGround();
	~BackGround();

	void Initialize()	   override;
	void Update()		   override;
	void LateUpdate()	   override;
	void Render()		   override;

	void SetBgTex(JoTexture* _pTex) { m_pBgTexture = _pTex; }
private:
	JoTexture* m_pBgTexture;

};

