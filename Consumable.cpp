#include "Consumable.h"
#include "RenderMgr.h"




PlayerStats* Consumable::s_pPlayerStats = nullptr;
JoTexture* Consumable::s_pNumTex = nullptr;

Consumable::Consumable()
	: Item(ItemType::IT_CONSUMABLE)
{
}

Consumable::~Consumable()
{
}

void Consumable::Render(const Vec2& vLeftTop)
{
	if (m_pRefSlot == nullptr || m_pRefSlot->iCount == 0)
		return;

	Item* item = m_pRefSlot->item;
	if (item == nullptr)
		return;

	RenderMgr::RenderImage(m_pItemTex,
		vLeftTop.x, vLeftTop.y,
		vLeftTop.x + 32.f, vLeftTop.y + 32.f);


	string sNum = format("{}", m_pRefSlot->iCount);

	Vec2 vNumPos = vLeftTop;
	vNumPos.y += 21.f;

	for (size_t i = 0; i < sNum.size(); ++i)
	{
		int iNum = sNum[i] - '0';

		RenderMgr::RenderFrame(s_pNumTex
			, vNumPos.x, vNumPos.y
			, vNumPos.x + 8.f, vNumPos.y + 11.f
			, 8.f * iNum, 0.f
			, 8.f * iNum + 8.f, 11.f);

		if (iNum == 1)
			vNumPos.x += 5.f;
		else
			vNumPos.x += 8.f;
	}
}

void Consumable::Key_Check(const eKeyCode& _key)
{
	if (KeyMgr::GetKeyDown(_key))
	{
		Use();
	}
}
