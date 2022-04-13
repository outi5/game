#pragma once

#include <memory>
#include <deque>

// forward declarations
class Engine;
class Actor;

// energy need for taking a turn
constexpr int DEFAULT_SPEED = 8;

// manages a collection of actors
class Actors {
public:
    Actors(int cost_of_turn=DEFAULT_SPEED);
    void add(std::shared_ptr<Actor> actor);
    void update();
    bool take_turn(Engine& engine);

    void advance();

    // for iterating over actors
    auto begin() { return std::begin(actors); }
    auto begin() const { return std::begin(actors); }
    auto end() { return std::end(actors); }
    auto end() const { return std::end(actors); }

private:
    int cost_of_turn;
    std::deque<std::shared_ptr<Actor>> actors;

    void remove_dead_actors();
};

