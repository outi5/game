#include "sword.h"

#include "engine.h"
#include "hit.h"

Sword::Sword(int damage) : Weapon("sword", damage) {}

void Sword::use(Engine& engine, Actor&, Actor& defender) {
    engine.events.add(Hit{defender, damage});
}