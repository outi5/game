#include "hit.h"
#include "actor.h"
#include "engine.h"
#include "die.h"

Hit::Hit(Actor& actor, int damage)
    :actor{actor}, damage{damage} {}

void Hit::execute(Engine& engine) {
    actor.take_damage(damage);

    if (actor.health <= 0) {
        engine.events.add(Die{actor});
    }
}
