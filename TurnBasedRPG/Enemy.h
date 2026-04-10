#pragma once
#include "Character.h"
#include "ActionResult.h"
#include "Drop.h"
#include <optional>

class Enemy : public Character
{
public:
    Enemy(std::string name, int maxHp, int maxToughness,
        std::optional<Drop> drop = std::nullopt);
    const std::optional<Drop>& getDrop() const; // also add getDrop declaration

    int  getToughness()    const;
    int  getMaxToughness() const;
    bool isBroken()        const;
    bool hasDrop()         const;
    // Reduces the break gauge by amount.
    // Sets isBroken() and resets the gauge when it reaches zero.
    void reduceToughness(int amount);

    // Called at the end of the enemy's stunned turn to clear the broken flag.
    void recoverFromBreak();

    // Returns the HP damage dealt to the player this turn.     
    // // Derived classes override this to implement specific attack patterns.
    virtual ActionResult performAttack();

    std::optional<Drop> dropLoot();

private:
    int  m_toughness{};
    int  m_maxToughness{};
    bool m_isBroken{ false };

    std::optional<Drop> m_drop{};
};

