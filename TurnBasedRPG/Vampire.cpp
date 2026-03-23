#include "Vampire.h"

#include <iostream>

Vampire::Vampire(std::string name, int maxHp, int maxToughness)
	: Enemy{ std::move(name), maxHp, maxToughness }
{
}

ActionResult Vampire::performAttack()
{
	++m_turnCount;
	if (m_turnCount % 4 == 0) {
		std::cout << "  >> " << m_name
			<< " summon a bat and bites you and drains your life! <<\n";
		return ActionResult{ ActionResult::Type::Heal, 8 }, ActionResult{ ActionResult::Type::Damage, 14 };
		
	}
	return ActionResult{ ActionResult::Type::Damage, 14 };
}