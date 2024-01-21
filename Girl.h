#pragma once
#include "GameObject.h"

class JoTexture;

class Girl :
    public GameObject
{
public:
    Girl();
    ~Girl();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;
private:
	JoTexture* m_pTexture;

};

