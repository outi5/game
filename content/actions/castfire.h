#pragma once

#include "action.h"

class CastFire : public Action {
    public:
    Result perform(Engine& engine) override;
};