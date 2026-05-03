#include <raylib.h>
#include <engine/game.h>
#include <iostream>
#include <initial.h>
#include <namespace/system.h>
#include <singleton/mouse.h>
#include <engine/render_type/world.h>
#include <engine/render_type/gui.h>
#include <engine/system.h>

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

    G_System->set_render_type(std::make_pair("WORLD", "main"));

    while (!WindowShouldClose()){
        sys::fps_counter();

        if(G_System->get_render_type().first == "GUI"){
            G_RENDER_TYPE_gui->Run();
        }else if(G_System->get_render_type().first == "WORLD"){
            G_RENDER_TYPE_world->Run();
        }
    }
    
    CloseWindow();
}

void Game::init_global(){
    G_initial = new Initial();
    G_System = new System();
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