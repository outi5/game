#include "actors.h"
#include "actor.h"
#include "action.h"

Actors::Actors(int cost_of_turn)
    :cost_of_turn{cost_of_turn} {}

void Actors::add(std::shared_ptr<Actor> actor) {
    actors.push_back(actor); 
}

void Actors::update() {
    // tell all actors to update
    for (auto& actor : actors) {
        actor->update();
    }
}

bool Actors::take_turn(Engine& engine) {
    remove_dead_actors();
    if (actors.empty()) {
        return false;
    }

    auto actor = actors.front();
    
    if (actor->energy < cost_of_turn) {
        advance();
        return true; // made progress
    }
    
    // get the actors next action
    auto action = actor->take_turn();
    // if actor produced no action, then wait for them by not advancing to next actor
    if (!action) {
        return false;
    }
    
    // bind actor to their actions
    action->bind(actor);
    
    // perform actor's action and all resulting actions until done
    while (true) {
        auto result = action->perform(engine);
        
        if (!result.succeeded && !result.next_action) {
            // action failed and no alternative, don't advance to next actor
            return true;
        }
        
        if (result.next_action) {
            // if there is a subsequent action, set it as the next one to perform
            action = std::move(result.next_action);
            action->bind(actor);
        }
        else {
            // chain of actions are complete, reduce the actor's energy
            actor->energy %= cost_of_turn;
            advance();
            return true;
        }
    }
}

void Actors::advance() {
    if (actors.empty()) {
        return;
    }
    auto actor = actors.front();
    actors.pop_front();
    actors.push_back(actor);
    // give actor some energy for their next turn
    actor->energy += actor->speed;
}

void Actors::remove_dead_actors() {
    auto it = std::remove_if(std::begin(actors), std::end(actors),
                             [](const auto& actor) { return !actor->alive; });
    actors.erase(it, std::end(actors));
}
