#pragma once
#include "AnimBG.h"
class ChewBG :
    public AnimBG
{
public:
    ChewBG();
    ~ChewBG();

    void Initialize() override;
};

