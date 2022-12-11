#include "firebomb.h"

#include <iostream>

#include "actor.h"
#include "engine.h"
#include "event.h"
#include "hit.h"

Firebomb::Firebomb(Vec location, Actor& actor)
    : Event{fire.number_of_frames()},
      location{location},
      actor{actor},
      damage{10} {}

void Firebomb::execute(Engine& engine) {
    if (frame_count == 0) {
        AnimatedSprite fire = engine.graphics.get_animated_sprite("fire", 1);
        std::cout << "Number of Frames: " << number_of_frames << std::endl;
    }

    engine.camera.add_overlay(location, fire.get_sprite());
    fire.update();
}

void Firebomb::when_done(Engine& engine) {
    Tile& tile = engine.dungeon.tiles(location);
    if (tile.actor) {
        engine.events.add(Hit{*tile.actor, damage});
    } else {
        engine.events.add(Hit{actor, 0});
    };
}