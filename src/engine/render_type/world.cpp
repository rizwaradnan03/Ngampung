#include <engine/render_type/world.h>
#include <singleton/mouse.h>

Render_Type_World* G_RENDER_TYPE_world = nullptr;

void Render_Type_World::Set(Dynamic* player, const std::pair<std::vector<Static*>*, std::vector<Dynamic*>*>& set){
    this->to_render_static = *set.first;
    this->to_render_dynamic = *set.second;
    this->player = player;

    // camera
    Camera2D cam = {0};
    cam.target = {(float)this->player->get_x(), (float)this->player->get_y()};
    cam.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    this->camera = cam;
}

void Render_Type_World::Run(){
    bool is_free = this->player->get_is_free();
    if(is_free == true){
        delete player;
        player = nullptr;
    }

    player->box_collide_checker(this->to_render_static, this->to_render_dynamic);
    player->Movement();

    BeginDrawing();
    ClearBackground(BLUE);
    BeginMode2D(this->camera);

    std::pair<std::string*, std::pair<int32_t, int32_t>>p_run = player->Run(this->to_render_static, this->to_render_dynamic);
    G_SINGLETON_mouse->set_mouse(p_run);

    this->Habit(nullptr);
}

void Render_Type_World::Habit(std::string* action){
    for(int i = 0;i < this->to_render_static.size();i++){
        Static* obj = this->to_render_static[i];

        bool is_free = this->to_render_static[i]->get_is_free();
        if(is_free == true){
            delete this->to_render_static[i];
            this->to_render_static.erase(this->to_render_static.begin() + i);
            i--;
        }else{
            this->to_render_static[i]->Run(action, to_render_static);
        }

    }
}

// camera alligned i need this
// void Game::camera_alligner(){
//     this->camera.target = {(float)this->player->get_x(), (float)this->player->get_y()};
// }