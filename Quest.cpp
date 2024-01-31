#include "Quest.h"
#include "ResourceMgr.h"
#include "QuestMgr.h"

Quest::Quest()
{
	m_pNumberTex = ResourceMgr::Find<JoTexture>(L"Quest_Number");
}

Quest::~Quest()
{
}



