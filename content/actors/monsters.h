#pragma once

#include "closedoor.h"
#include "engine.h"
#include "monster.h"
#include "monstertype.h"
#include "move.h"
#include "none.h"
#include "randomness.h"
#include "rest.h"
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

        /* ********
           I had to change this to "> 2" or the game would crash everytime the
           monster was asked to make a move when right next to the hero. I
           assume that's because he was not able to move on top of the hero.

           As it is the game still crashes when two monster get stacked up one
           behind the other and directly behind the hero, because this doesn't
           stop the second in line from trying to move.

           The game also stops (although it doesn' crash) when the hero is stuck
           between 2 monsters and can't move to either side (e.g., in a hall).
           They are tyring to move forward (but can't) and the hero can't move
           either direction.

           I think this needs to be resolved in MOVE, but I didn't have time to
           sort through it. Some of it will be resolved simply by implementing
           ATTACK for the monsters.
           ********
        */
        if (path.size() > 2) {
            Vec direction = path.at(1) - path.at(0);
            return std::make_unique<Move>(direction);
        }
        // this is TEMPORARY until attack is implemented
        else {
            return std::make_unique<Rest>();
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
   Likewise, I could not get this to build if I put it in mosters.cpp,
   but I could get it to build here, so I left it for now. What am I 
   missing (I fully expect this to be a face-palm moment)
   ********
*/

constexpr int default_speed{8};
int default_health = 2;
const MonsterType goblin{"goblin", default_speed, default_health,
                         std::make_shared<None>(), default_behavior};
const MonsterType zombie_small{"zombie_small", default_speed, default_health,
                               std::make_shared<None>(), default_behavior};
const MonsterType skeleton{"skeleton", default_speed, default_health,
                           std::make_shared<None>(), default_behavior};
}  // namespace Monsters
