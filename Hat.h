#pragma once
#include "Equipable.h"

class Hat :
    public Equipable
{
public:
    Hat();
    ~Hat();

    void Initialize()  override;

};

