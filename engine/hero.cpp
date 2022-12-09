#include "hero.h"

#include "action.h"
#include "engine.h"

constexpr int TEAM_HERO = 0;
constexpr double WEAPON_ANGLE = 20;

Hero::Hero(Engine& engine, HeroType type, const Vec& position)
    :Actor{engine, position, type.max_health, TEAM_HERO, type.speed}, type{type} {
    move_to(position);
    sprite = engine.graphics.get_animated_sprite(type.name, 1, true);
    type.weapon->sprite = engine.graphics.get_sprite(type.weapon->name);
    type.weapon->sprite.shift.x = sprite.get_sprite().size.x/8;
    type.weapon->sprite.angle = WEAPON_ANGLE;
    type.weapon->sprite.center = {type.weapon->sprite.size.x / 2, type.weapon->sprite.size.y};
}

void Hero::change_direction(const Vec& dir) {
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

void Hero::move_to(const Vec& new_position) {
    Actor::move_to(new_position);
    engine.dungeon.update_visibility(position);
    engine.camera.move_to(position);
}

void Hero::attack(Actor& defender) {
    type.weapon->use(engine, *this, defender);
}

void Hero::update() {
    sprite.update();
}

std::unique_ptr<Action> Hero::take_turn() {
    auto action = std::move(next_action);
    next_action = nullptr;
    return action;
}

std::vector<Sprite> Hero::get_sprites() const {
    auto s = sprite.get_sprite();
    return {type.weapon->sprite, s};
}

void Hero::handle_input(const std::string& key_name) {
    auto search = type.key_bindings.find(key_name);
    if (search != type.key_bindings.end()) {
        Reaction reaction = search->second;
        next_action = reaction();
    }
}
