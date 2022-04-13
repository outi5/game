#pragma once

#include "actor.h"
#include "monstertype.h"
#include "animatedsprite.h"
#include <memory>
#include <vector>


class Monster : public Actor {
public:
    Monster(Engine& engine, const MonsterType& type, const Vec& position);
    virtual ~Monster() {}

    // orient monster towards direction
    void change_direction(const Vec& direction) override;
    void attack(Actor& defender) override;
    void update() override;
    std::unique_ptr<Action> take_turn() override;
    std::vector<Sprite> get_sprites() const override;

private:
    MonsterType type;
    AnimatedSprite sprite;
};
