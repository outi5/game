#include "tile.h"

Tile::Tile()
    :type{Type::None}, walkable{false}, actor{nullptr} {}
    
bool Tile::is_wall() const {
    return type == Type::Wall;
}
    
bool Tile::is_door() const {
    return type == Type::Door;
}

