#pragma once

#include "graphics.h"
#include "input.h"
#include "camera.h"
#include "dungeon.h"
#include "actors.h"
#include "hero.h"
#include "monstertype.h"
#include "events.h"
#include "settings.h"
    
class Engine {
public:
    Engine(const Settings& settings);

    // Add a hero to the game with the given type
    void create_hero(const HeroType& type);

    // add a monster to the game with the given type
    void create_monster(const MonsterType& type);

    // start running the game
    void run();

    // access to engine components
    Graphics graphics;
    Camera camera;     
    Dungeon dungeon;
    Events events;
    std::shared_ptr<Hero> hero;
    
private:
    bool running;
    void handle_input();
    void update();
    void render();

    Input input;   // handles button presses and mouse clicks
    Actors actors; // manages actors and when they can take their turn
public:

};

