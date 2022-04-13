#include "action.h"

void Action::bind(std::shared_ptr<Actor> actor) {
    this->actor = actor;
}

Result success() {
    return {true, nullptr};
}
    
Result failure() {
    return {false, nullptr};
}
