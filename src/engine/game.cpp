#include <engine/game.h>
#include <raylib.h>
#include <body/static.h>
#include <body/dynamic.h>
#include <iostream>
#include <initial.h>
#include <cstdint>

std::vector<Static*> RunStarter(){
    std::vector<Static*> tmp;
    int32_t h = 3;

    std::vector<int32_t> masks = {1, 2, 3};

    int cur_x = 0;
    int cur_y = 300;
    while(cur_y < 600){
        while(cur_x <= 780){
            Static* block = new Static();
            block->Init(cur_x, cur_y, 30, 30, h, true, true, 1, &masks, "BLOCK_dirt");

            tmp.push_back(block);
            cur_x += 30;
        }

        cur_y += 30;
        cur_x = 0;
    }

    return tmp;
}

void Game::Start(){
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Ngampung");
    InitAudioDevice();
    SetTargetFPS(60);

    this->init_global();

    std::vector<Static*> value = RunStarter();

    this->to_render_static = value;

    Dynamic* player = new Dynamic();

    std::vector<int32_t> masks = {1, 2, 3};

    player->Init(30, 0, 30, 30, 100, false, true, 1, &masks, "BLOCK_player");

    this->player = player;

    auto start_time = std::chrono::high_resolution_clock::now();
    this->set_run_time(start_time);

    // init camera
    Camera2D cam = {0};
    cam.target = {(float)this->player->get_x(), (float)this->player->get_y()};
    cam.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    this->camera = cam;

    while (!WindowShouldClose()){
        this->background_action();
        player->Movement();

        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode2D(this->camera);

        this->Habit(nullptr);

        player->Run(this->to_render_static, this->to_render_dynamic);

        EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
}

void Game::init_global(){
    G_initial = new Initial();
}

int32_t Game::get_frame_count(){
    return this->frame_count;
}

void Game::set_frame_count(int32_t value){
    this->frame_count = value;
}

Dynamic* Game::get_player(){
    return this->player;
}

void Game::set_player(Dynamic* player){
    this->player = player;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Game::get_run_time(){
    return this->run_time;
}

void Game::set_run_time(std::chrono::time_point<std::chrono::high_resolution_clock> value){
    this->run_time = value;
}

void Game::Habit(std::string* action){
    for(int i = 0;i < this->to_render_static.size();i++){
        this->to_render_static[i]->Run(action, to_render_static);
    }
}

void Game::background_action(){
    this->fps_counter();
    this->camera_alligner();
}

void Game::fps_counter(){
    auto current_time = std::chrono::high_resolution_clock::now();
    this->set_frame_count(this->get_frame_count() + 1);

    std::chrono::duration<float> differ = current_time - this->get_run_time();
    std::string strf = "Frame : " + std::to_string(this->frame_count);

    if(differ.count() >= 1.0f){
        float fps = static_cast<float>(this->frame_count) / differ.count();
        this->set_frame_count(0);
        this->set_run_time(current_time);
    }

    DrawText(strf.c_str(), 0, 0, 20, RED);
}

void Game::camera_alligner(){
    this->camera.target = {(float)this->player->get_x(), (float)this->player->get_y()};
}