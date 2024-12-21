#pragma once

#include "CommonInclude.h"

#define SLOT_COUNT 12

class Enrollable;

class QuickStats
{
public:
	QuickStats();
	~QuickStats();

	void Key_Check();

	const vector<Enrollable*>& GetEnrollState() const { return m_vecEnrollState; }
	void Set_Enroll(const size_t& Iidx, Enrollable* pEnroll) { m_vecEnrollState[Iidx] = pEnroll; }
private:
	vector<Enrollable*> m_vecEnrollState;

};

