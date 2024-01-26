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

	LT_UI = 8,
	LT_END = 10
};

enum class eResourceType
{
	Texture,
	Bmp,
	Audio,
	Animation,
	End,
};