#pragma once

#include "framework.h"
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <assert.h>
#include <functional>
#include <bitset>
#include <unordered_map>
#include <format>


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

#define SAFE_ARR_DELETE(p) if (p) {delete[] p; p = nullptr; }
#define PURE = 0

using std::vector;
using std::list;
using std::for_each;
using std::string;
using std::wstring;
using std::map;
using std::function;
using std::move;
using std::clamp;
using std::bitset;
using std::unordered_map;
using std::min;
using std::max;
using std::swap;
using std::to_string;
using std::to_wstring;
using std::bind;
using std::format;
using std::pair;

#include "Vec2.h"
#include "Enums.h"

struct Timer
{
	float m_fNowTime = 0.f;
};