#include "engine/game.h"
#include <raylib.h>
#include "body/static.h"
#include "body/dynamic.h"
#include "iostream"
#include "initial.h"

void Game::Start(){
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Ngampung");
    SetTargetFPS(60);

    // starting the GLOBAL
    G_initial = new Initial();
    Render* block_of_water = new Static();
    block_of_water->Init(0, 0, true, "block_face");

    std::vector<Render*> water;
    water.push_back(block_of_water);

    this->to_render.push_back(std::make_pair(1, water));

    Dynamic* player = new Dynamic();
    player->Init(0, 0, false, "jawa");

    this->player = player;

    while (!WindowShouldClose()){
        // need to implement the update
        
        BeginDrawing();
        ClearBackground(BLUE);

        // displaying the screen
        // this->Display();
        // the character

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