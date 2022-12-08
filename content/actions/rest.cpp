#include "rest.h"

#include <iostream>

#include "actor.h"
#include "engine.h"

Result Rest::perform(Engine&) {
    actor->health += 2;
    std::cout << "I feel better!\n";
    return success();
}
