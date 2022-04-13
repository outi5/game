#pragma once

#include <string>
#include <memory>
#include <functional>
#include "actor.h"
#include "sprite.h"

class Weapon {
public:
    // name corresponds to a sprite in weapons.txt
    Weapon(const std::string& name, int damage);
    virtual ~Weapon() {}

    // override with what happens when weapon is used in game
    virtual void use(Engine& engine, Actor& attacker, Actor& defender) = 0;

    // these are public to allow for manipulation by heros and monsters
    std::string name;
    int damage;
    Sprite sprite;
};
