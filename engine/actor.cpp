#include "actor.h"
#include "engine.h"
#include <sstream>
#include <algorithm>

Actor::Actor(Engine& engine, const Vec& position, int health, int team, int speed)
    :engine{engine}, position{position}, direction{1, 0},
     health{health}, max_health{health}, alive{true}, team{team}, speed{speed}, energy{0} {
    
    // place actor onto its dungeon tile
    Tile& tile = engine.dungeon.tiles(position);
    if (tile.actor == nullptr) {
        tile.actor = this;
    }
    else { // an actor is already on this tile, throw error
        std::stringstream ss{"An actor is already on tile: "};
        ss << position;
        throw std::runtime_error(ss.str());
    }
}
    
void Actor::change_direction(const Vec& dir) {
    direction = dir;
}
    
void Actor::move_to(const Vec& new_position) {
    Tile& old_tile = engine.dungeon.tiles(position);
    Tile& new_tile = engine.dungeon.tiles(new_position);
    std::swap(old_tile.actor, new_tile.actor);
    position = new_position;
}

const Vec& Actor::get_position() const {
    return position;
}

const Vec& Actor::get_direction() const {
    return direction;
}

bool Actor::is_visible() const {
    // actor is visible if tile is visible
    const Tile& tile = engine.dungeon.tiles(position);
    return tile.visible;
}

void Actor::take_damage(int amount) {
    health -= amount;
    std::clamp(health, 0, max_health);
}
