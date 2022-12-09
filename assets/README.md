# Engine update to allow animated effects
This updated engine makes rendering sprites at dungeon locations much
easier. This is useful for animated effects such as projectiles and
spells.

# Instructions
Replace your engine files with the ones included in this patch.

# List of changes
## Camera
Member function `add_overlay` was added to `class Camera` to allow for
easy drawing of a sprite at a dungeon location. Sprites passed into
this function are drawn on top of all others.
```C++
class Camera {
public:
    void add_overlay(const Vec& position, const Sprite& sprite);
}
```

## Graphics
Member function `get_animated_sprite` now takes two parameters to
control randomness in frame ordering:
```C++
class Graphics {
public:
    AnimatedSprite get_animated_sprite(const std::string& name, int ticks_per_frame,
                                       bool random_start=false, bool shuffle_order=false) const;
}
```

Because of this change `decorator.cpp`, `monster.cpp`, and `hero.cpp` were updated.


## AnimatedSprite
Member function `number_of_frames()` was added to `class
AnimatedSprite` to query the number of frames in the sequence.
```C++
class AnimatedSprite {
public:
    int number_of_frames() const;
}
```
This is useful for setting the `number_of_frames` of an `Event`:
```C++
class AnimationEvent : public Event {
public:
    AnimationEvent(Vec position) :position{position} {}
    void execute(Engine& engine) override {
        if (frame_count == 0) {
            AnimatedSprite sprite = engine.graphics.get_animated_sprite("name", 1);
            number_of_frames = sprite.number_of_frames();
        }
        engine.camera.add_overlay(position, sprite.get_sprite());
        sprite.update();
    }
private:
    Vec position;
    AnimatedSprite sprite;
};
```

## Settings
A new `effects` asset file entry was added:
```C++
struct Settings {
    std::string effects;
};
```
and the `Engine` constructor was updated to load it:
```C++
Engine::Engine(const Settings& settings) {
    ...
    graphics.load_spritesheet(settings.effects);
    ...
}
```
Add the following line to settings.txt:
```
effects assets/effects.txt
```
