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

    // if not walkable and not a door, allow retry
    if (tile.is_wall() || tile.actor) {
        return failure();
    }

    // if a closed door, open it
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