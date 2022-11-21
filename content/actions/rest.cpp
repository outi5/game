#include "rest.h"

#include <iostream>

Result Rest::perform(Engine&) {
    std::cout << "SHHH, I'm Resting...\n";
    return success();
}
