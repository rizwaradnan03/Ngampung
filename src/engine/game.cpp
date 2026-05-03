#include <raylib.h>
#include <engine/game.h>
#include <iostream>
#include <initial.h>
#include <namespace/system.h>
#include <singleton/mouse.h>
#include <engine/render_type/world.h>
#include <engine/render_type/gui.h>

// std::vector<Static*> RunStarter(){
//     std::vector<Static*> tmp;
//     int32_t h = 3;

//     std::vector<int32_t> masks = {1, 2, 3};

//     Static* blck = new Static();
//     blck->Init(60, 240, 30, 30, h, true, true, 1, &masks, "BLOCK_dirt");

//     tmp.push_back(blck);

//     int cur_x = 0;
//     int cur_y = 300;
//     while(cur_y < 600){
//         while(cur_x <= 780){
//             Static* block = new Static();
//             block->Init(cur_x, cur_y, 30, 30, h, true, true, 1, &masks, "BLOCK_dirt");

//             tmp.push_back(block);
//             cur_x += 30;
//         }

//         cur_y += 30;
//         cur_x = 0;
//     }

//     return tmp;
// }

void Game::Start(){
    const int screenWidth = 800;
    const int screenHeight = 600;
    // const int screenWidth = GetMonitorWidth(0);
    // const int screenHeight = GetMonitorHeight(0);
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);

    InitWindow(screenWidth, screenHeight, "Ngampung");
    InitAudioDevice();
    SetTargetFPS(60);

    this->init_global();

    this->set_render_type("WORLD");

    while (!WindowShouldClose()){
        System::fps_counter();

        if(this->get_render_type() == "GUI"){
            G_RENDER_TYPE_gui->Run();
        }else if(this->get_render_type() == "WORLD"){
            G_RENDER_TYPE_world->Run();
        }
    }
    
    CloseWindow();
}

void Game::init_global(){
    G_initial = new Initial();
    G_SINGLETON_mouse = new SINGLETON_Mouse();
    G_RENDER_TYPE_world = new Render_Type_World();
    G_RENDER_TYPE_gui = new Render_Type_Gui();
}

std::string Game::get_render_type(){
    return this->render_type;
}

void Game::set_render_type(std::string render_type){
    this->render_type = render_type;
}