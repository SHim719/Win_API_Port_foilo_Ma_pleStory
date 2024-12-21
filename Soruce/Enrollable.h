#pragma once

#include "CommonInclude.h"
#include "KeyMgr.h"

class JoTexture;
struct Slot;

class Enrollable abstract 
{
public:
	//virtual void Use() PURE;
	virtual void Render(const Vec2& vLeftTop) PURE;
	virtual void Key_Check(const eKeyCode& _key) PURE;
	
	void SetIconTex(JoTexture* const _pIconTex) { m_pIconTex = _pIconTex; }
	JoTexture* GetIconTex() const { return m_pIconTex; }
	
	void SetRefSlot(Slot* _pSlot) { m_pRefSlot = _pSlot; }
	Slot* GetRefSlot() { return m_pRefSlot; }
protected:
	JoTexture* m_pIconTex = nullptr;
	Slot* m_pRefSlot = nullptr;
};

