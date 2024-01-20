#pragma once


enum class eLayerType
{
	LT_NONE,
	LT_BACKGROUND,
	LT_MONSTER,
	LT_PLAYER,
	LT_PLATFORM,
	LT_EFFECT,

	LT_UI = 8,
	LT_CAMERA = 9,
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