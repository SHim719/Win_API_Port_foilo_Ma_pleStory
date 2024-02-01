#pragma once
#include "UI.h"

enum class QuestFlag
{
    Hunt_Monster,
    Obtain_Item,
};

class Quest :
    public UI
{
public:
    Quest();
    ~Quest();
   
    void Set_QuestNumber(const int& _iNum) { m_iQuestNumber = _iNum; }
    void Set_Satisfied(bool _b) { m_bSatisfied = _b; }
    void Set_Clear(bool _b) { m_bClear = _b; }
    bool IsClear() const { return m_bClear; }
    bool IsSatisfied() const { return m_bSatisfied; }
protected:
    JoTexture* m_pNumberTex = nullptr;
    bool m_bSatisfied = false;
    bool m_bClear = false;
    int m_iQuestNumber = 0;

   
};

