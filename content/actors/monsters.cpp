#include "monsters.h"

#include "axe.h"
#include "closedoor.h"
#include "engine.h"
#include "monstertype.h"
#include "move.h"
#include "none.h"
#include "randomness.h"
#include "rest.h"
#include "sword.h"
#include "wander.h"

namespace Monsters {

std::unique_ptr<Action> default_behavior(Engine& engine, Monster& me) {
    // pursue Hero if monster can see him (If Hero sees me, I see him)
    if (me.is_visible() && engine.hero) {
        Vec from = me.get_position();
        Vec to = engine.hero->get_position();
        std::vector<Vec> path = engine.dungeon.calculate_path(from, to);
        if (path.size() > 2) {
            Vec direction = path.at(1) - path.at(0);
            return std::make_unique<Move>(direction);
        } else {
            // this is TEMPORARY until attack is implemented
            return std::make_unique<Rest>();
        }
    }
    // Monster doesn't see Hero
    if (probability(66)) {
        return std::make_unique<Wander>();
    } else {
        return std::make_unique<Rest>();
    }
}
constexpr int default_speed{8};
constexpr int default_health(3);

MonsterType goblin() {
    return {"goblin", default_speed, default_health * 2,
            std::make_shared<Sword>(2), default_behavior};
}

MonsterType zombie_small() {
    return {"zombie_small", default_speed, default_health,
            std::make_shared<Sword>(2), default_behavior};
}

MonsterType skeleton() {
    return {"skeleton", default_speed, default_health,
            std::make_shared<Sword>(2), default_behavior};
}

}  // namespace Monsters