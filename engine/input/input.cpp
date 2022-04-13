#include "input.h"
#include <SDL2/SDL.h>
#include <stdexcept>

Input::Input()
    :mouse_x{-1}, mouse_y{-1} {
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::string msg{"Unable to initialize SDL Events: "};
        msg += SDL_GetError();
        SDL_Quit();
        throw std::runtime_error(msg);
    }
}

Input::~Input() {
    SDL_Quit();
}

std::vector<std::string> Input::get_input() {
    std::vector<std::string> inputs;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            inputs.push_back("Quit");
        }
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            std::string key_name = SDL_GetKeyName(key);
            inputs.push_back(key_name);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                inputs.push_back("Click");
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            }
        }
    }
    return inputs;
}
