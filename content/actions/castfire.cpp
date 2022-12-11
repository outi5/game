#include "castfire.h"

#include <iostream>

#include "actor.h"
#include "engine.h"
#include "events.h"
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
                // if tile is NOT a wall and NOT a cloesed door
                if (!tile.is_wall() && !(tile.is_door() && !tile.walkable)) {
                    std::cout << "fire at: " << location << std::endl;

                    const Sprite& fire = engine.graphics.get_sprite("fire");
                    engine.camera.add_overlay(location, fire);

                    if (tile.actor) {
                        engine.events.add(Hit{*tile.actor, 10});
                    };
                };
            };

            return success();
        }
    }
    std::cout << "Uh, oh...NO TORCH!\n";
    return failure();
}
