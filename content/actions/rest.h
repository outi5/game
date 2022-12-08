#pragma once

#include "action.h"

// increases actor's health by 2
class Rest : public Action {
public:
    Result perform(Engine& engine) override;
};