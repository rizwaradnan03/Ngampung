#include <engine/render.h>
#include <utility>
#include <string>

#pragma once

namespace Physic {
    std::pair<bool, std::string*> is_colliding(Render* me, Render* target);
}