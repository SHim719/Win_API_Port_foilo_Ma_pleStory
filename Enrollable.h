#pragma once

#include "CommonInclude.h"
#include "KeyMgr.h"

class JoTexture;

class Enrollable abstract 
{
public:
	//virtual void Use() PURE;
	virtual void Render(const Vec2& vLeftTop) PURE;
	virtual void Key_Check(const eKeyCode& _key) PURE;
	
	void SetIconTex(JoTexture* const _pIconTex) { m_pIconTex = _pIconTex; }
	JoTexture* GetIconTex() const { return m_pIconTex; }
	
protected:
	JoTexture* m_pIconTex = nullptr;
};

