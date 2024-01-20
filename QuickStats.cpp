#include "QuickStats.h"
#include "KeyMgr.h"
#include "Enrollable.h"

eKeyCode ArrSlotKey[] = 
{ eKeyCode::A, eKeyCode::S, eKeyCode::D, eKeyCode::F, eKeyCode::G, eKeyCode::H,
eKeyCode::LCtrl, eKeyCode::LShift, eKeyCode::One, eKeyCode::Two, eKeyCode::Three, eKeyCode::Four,
};

QuickStats::QuickStats()
	: m_vecEnrollState{}
{
	m_vecEnrollState.resize(SLOT_COUNT);

	for (int i = 0; i < SLOT_COUNT; ++i)
		m_vecEnrollState[i] = nullptr;
}

QuickStats::~QuickStats()
{
}

void QuickStats::Key_Check()
{
	for (int i = 0; i < SLOT_COUNT; ++i)
	{
		if (m_vecEnrollState[i])
		{
			m_vecEnrollState[i]->Key_Check(ArrSlotKey[i]);
		}
		
	}
}
