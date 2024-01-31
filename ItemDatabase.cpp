#include "ItemDatabase.h"
#include "KeyMgr.h"
#include "Hat.h"
#include "Top.h"
#include "Bottom.h"
#include "Shoes.h"
#include "Weapon.h"
#include "PowerEllixer.h"
#include "Token.h"

unordered_map<wstring, Item*> ItemDatabase::m_mapItemData{};

void ItemDatabase::Initialize()
{

	Hat* hat = new Hat;
	hat->Initialize();
	m_mapItemData.insert({ hat->GetName(), hat});

	Top* top = new Top;
	top->Initialize();
	m_mapItemData.insert({ top->GetName(), top });

	Bottom* bottom = new Bottom;
	bottom->Initialize();
	m_mapItemData.insert({ bottom->GetName(), bottom });

	Shoes* shoes = new Shoes;
	shoes->Initialize();
	m_mapItemData.insert({ shoes->GetName(), shoes });

	Weapon* weapon = new Weapon;
	weapon->Initialize();
	m_mapItemData.insert({ weapon->GetName(), weapon });

	PowerEllixer* powerEllixer = new PowerEllixer;
	powerEllixer->Initialize();
	m_mapItemData.insert({ powerEllixer->GetName(), powerEllixer});

	Token* token = new Token;
	token->Initialize();
	m_mapItemData.insert({ token->GetName(), token });
	
}

void ItemDatabase::Release()
{
}

Item* ItemDatabase::FindItemData(const wstring& name)
{
	auto it = m_mapItemData.find(name);
	if (it == m_mapItemData.end())
		return nullptr;

	return it->second;
}
