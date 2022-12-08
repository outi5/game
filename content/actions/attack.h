#pragma once

#include "action.h"

class Attack : public Action {
public:
    Attack(Actor& defender);
    Result perform(Engine& engine) override;

private:
    Actor& defender;
};