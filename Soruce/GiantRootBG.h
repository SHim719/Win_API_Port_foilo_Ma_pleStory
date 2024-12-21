#pragma once
#include "AnimBG.h"


class GiantRootBG :
    public AnimBG
{
public:
    GiantRootBG();
    ~GiantRootBG();

    void Initialize()    override;
    void Release()       override;
};

