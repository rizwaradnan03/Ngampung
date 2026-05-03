#include <raylib.h>
#include <vector>
#include <body/static.h>
#include <body/dynamic.h>
#include <engine/gui.h>
#include <string>

#pragma once

class Render_Type_World {
    public:
        void Set(Dynamic* player, const std::pair<std::vector<Static*>*, std::vector<Dynamic*>*>& set);
        void Run();
        void Habit(std::string* action);
        void camera_alligner();

    private:
        std::vector<Static*> to_render_static;
        std::vector<Dynamic*> to_render_dynamic;
        Dynamic* player;
        Camera2D camera;
};

extern Render_Type_World* G_RENDER_TYPE_world;