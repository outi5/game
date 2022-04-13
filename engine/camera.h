#pragma once

#include "vec.h"
#include <unordered_set>
#include <vector>
#include <functional>

// forward declaration
class Graphics;
struct Sprite;
class Dungeon;
class Actors;
class Engine;


class Camera {
public:
    Camera(Graphics& graphics, int tilesize, int zoom=1);

    // drawing functions
    void render(const Vec& position, const Sprite& sprite) const;
    void render(const Dungeon& dungeon) const;
    void render(const Actors& actors) const;
    void render_fog(const Dungeon& dungeon) const;
    void render_rect(const Vec& position, int red, int green, int blue, int alpha) const;
    void render_healthbar(int current_health, int max_health);
    void add_overlay(std::function<void()> overlay);
    void render_overlays();

    // translate actor positions to pixel positions
    Vec world_to_screen(const Vec& position) const;

    // position camera over this position
    void move_to(const Vec& position);
    void zoom_in();
    void zoom_out();

    
private:
    Graphics& graphics;
    int tilesize;
    int zoom;
    Vec location, screen_center;

    Vec min, max; // world coordinates of min/max tiles that are visible
    void calculate_visibility_limits();
    bool within_view(const Vec& position) const;

    std::vector<std::function<void()>> overlays;
};

