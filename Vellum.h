#pragma once

#include "Enemy.h"

class Vellum : public Enemy
{
public:
	Vellum();
	~Vellum();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	void Hit(const HitInfo& _hitInfo);

private:


};

