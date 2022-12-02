#pragma once

#include "weapon.h"

class Sword : public Weapon {
public:
    Sword(int damage);
    void use(Engine& engine, Actor& attacker, Actor& defender) override;
};