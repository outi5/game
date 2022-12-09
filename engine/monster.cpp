#include "monster.h"
#include "engine.h"

constexpr int TEAM_MONSTER = 1;
constexpr double WEAPON_ANGLE = 20;

Monster::Monster(Engine& engine, const MonsterType& type, const Vec& position)
    :Actor{engine, position, type.max_health, TEAM_MONSTER, type.speed}, type{type} {
    sprite = engine.graphics.get_animated_sprite(type.name, 1, true);
    type.weapon->sprite = engine.graphics.get_sprite(type.weapon->name);
    type.weapon->sprite.shift.x = sprite.get_sprite().size.x/8;
    type.weapon->sprite.angle = WEAPON_ANGLE;
    type.weapon->sprite.center = {type.weapon->sprite.size.x / 2, type.weapon->sprite.size.y};
}

void Monster::attack(Actor& defender) {
    type.weapon->use(engine, *this, defender);
}

void Monster::change_direction(const Vec& dir) {
    direction = dir;
    if (direction.x == 1) {
        sprite.flip(false);
        type.weapon->sprite.flip = false;
        type.weapon->sprite.shift.x = sprite.get_sprite().size.x/8;
        type.weapon->sprite.angle = WEAPON_ANGLE;
    } else if (direction.x == -1) {
        sprite.flip(true);
        type.weapon->sprite.flip = true;
        type.weapon->sprite.shift.x = -sprite.get_sprite().size.x/2;
        type.weapon->sprite.angle = -WEAPON_ANGLE;
    }
}

void Monster::update() {
    sprite.update();
}

std::unique_ptr<Action> Monster::take_turn() {
    return type.behavior(engine, *this);
}

std::vector<Sprite> Monster::get_sprites() const {
    auto s = sprite.get_sprite();
    return {type.weapon->sprite, s};
}
