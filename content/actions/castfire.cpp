#include "castfire.h"

#include <iostream>

#include "actor.h"
#include "engine.h"
#include "events.h"
#include "firebomb.h"
#include "hit.h"

Result CastFire::perform(Engine& engine) {
    Vec position = actor->get_position();
    std::vector<Vec> neighbors = engine.dungeon.neighbors(position);
    for (const Vec& neighbor : neighbors) {
        if (engine.dungeon.torch_positions.count(neighbor)) {
            std::cout << "TORCH!!!!\n";
            // get all adjacent tiles, including diagonals
            Vec directions[8] = {{1, 0},  {-1, 0},  {0, -1}, {0, 1},
                                 {1, -1}, {-1, -1}, {1, 1},  {-1, 1}};
            for (Vec i : directions) {
                Vec location = position - i;
                Tile& tile = engine.dungeon.tiles(location);

                // if tile is NOT a wall and NOT a closed door, Firebomb!!!
                if (!tile.is_wall() && !(tile.is_door() && !tile.walkable)) {
                    // Firebomb!!!
                    engine.events.add(Firebomb{location, *actor});
                };
            };

            return success();
        }
    }
    std::cout << "Uh, oh...NO TORCH! (This isn't good)\n";
    return failure();
}
