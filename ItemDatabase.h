#pragma once

#include "CommonInclude.h"

class Item;

class ItemDatabase
{
public:
	static void Initialize();
	static void Release();

	static Item* FindItemData(const wstring& name);

private:
	static unordered_map<wstring, Item*> m_mapItemData;
};

