#pragma once

#include <memory>

// forward declarations
class Engine;
class Action;
class Actor;

// the result of performing an Action
struct Result {
    bool succeeded{false};
    std::unique_ptr<Action> next_action{nullptr}; // allows chaining of actions
};


// base class for all actions
class Action {
public:
    virtual ~Action() {}
    // bind is called automatically within the engine,
    // you do not need to call it yourself
    void bind(std::shared_ptr<Actor> actor);

    // override perform in a derived class
    virtual Result perform(Engine& engine) = 0;

protected:
    // the actor who is performing this action
    std::shared_ptr<Actor> actor;
};
    

// Helper functions for generating results. You will use these inside
// Perform() of derived classes to signal whether an action was
// successful, failed, or that the actor needs to perform an
// alternative action instead.

// return success() if the actor completed the action and its turn is
// over
Result success();

// return success(another_action{}) if an actor has more actions to
// take
template <typename T>
Result success(const T& action) {
    return {true, std::make_unique<T>(action)};
}

// return failure() if the action cannot be performed and you'd like
// the actor to have another turn
Result failure();


// return alternative(another_action{}) to substitute the actor's
// current action for another
template <typename T>
Result alternative(const T& action) {
    return {false, std::make_unique<T>(action)};
}

