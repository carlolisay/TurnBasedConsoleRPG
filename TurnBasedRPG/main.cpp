
#include "Battle.h"
#include "StoneGolem.h"
#include "Slime.h"
#include "Mage.h"
#include "Player.h"
#include "Vampire.h"

#include <iostream>
#include <string>

int main()
{
    //std::cout << "Enter your name: ";
    //std::string name{};
    //std::getline(std::cin, name);
    //if (name.empty())
    //    name = "Hero";

    //Player     player{ name };
    //StoneGolem stonegolem{ "Stone Golem", 200, 100 };
    //Battle     battle{ player, stonegolem };
    Mage mage{ "Mage" };
	Vampire vampire{ "Vampire", 120, 40 };
    Slime slime{ "Slime", 150, 50 };
    Battle     battle{ mage, vampire };
    battle.run();

    return 0;
}
