#include <string>
#include <utility>

#pragma once

class System {
    public:
        std::pair<std::string, std::string> get_render_type();
        void set_render_type(std::pair<std::string, std::string> render);

    private:
        // first is type, second is thing
        std::pair<std::string, std::string> render;
};

extern System* G_System;