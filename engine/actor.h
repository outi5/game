#pragma once

#include "vec.h"
#include "sprite.h"
#include <memory>

// forward declarations
class Engine;
class Action;


// base class for all interacting beings
class Actor {
public:
    Actor(Engine& engine, const Vec& position, int health, int team, int speed);

    virtual void change_direction(const Vec& direction);
    virtual void move_to(const Vec& position);
    const Vec& get_position() const;
    const Vec& get_direction() const;
    bool is_visible() const;

    void take_damage(int amount);
    virtual void attack(Actor& defender) = 0;
    
    virtual void update() = 0;
    virtual std::unique_ptr<Action> take_turn() = 0;
    virtual std::vector<Sprite> get_sprites() const = 0;

protected:
    Engine& engine;
    Vec position, direction;

public:
    // health gets reduced by calling take damage
    int health, max_health;
    bool alive;

    
    // teams can be used to determine who can attack whom
    int team;

    // speed is energy gain per turn, once an actor has enough energy
    // it can take a turn
    int speed, energy;
};

