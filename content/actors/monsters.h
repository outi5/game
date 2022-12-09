#pragma once

#include "axe.h"
#include "closedoor.h"
#include "engine.h"
#include "monster.h"
#include "monstertype.h"
#include "move.h"
#include "none.h"
#include "randomness.h"
#include "rest.h"
#include "sword.h"
#include "wander.h"

namespace Monsters {

/* ********
   I couldn't figure out what I was doing wrong, but when I
   tried to implement this code in monsters.cpp it wouldn't build. So
   I know I need to clean this up, but I figured building was better
   than not building for now. Can you see what I'm doing wrong?
   ********
*/
std::unique_ptr<Action> default_behavior(Engine& engine, Monster& me);

MonsterType goblin();
MonsterType zombie_small();
MonsterType skeleton();

}  // namespace Monsters
