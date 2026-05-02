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
        void Habit(std::string* action);
        void background_action();
        void fps_counter();
        void camera_alligner();
        void init_global();

        int32_t get_frame_count();
        void set_frame_count(int32_t value);

        Dynamic* get_player();
        void set_player(Dynamic* player);

        std::pair<std::string*, std::pair<int32_t, int32_t>> get_mouse();
        void set_mouse(std::pair<std::string*, std::pair<int32_t, int32_t>> mouse);

        std::chrono::time_point<std::chrono::high_resolution_clock> get_run_time();
        void set_run_time(std::chrono::time_point<std::chrono::high_resolution_clock> value);

    private:
        float fps;
        int32_t frame_count;
        std::vector<Static*> to_render_static;
        std::vector<Dynamic*> to_render_dynamic;
        std::chrono::time_point<std::chrono::high_resolution_clock> run_time;

        std::pair<std::string*, std::pair<int32_t, int32_t>> mouse;

        Dynamic* player;
        Camera2D camera;
};