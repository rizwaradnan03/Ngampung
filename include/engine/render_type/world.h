#include <raylib.h>
#include <vector>
#include <nodes/body/static.h>
#include <nodes/body/dynamic.h>
#include <sources/objects/player.h>
#include <engine/gui.h>
#include <string>

#pragma once

class Render_Type_World {
    public:
        void Set(std::string type);
        void Run();
        void Habit(std::string* action);
        void camera_alligner();

        std::vector<Static*> get_to_render_static();
        void set_to_render_static(std::vector<Static*> to_render_static);

        std::vector<Dynamic*> get_to_render_dynamic();
        void set_to_render_dynamic(std::vector<Dynamic*> to_render_dynamic);

        Player* get_player();
        void set_player(Player* player);

        Camera2D get_camera();
        void set_camera(Camera2D camera);

        void R_main();

    private:
        std::vector<Static*> to_render_static;
        std::vector<Dynamic*> to_render_dynamic;
        Player* player;
        Camera2D camera;
};

extern Render_Type_World* G_RENDER_TYPE_world;