#include "door.h"
#include "tile.h"


Door::Door() {}
    
Door::Door(bool is_horizontal, const Sprite& horizontal, const Sprite& vertical)
    :open_status{false}, is_horizontal{is_horizontal}, horizontal{horizontal},
     vertical{vertical} {

    // shift open door sprites by a few pixels to make tile appear walkable
    if (is_horizontal) {
        this->vertical.shift.x += -6;
    }
    else {
        this->horizontal.shift.x += 6;
        this->horizontal.shift.y -= 12;
    }
}

bool Door::is_open() const {
    return open_status;
}

void Door::open() {
    open_status = true;
}

void Door::close() {
    open_status = false;
}

const Sprite& Door::get_sprite() const {
    if ((is_open() && is_horizontal) || (!is_open() && !is_horizontal)) {
        return vertical;
    }
    else {
        return horizontal;
    }
}

