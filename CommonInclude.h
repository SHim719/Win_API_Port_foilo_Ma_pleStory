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
using std::abs;
using std::fabs;

#include "Vec2.h"
#include "Enums.h"

struct Timer
{
	float m_fNowTime = 0.f;
};

int generateRandomNumber(int firstDigit, int totalDigits)
{
    // 맨 앞자릿수는 1 이상 9 이하의 정수여야 합니다.
    if (firstDigit < 1 || firstDigit > 9) {
        throw std::invalid_argument("맨 앞자릿수는 1 이상 9 이하의 정수여야 합니다.");
    }

    // 총 자릿수는 1 이상이어야 합니다.
    if (totalDigits < 1) {
        throw std::invalid_argument("총 자릿수는 1 이상이어야 합니다.");
    }

    // 맨 앞자릿수를 제외한 나머지 자릿수를 랜덤하게 생성
    int randomNumber = firstDigit * (int)pow(10, totalDigits - 1) + rand() % (int)pow(10, totalDigits - 1);

    return randomNumber;
}

bool Calc_Critical()
{
    if (rand() % 10 < 2)
        return true;
    else
        return false;
}