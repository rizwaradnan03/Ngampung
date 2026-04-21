#include "engine/game.h"
#include <raylib.h>
#include "body/static.h"
#include "iostream"

void Game::Start(){
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    Render* block_of_water = new Render();
    block_of_water->Init(400, 200, true, "block_face");

    std::vector<Render*> water;
    water.push_back(block_of_water);

    this->to_render.push_back(std::make_pair(1, water));

    InitWindow(screenWidth, screenHeight, "Ngampung");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        // need to implement the update
        
        BeginDrawing();
        ClearBackground(BLUE);

        Game::Display();

        EndDrawing();
    }
    
    CloseWindow();
}

void Game::Display(){
    for(int i = 0;i < this->to_render.size();i++){
        for(int j = 0;j < this->to_render[i].second.size();j++){
            this->to_render[i].second[j]->Display();
            std::cout << "sleeping child : " << this->to_render.size() << std::endl;
        }
    }
}