#pragma once
#include "Equipable.h"


class Shoes :
    public Equipable
{
public:
    Shoes();
    ~Shoes();

    void Initialize()  override;
};

