#pragma once

#include "weapon.h"

class None : public Weapon {
public:
    None();
    void use(Engine& engine, Actor& attacker, Actor& defender) override;
};
