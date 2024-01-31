#pragma once
#include "Portal.h"


class EventPortal2 :
    public Portal
{
    enum class PortalState
    {
        First,
        Second,
        End,
    };

public:
    EventPortal2();
    void OnCollisionStay(Collider* other) override;
    void Set_QuestNumber(const int& _iNum) { m_iQuestNumber = _iNum; }

private:
    void First();
    void Second();

private:
    int m_iQuestNumber = 0;
    vector<pair<wstring, int>> m_vecDials[2] = {};

    PortalState  m_eState;


};

