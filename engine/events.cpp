#include "events.h"
#include <algorithm>

void Events::execute(Engine& engine) {
    if (empty()) {
        return;
    }

    // process all current events
    for (auto& event : events) {
        event->execute(engine);
        event->update();
        if (event->is_done()) {
            event->when_done(engine);
        }
    }

    remove_done_events();
}

bool Events::empty() const {
    return events.empty();
}

void Events::remove_done_events() {
    auto it = std::remove_if(std::begin(events), std::end(events),
                             [](const auto& event) { return event->is_done(); });
    events.erase(it, std::end(events));
}
