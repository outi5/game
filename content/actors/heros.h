#pragma once

#include "axe.h"
#include "castfire.h"
#include "closedoor.h"
#include "herotype.h"
#include "move.h"
#include "none.h"
#include "rest.h"
#include "sword.h"

namespace Heros {

const std::unordered_map<std::string, Reaction> key_bindings = {
    {"Right",
     []() {
         return std::make_unique<Move>(Vec{1, 0});
     }},
    {"Left",
     []() {
         return std::make_unique<Move>(Vec{-1, 0});
     }},
    {"Up",
     []() {
         return std::make_unique<Move>(Vec{0, 1});
     }},
    {"Down",
     []() {
         return std::make_unique<Move>(Vec{0, -1});
     }},
    {"Z", []() { return std::make_unique<Rest>(); }},
    {"T", []() { return std::make_unique<CastFire>(); }},
    {"C", []() { return std::make_unique<CloseDoor>(); }}};

constexpr int default_speed{8};
int default_health = 20;
const HeroType nobody{
    "none", default_speed, default_health, std::make_shared<None>(), {}};
const HeroType knight{"knight", default_speed, default_health,
                      std::make_shared<None>(), key_bindings};
const HeroType elf{"elf", default_speed, default_health,
                   std::make_shared<Axe>(4), key_bindings};
const HeroType wizard{"wizard", default_speed, default_health,
                      std::make_shared<None>(), key_bindings};
const HeroType dragon{"dragon", default_speed, default_health,
                      std::make_shared<Axe>(3), key_bindings};
}  // namespace Heros
