#include "ItemDatabase.h"
#include "KeyMgr.h"
#include "Hat.h"
#include "Top.h"
#include "Bottom.h"
#include "Shoes.h"
#include "Weapon.h"

unordered_map<wstring, Item*> ItemDatabase::m_mapItemData{};

void ItemDatabase::Initialize()
{

	Hat* hat = new Hat;
	hat->Initialize();
	m_mapItemData.insert({ L"Hat", hat });

	Top* top = new Top;
	top->Initialize();
	m_mapItemData.insert({ L"Top", top });

	Bottom* bottom = new Bottom;
	bottom->Initialize();
	m_mapItemData.insert({ L"Bottom", bottom });

	Shoes* shoes = new Shoes;
	shoes->Initialize();
	m_mapItemData.insert({ L"Shoes", shoes });

	Weapon* weapon = new Weapon;
	weapon->Initialize();
	m_mapItemData.insert({ L"Weapon", weapon });


	//PowerEllixer* powerEllixer = new PowerEllixer;
	//powerEllixer->Initialize();
	//m_mapItemData.insert({ L"PowerEllixer", powerEllixer });

	
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
