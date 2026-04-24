#include "engine/game.h"
#include <raylib.h>
#include "body/static.h"
#include "body/dynamic.h"
#include "iostream"
#include "initial.h"

std::vector<Render*> RunStarter(){
    std::vector<Render*> tmp;
    
    int cur_x = 0;
    int cur_y = 300;
    while(cur_y < 600){
        while(cur_x <= 780){
            Render* block = new Static();
            block->Init(cur_x, cur_y, true, "block_face");

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
    SetTargetFPS(60);

    // starting the GLOBAL
    G_initial = new Initial();

    std::vector<Render*> value = RunStarter();

    this->to_render.push_back(std::make_pair(1, value));

    Dynamic* player = new Dynamic();
    player->Init(0, 0, false, "jawa");

    this->player = player;

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLUE);

        // displaying the screen
        this->Display();
        DrawRectangle(0, 0, 20, 20, RED);

        // displaying the character here

        EndDrawing();
    }
    
    CloseWindow();
}

void Game::Display(){
    for(int i = 0;i < this->to_render.size();i++){
        for(int j = 0;j < this->to_render[i].second.size();j++){
            this->to_render[i].second[j]->Display();
        }
    }
}