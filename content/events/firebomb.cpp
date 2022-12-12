#include "firebomb.h"

#include <iostream>

#include "hit.h"

Firebomb::Firebomb(Vec location, Actor& actor)
    : location{location}, actor{actor}, damage{10} {}

void Firebomb::execute(Engine& engine) {
    if (frame_count == 0) {
        fire = engine.graphics.get_animated_sprite("fire", 1);
        number_of_frames = fire.number_of_frames();
    }

    engine.camera.add_overlay(location, fire.get_sprite());
    fire.update();
}

void Firebomb::when_done(Engine& engine) {
    Tile& tile = engine.dungeon.tiles(location);

    // create Hit event if there is an actor on the tile, as well as alway
    // damaging the actor 1 for firebombing
    if (tile.actor) {
        engine.events.add(Hit{*tile.actor, damage});
        engine.events.add(Hit{actor, 1});
    } else {
        engine.events.add(Hit{actor, 1});
    };
}