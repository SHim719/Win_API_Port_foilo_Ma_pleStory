#pragma once

#include "Quest.h"

class QuestMgr
{
public:
	static bool IsClearQuest(const int& _iIdx) { return m_bClearQuest[_iIdx]; }

	static void Update();

	static Quest* Get_NowQuest() { return m_pNowQuest; }
	static void Set_NowQuest(Quest* _pQuest) { m_pNowQuest = _pQuest; }
private:
	static Quest* m_pNowQuest;
	static bool m_bClearQuest[10];

};

