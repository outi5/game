#include "die.h"
#include "engine.h"

Die::Die(Actor& actor)
    :actor{actor} {}

void Die::execute(Engine& engine) {
    actor.health = 0;
    actor.alive = false;
    engine.dungeon.remove_actor(actor.get_position());
}
