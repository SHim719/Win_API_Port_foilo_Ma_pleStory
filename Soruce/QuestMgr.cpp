#include "QuestMgr.h"

Quest* QuestMgr::m_pNowQuest = nullptr;
bool QuestMgr::m_bClearQuest[10] = {};

void QuestMgr::Update()
{
	if (m_pNowQuest == nullptr)
		return;

	if (m_pNowQuest->IsClear())
	{
		Safe_Delete<Quest*>(m_pNowQuest);
	}
		
	
}
