#pragma once

#include "action.h"
#include "tile.h"

class OpenDoor : public Action {
public:
    OpenDoor(Vec door_postition);
    Result perform(Engine& engine) override;
private:
    Vec door_position;
};