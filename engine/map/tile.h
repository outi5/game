#pragma once

#include "sprite.h"

// forward declaration
class Actor;

class Tile {
public:
    Tile();
    bool is_wall() const;
    bool is_door() const;
        
    enum class Type { None, Floor, Wall, Door };
    
    Type type;
    bool walkable;
    Sprite sprite;
    Actor* actor;
    bool visible;
};
