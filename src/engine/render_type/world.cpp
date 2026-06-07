#include <engine/render_type/world.h>
#include <singleton/mouse.h>
#include <nodes/body/body.h>
#include <iostream>
#include <sources/objects/player.h>

Render_Type_World* G_RENDER_TYPE_world = nullptr;

void Render_Type_World::R_main(){
    std::vector<Static*> tmp;
    int32_t h = 3;

    std::vector<int32_t>* masks = new std::vector<int32_t>{1, 2, 3};

    Static* blck = new Static();
    blck->Init(60, 240, 30, 30, "BLOCK", h, true, true, 1, masks, "BLOCK_dirt");

    tmp.push_back(blck);

    int cur_x = 0;
    int cur_y = 300;
    while(cur_y < 600){
        while(cur_x <= 780){
            Static* block = new Static();
            block->Init(cur_x, cur_y, 30, 30, "BLOCK", h, true, true, 1, masks, "BLOCK_dirt");

            tmp.push_back(block);
            cur_x += 30;
        }

        cur_y += 30;
        cur_x = 0;
    }

    this->set_to_render_static(tmp);
}

void Render_Type_World::Set(std::string type){
    if(type == "main"){
        R_main();
    }
    
    Player* player = new Player();
    std::vector<int32_t>* masks = new std::vector<int32_t>{1, 2, 3};
    player->Init(0, 0, 30, 30, 100, false, true, 1, masks, "BLOCK_player");
    this->set_player(player);

    Camera2D cam = {0};
    cam.target = {(float)this->player->get_x(), (float)this->player->get_y()};
    cam.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    this->set_camera(cam);
}

void Render_Type_World::Run(){
    this->camera_alligner();
    
    player->box_collide_checker(this->get_to_render_static(), this->get_to_render_dynamic());
    player->Movement();

    BeginDrawing();
    ClearBackground(BLUE);
    BeginMode2D(this->get_camera());

    player->Run(nullptr, this->get_to_render_static(), this->get_to_render_dynamic());
    this->Habit(nullptr);

    EndMode2D();

    player->fixed_on_screen_run();

    EndDrawing();
}

std::vector<Static*> Render_Type_World::get_to_render_static(){
    return this->to_render_static;
}

void Render_Type_World::set_to_render_static(std::vector<Static*> to_render_static){
    this->to_render_static = to_render_static;
}

std::vector<Dynamic*> Render_Type_World::get_to_render_dynamic(){
    return this->to_render_dynamic;
}

void Render_Type_World::set_to_render_dynamic(std::vector<Dynamic*> to_render_dynamic){
    this->to_render_dynamic = to_render_dynamic;
}

Player* Render_Type_World::get_player(){
    return this->player;
}

void Render_Type_World::set_player(Player* player){
    this->player = player;
}

Camera2D Render_Type_World::get_camera(){
    return this->camera;
}

void Render_Type_World::set_camera(Camera2D camera){
    this->camera = camera;
}

void Render_Type_World::Habit(std::string* action){
    std::vector<Static*> ts = this->get_to_render_static();
    std::vector<Dynamic*> td = this->get_to_render_dynamic();

    int32_t sz = ts.size();
    int32_t dz = td.size();

    for(int i = 0;i < sz + dz;i++){
        Body* obj;

        if(i < sz){
            obj = ts[i];
        }else{
            obj = td[i - sz];
        }

        bool is_free = obj->get_is_free();
        if(is_free == true){
            delete obj;
            if(i < sz){
                this->to_render_static.erase(this->to_render_static.begin() + i);
            }else{
                this->to_render_dynamic.erase(this->to_render_dynamic.begin() + (i - sz));
            }

            if(i == 0){
                obj->Run(action, this->get_to_render_static(), this->get_to_render_dynamic());
            }else{
                i--;
            }

        }else{
            obj->Run(action, this->get_to_render_static(), this->get_to_render_dynamic());
        }
    }
}

// camera alligned i need this
void Render_Type_World::camera_alligner(){
    this->camera.target = {(float)this->player->get_x(), (float)this->player->get_y()};
}