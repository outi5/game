#include "settings.h"
#include <fstream>
#include <unordered_map>

Settings read_settings(const std::string& path) {
    std::ifstream input{path};
    if (!input) {
        throw std::runtime_error("Could not open filename: " + path);
    }
    std::unordered_map<std::string, std::string> parameters;
    std::string key, value;
    while (input >> key >> value) {
        parameters[key] = value;
    }

    Settings settings;
    settings.title = parameters.at("title");
    settings.screen_width = std::stoi(parameters.at("screen_width"));
    settings.screen_height = std::stoi(parameters.at("screen_height"));
    settings.tilesize = std::stoi(parameters.at("tilesize"));
    settings.zoom = std::stoi(parameters.at("zoom"));
    settings.tiles = parameters.at("tiles");
    settings.heros = parameters.at("heros");
    settings.monsters = parameters.at("monsters");
    settings.weapons = parameters.at("weapons");
    settings.items = parameters.at("items");
    settings.effects = parameters.at("effects");
    settings.map_width = std::stoi(parameters.at("map_width"));
    settings.map_height = std::stoi(parameters.at("map_height"));
    settings.room_placement_attempts = std::stoi(parameters.at("room_placement_attempts"));

    return settings;
}
