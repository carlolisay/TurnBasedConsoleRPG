#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(std::string name, int maxHp, int maxToughness, std::optional<Drop> drop)
    : Character{ std::move(name), maxHp }
    , m_toughness{ maxToughness }
    , m_maxToughness{ maxToughness }
    , m_drop{ std::move(drop) } // move the optional into m_drop
{
}

const std::optional<Drop>& Enemy::getDrop() const { return m_drop; }

int  Enemy::getToughness()    const { return m_toughness; }
int  Enemy::getMaxToughness() const { return m_maxToughness; }
bool Enemy::isBroken()        const { return m_isBroken; }
//bool Enemy::hasDrop()         const { return true; }
bool Enemy::hasDrop() const { return m_drop.has_value(); }
void Enemy::reduceToughness(int amount)
{
    m_toughness = std::max(0, m_toughness - amount);
    if (m_toughness == 0)
    {
        m_isBroken = true;
        m_toughness = m_maxToughness; // reset for the next cycle
    }
}

void Enemy::recoverFromBreak()
{
    m_isBroken = false;
}

ActionResult Enemy::performAttack()
{
    return ActionResult{ ActionResult::Type::Damage, 20 };
}

std::optional<Drop> Enemy::dropLoot()
{
    std::optional<Drop> result{ m_drop }; // copy whatever is there
    m_drop = std::nullopt; // always clear it
    return result;
}
