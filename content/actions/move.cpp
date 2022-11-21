#include "move.h"

#include <iostream>

#include "actor.h"
#include "engine.h"
#include "tile.h"

Move::Move(Vec direction) : direction{direction} {}

Result Move::perform(Engine& engine) {
    Vec position = actor->get_position();
    Vec new_position = position + direction;
    Tile& tile = engine.dungeon.tiles(new_position);
    if (tile.is_wall() || tile.actor) {
        return failure();
    }
    if (tile.is_door() && !tile.walkable) {
        Door& door = engine.dungeon.doors.at(new_position);
        door.open();
        tile.walkable = true;
        return success();
    }
    actor->change_direction(direction);
    actor->move_to(new_position);
    return success();
}