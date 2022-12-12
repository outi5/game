#pragma once

#include "action.h"

// Castfire is called with the T key
class CastFire : public Action {
public:
    Result perform(Engine& engine) override;
};