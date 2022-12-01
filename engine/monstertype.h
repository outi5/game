#pragma once

#include <functional>
#include <memory>
#include <string>

#include "weapon.h"

// forward declarations
class Action;
class Engine;
class Monster;

struct MonsterType {
    std::string name;
    int speed, max_health;
    std::shared_ptr<Weapon> weapon;
    std::function<std::unique_ptr<Action>(Engine& engine, Monster& monster)>
        behavior;
};
