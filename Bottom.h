#pragma once
#include "Equipable.h"


class Bottom :
    public Equipable
{
public:
    Bottom();
    ~Bottom();

    void Initialize()  override;
};

