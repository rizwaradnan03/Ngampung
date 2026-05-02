#include <vector>
#include <utility>
#include <body/dynamic.h>
#include <body/static.h>
#include <string>
#include <chrono>
#include <string.h>

#pragma once

class Game {
    public:
        void Start();
        void init_global();

        std::string get_render_type();
        void set_render_type(std::string render_type);

    private:
        std::string render_type;
};