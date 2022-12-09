#include "rest.h"

#include <iostream>

#include "actor.h"
#include "engine.h"

Result Rest::perform(Engine&) {
    if (actor->health < actor->max_health) {
        actor->take_damage(-2);
        std::cout << "I feel better!\n";
        return success();
    } else {
        return failure();
    }
}
