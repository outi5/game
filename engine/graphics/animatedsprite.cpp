#include "animatedsprite.h"


AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(const std::vector<Sprite>& sprites, int ticks_per_frame,
                               int starting_frame)
    :visible{true}, sprites{sprites}, ticks_per_frame{ticks_per_frame},
     current_frame{starting_frame}, time{0} {}

void AnimatedSprite::flip(bool flip) {
    for (auto& sprite : sprites) {
        sprite.flip = flip;
    }
}

void AnimatedSprite::update() {
    if (!visible) {
        return;
    }
    ++time;
    if (time >= ticks_per_frame) {
        current_frame = (current_frame + 1) % sprites.size();
    }
}

Sprite AnimatedSprite::get_sprite() const {
    return sprites.at(current_frame);
}

int AnimatedSprite::number_of_frames() const {
    return sprites.size();
}
