#include "engine.h"
#include "builder.h"
#include "decorator.h"
#include "timer.h"
#include "settings.h"
#include "monster.h"

#include <fstream>
#include <unordered_map>
#include <sstream>
#include <iomanip>


Engine::Engine(const Settings& settings)
    :graphics{settings.title, settings.screen_width, settings.screen_height},
     camera{graphics, settings.tilesize, settings.zoom}, running{false} {

    // load sprites
    graphics.load_spritesheet(settings.tiles);
    graphics.load_spritesheet(settings.heros);
    graphics.load_spritesheet(settings.monsters);
    graphics.load_spritesheet(settings.weapons);
    graphics.load_spritesheet(settings.items);
    graphics.load_spritesheet(settings.effects);
    
    // create dungeon layout
    Builder builder(settings.room_placement_attempts);
    auto [layout, rooms] = builder.generate(settings.map_width, settings.map_height);

    // assign sprites to dungeon tiles
    Decorator decorator(graphics, layout, rooms);
    dungeon = decorator.create_dungeon();
}

void Engine::run() {
    running = true;
    Timer timer;
    double accumulated_time{0.0};
    constexpr double timestep_per_update{0.1};

    // main game loop
    while (running && hero->alive) {
        // handling input and rendering produce time, whereas the
        // update loop consumes time in fixed steps
        accumulated_time += timer.elapsed(); 

        handle_input();

        // if we have accumulated enough rendering time for an update,
        // then take it
        while (accumulated_time >= timestep_per_update) {
            update();
            accumulated_time -= timestep_per_update;
        }

        // redraw everything on the screen
        render();
    }
}

void Engine::create_hero(const HeroType& type) {
    // place hero at an empty tile
    auto position = dungeon.random_open_room_tile();
    hero = std::make_shared<Hero>(*this, type, position);
    actors.add(hero);
}

void Engine::create_monster(const MonsterType& type) {
    // place monster at an empty tile
    auto position = dungeon.random_open_room_tile();
    auto monster = std::make_shared<Monster>(*this, type, position);
    actors.add(monster);
}

void Engine::handle_input() {
    auto inputs = input.get_input();
    for (const auto& i : inputs) {
        if (i == "Quit") { // close of game window
            running = false;
            break;
        }
        // handle change to camera zoom
        else if (i == "-") {
            camera.zoom_out();
        }
        else if (i == "=") { // also handles + key
            camera.zoom_in();
        }
        // otherwise pass the key onto the hero who may react to it
        else if (hero) {
            hero->handle_input(i);
        }
    }
}

void Engine::update() {
    camera.update();
    
    // update all dungeon tiles, mostly updating animate sprites
    dungeon.update();

    // let actors know that game has progressed, they may update their sprites
    actors.update();

    while (events.empty() && actors.take_turn(*this)) {
        // if there are no outstanding events, let actors take turns
        // until events are produced or an actor cannot take a turn
    }

    // an actor may have produced an event, so process it
    events.execute(*this);
}

void Engine::render() {
    graphics.clear();
    camera.render(dungeon);
    camera.render(actors);
    camera.render_fog(dungeon);
    camera.render_overlays();
    if (hero) {
        camera.render_healthbar(hero->health, hero->type.max_health);
    }
    graphics.redraw();
}

