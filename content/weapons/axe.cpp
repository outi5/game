#include "axe.h"

#include "engine.h"
#include "hit.h"
#include "swing.h"

Axe::Axe(int damage) : Weapon{"axe", damage} {}

void Axe::use(Engine& engine, Actor& attacker, Actor& defender) {
    Vec direction = defender.get_position() - attacker.get_position();
    engine.events.add(Swing{sprite, direction, defender, damage});
    // engine.events.add(Hit{defender, damage});
}