#pragma once

#include "engine.h"
#include "monster.h"
#include "monstertype.h"

namespace Monsters {

std::unique_ptr<Action> default_behavior(Engine& engine, Monster& me);

MonsterType goblin();
MonsterType zombie_small();
MonsterType skeleton();
MonsterType demon_big();

}  // namespace Monsters
