#include "opendoor.h"

#include "actor.h"
#include "engine.h"
#include "updatefov.h"

OpenDoor::OpenDoor(Vec door_position) : door_position{door_position} {}

Result OpenDoor::perform(Engine& engine) {
    Tile& tile = engine.dungeon.tiles(door_position);
    Door& door = engine.dungeon.doors.at(door_position);
    door.open();
    tile.walkable = true;
    return success();
}