#include "engine.h"
#include "heros.h"
#include "monsters.h"

int main() {
    std::string filename{"settings.txt"};
    Settings settings = read_settings(filename);
    Engine engine{settings};

    engine.create_hero(Heros::dragon);
    for (int i = 0; i <= 5; ++i) {
        engine.create_monster(Monsters::demon_big());
    };
    for (int i = 0; i <= 10; ++i) {
        engine.create_monster(Monsters::zombie_small());
    };
    for (int i = 0; i <= 5; ++i) {
        engine.create_monster(Monsters::goblin());
    };
    for (int i = 0; i <= 10; ++i) {
        engine.create_monster(Monsters::skeleton());
    };
    engine.run();
}
