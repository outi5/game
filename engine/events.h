#pragma once

#include "event.h"
#include <memory>
#include <list>

// forward declaration
class Engine;


class Events {
public:
    // add an event to the list of events
    template <typename T>
    void add(T&& event) {
        events.push_back(std::make_unique<T>(std::move(event)));
    }

    // update all currently running events
    void execute(Engine& engine);
    bool empty() const;
    
private:
    std::list<std::unique_ptr<Event>> events;
    void remove_done_events();
};
