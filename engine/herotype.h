#pragma once

#include "weapon.h"

#include <memory>
#include <functional>
#include <string>
#include <unordered_map>

// forward declaration
class Action;

// alias for a function that returns an Action
using Reaction = std::function<std::unique_ptr<Action>()>;

struct HeroType {
    // name corresponds to sprite name in asset file heros.txt
    std::string name;
    int speed, max_health;
    std::shared_ptr<Weapon> weapon;

    // a mapping of an input (e.g. arrow key 'Left' pressed) to a
    // function that produces an action ('Move actor left')
    std::unordered_map<std::string, Reaction> key_bindings;
};

