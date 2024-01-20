#pragma once
#include "Equipable.h"


class Weapon :
    public Equipable
{
public:
    Weapon();
    ~Weapon();

    void Initialize()  override;
};

