#pragma once

#include <string>

// general settings for game
struct Settings {
    std::string title; // title in window bar

    // screen dimensions in pixels
    int screen_width;
    int screen_height;

    // number of pixels for a square tile
    int tilesize;
    int zoom; // zoom level of camera

    // paths to asset files
    std::string tiles;
    std::string heros;
    std::string monsters;
    std::string weapons;
    std::string items;
    std::string effects;

    // dungeon parameters
    int map_width;
    int map_height;
    int room_placement_attempts; // controls the number of rooms
};

Settings read_settings(const std::string& path);
