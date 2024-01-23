#pragma once
#include "Button.h"
class Title_Button :
    public Button
{
public:
    Title_Button();
    ~Title_Button();

    void Initialize()       override;

    void Press_Button()     override;
    
};

