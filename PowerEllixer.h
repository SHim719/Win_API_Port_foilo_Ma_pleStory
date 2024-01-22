#pragma once
#include "Consumable.h"


class PowerEllixer :
    public Consumable
{
public:
    PowerEllixer();
    ~PowerEllixer();

    void Initialize() override;

    void Use() override;
};

