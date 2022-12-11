#pragma once

#include "actor.h"
#include "event.h"
#include "animatedsprite.h"
#include "engine.h"

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