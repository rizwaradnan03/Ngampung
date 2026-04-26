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

    int cur_x = 0;
    int cur_y = 300;
    while(cur_y < 600){
        while(cur_x <= 780){
            // Static* block = new Static();
            // block->Init(cur_x, cur_y, &h, true, true, "BLOCK_face");

            // tmp.push_back(block);
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

    // starting the GLOBAL
    G_initial = new Initial();

    std::vector<Static*> value = RunStarter();

    this->to_render_static.push_back(std::make_pair(1, value));

    Dynamic* player = new Dynamic();
    int32_t h = 100;

    std::vector<int32_t> masks = {1, 2, 3};

    player->Init(30, 0, &h, false, true, &masks, "BLOCK_face");

    this->player = player;

    while (!WindowShouldClose()){
        player->Movement();

        BeginDrawing();
        ClearBackground(BLUE);

        this->Habit(nullptr);

        player->Run(this->to_render_static, this->to_render_dynamic);

        EndDrawing();
    }
    
    CloseWindow();
}

void Game::Habit(std::string* action){
    for(int i = 0;i < this->to_render_static.size();i++){
        for(int j = 0;j < this->to_render_static[i].second.size();j++){
            this->to_render_static[i].second[j]->Run(action, this->to_render_static);
        }
    }
}