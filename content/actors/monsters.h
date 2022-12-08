#pragma once

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

std::unique_ptr<Action> default_behavior(Engine& engine, Monster& me) {
    // pursue Hero if monster can see him (If Hero sees me, I see him)
    if (me.is_visible() && engine.hero) {
        Vec from = me.get_position();
        Vec to = engine.hero->get_position();
        std::vector<Vec> path = engine.dungeon.calculate_path(from, to);

        if (path.size() > 1) {
            Vec direction = path.at(1) - path.at(0);
            return std::make_unique<Move>(direction);
        }
    }
    // Monster doesn't see Hero
    if (probability(66)) {
        return std::make_unique<Wander>();
    } else {
        return std::make_unique<Rest>();
    }
};

// MonsterType goblin();
/* ********
   Likewise, I could not get this to build if I put it in monsters.cpp,
   but I could get it to build here, so I left it for now. What am I
   missing (I fully expect this to be a face-palm moment)
   ********
*/

constexpr int default_speed{8};
int default_health = 6;
const MonsterType goblin{"goblin", default_speed, default_health,
                         std::make_shared<Sword>(2), default_behavior};
const MonsterType zombie_small{"zombie_small", default_speed, default_health,
                               std::make_shared<Sword>(2), default_behavior};
const MonsterType skeleton{"skeleton", default_speed, default_health,
                           std::make_shared<Sword>(2), default_behavior};
}  // namespace Monsters
