#pragma once
#include "Enemy.h"

class Vampire : public Enemy
{
public:
	Vampire(std::string name, int maxHp, int maxToughness);
	ActionResult performAttack() override;

private:
	int m_turnCount{ 0 };
};