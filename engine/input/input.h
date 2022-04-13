#pragma once

#include <vector>
#include <string>

class Input {
public:
    Input();
    ~Input();

    // returns list of all input events since last call
    std::vector<std::string> get_input();

    // mouse position of last click
    int mouse_x, mouse_y;
};
