#include "doctest.h"
#include "Enemy.h"
#include "Battle.h"
#include "Drop.h"

TEST_CASE("Enemy without a drop has no drop") {
	Enemy e{ "Dummy", 100, 50 };
	CHECK(!e.hasDrop());
}

TEST_CASE("Enemy with a drop reports it correctly") {
	Drop d{ "Iron Shard", 10 };
	Enemy e{ "Golem", 200, 100, d };
	SUBCASE("hasDrop returns true") {
		CHECK(e.hasDrop());
	}
	SUBCASE("getDrop returns correct name") {
		CHECK(e.getDrop()->name == "Iron Shard");
	}
	SUBCASE("getDrop returns correct gold value") {
		CHECK(e.getDrop()->goldValue == 10);
	}
}

TEST_CASE("Enemy::dropLoot returns and removes the drop") {
	Drop d{ "Iron Shard", 10 };
	Enemy e{ "Golem", 200, 100, d };
	SUBCASE("returns the correct drop") {
		auto dropped = e.dropLoot();
		CHECK(dropped.has_value());
		CHECK(dropped->name == "Iron Shard");
		CHECK(dropped->goldValue == 10);
	}
	SUBCASE("removes the drop so hasDrop becomes false") {
		e.dropLoot();
		CHECK(!e.hasDrop());
	}
	SUBCASE("returns nullopt when there is no drop") {
		Enemy noDrop{ "Dummy", 100, 50 };
		CHECK(!noDrop.dropLoot().has_value());
	}
}

TEST_CASE("Enemy drop is accessible after enemy dies") {
	Drop d{ "Iron Shard", 10 };
	Enemy e{ "Golem", 200, 100, d };
	e.takeDamage(999);
	CHECK(!e.isAlive());
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->name == "Iron Shard");
}
TEST_CASE("Drop with empty name is still valid") {
	Drop d{ "", 5 };
	Enemy e{ "Golem", 200, 100, d };
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->goldValue == 5);
}
TEST_CASE("Drop can have zero gold value") {
	Drop d{ "Broken Sword", 0 };
	Enemy e{ "Golem", 200, 100, d };
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->goldValue == 0);
}
//Lab Activity
TEST_CASE("Enemy initialises with full toughness") {
	// write this test case
	Enemy e{ "Golem", 200, 100 };
	CHECK(e.getMaxToughness());
}
TEST_CASE("Enemy::reduceToughness") {
	Enemy e{ "Golem", 200, 100 };
	// write all subcases
	SUBCASE("reduceToughness on basic strike") {
		e.reduceToughness(10);
		CHECK(e.getToughness() == 90);
	}	
	SUBCASE("reduceToughness on basic skill") {
		e.reduceToughness(25);
		CHECK(e.getToughness() == 75);
	}
	SUBCASE("reduceToughness on ultimate skill") {
		e.reduceToughness(30);
		CHECK(e.getToughness() == 70);
	}
	SUBCASE("Toughness must not be zero") {
		e.reduceToughness(100);
		REQUIRE(e.isBroken());
		CHECK(e.getToughness() == e.getMaxToughness());
	}
	SUBCASE("Toughness must not be negative") {
		e.reduceToughness(150);
		REQUIRE(e.isBroken());
		CHECK(e.getToughness() == e.getMaxToughness());
	}
	SUBCASE("Toughness will not broken if greater than zero") {
		e.reduceToughness(99);
		CHECK(e.isBroken() == false);
	}
}
TEST_CASE("Enemy::recoverFromBreak") {
	const int maxToughness{ 50 };
	Enemy e{ "Dummy", 100, maxToughness };
	SUBCASE("clears broken flag") {
		e.reduceToughness(maxToughness);
		REQUIRE(e.isBroken() == true); // stop if not broken; rest of test is meaningless
		e.recoverFromBreak();
		CHECK(e.isBroken() == false);
	}
	// add remaining subcases
	
}
TEST_CASE("Enemy::performAttack returns damage") {
	// write this test case
	Enemy e{ "Golem", 200, 100 };
	CHECK(e.performAttack().type == ActionResult::Type::Damage);
}
