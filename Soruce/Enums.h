#pragma once


enum class eLayerType
{
	LT_BACKGROUND,
	LT_NONE,
	LT_OBJECT,
	LT_NPC,
	LT_MONSTER,
	LT_MONSTER_EFFECT,
	LT_PLAYER,
	LT_EFFECT,
	LT_ITEM,

	LT_UI = 10,
	LT_END = 11
};

enum class eResourceType
{
	Texture,
	Bmp,
	Audio,
	Animation,
	End,
};