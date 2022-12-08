#include "attack.h"

#include <iostream>

#include "engine.h"

Attack::Attack(Actor& defender) : defender{defender} {}

Result Attack::perform(Engine&) {
    actor->attack(defender);
    std::cout << "ATTACK!\n";
    return success();
}
