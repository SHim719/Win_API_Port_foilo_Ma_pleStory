#pragma once
#include "GameObject.h"
class Success :
    public GameObject
{
public:
    Success();
   ~Success();

   void Initialize();
   void Update();
   void Render();
};

