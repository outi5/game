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

                // if tile is NOT a wall and NOT a cloesed door
                if (!tile.is_wall() && !(tile.is_door() && !tile.walkable)) {
                    std::cout << "fire at: " << location << std::endl;

                    /*
                       I feel like this is the point were I need to switch to
                       an animation event, but I can't figure out how to do so.
                       I'm also not sure why it's requiring me to make fire a
                       const here, but it is.
                    */
                    // const AnimatedSprite& fire =
                    //     engine.graphics.get_animated_sprite("fire", 6);

                    engine.events.add(Firebomb{location, *actor});
                    // engine.camera.add_overlay(location, fire.get_sprite());

                    /*
                       If I could get the previous 3 lines to be an event,
                       then this next part could be the "when_done" for that
                       event, which would seem correct.
                    */
                    // if (tile.actor) {
                    //     engine.events.add(Hit{*tile.actor, 10});
                    // };
                };
            };

            return success();
        }
    }
    std::cout << "Uh, oh...NO TORCH!\n";
    return failure();
}
