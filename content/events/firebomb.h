#pragma once

#include "actor.h"
#include "animatedsprite.h"
#include "engine.h"
#include "event.h"

// Firebombs all tiles adjacent to the actor except walls
// and closed doors. Gives damage to all monsters on those
// tiles. Also causes some damage to hero for each use.
class Firebomb : public Event {
public:
    Firebomb(Vec location, Actor& actor);
    void execute(Engine& engine) override;
    void when_done(Engine& engine) override;

private:
    Vec location;
    Actor& actor;
    AnimatedSprite fire;
    int damage;
};