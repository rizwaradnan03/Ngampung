#include <engine/render_type/world.h>
#include <singleton/mouse.h>
#include <body/body.h>
#include <iostream>

Render_Type_World* G_RENDER_TYPE_world = nullptr;

void Render_Type_World::R_main(){
    std::vector<Static*> tmp;
    int32_t h = 3;

    std::vector<int32_t> masks = {1, 2, 3};

    Static* blck = new Static();
    blck->Init(60, 240, 30, 30, h, true, true, 1, &masks, "BLOCK_dirt");

    tmp.push_back(blck);

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

    this->to_render_static = tmp;
}

void Render_Type_World::Set(std::string type){
    if(type == "main"){
        R_main();
    }
    
    Dynamic* player = new Dynamic();
    std::vector<int32_t> masks = {1, 2, 3};
    player->Init(0, 0, 30, 30, 100, false, true, 1, &masks, "BLOCK_player");
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
    this->camera_alligner();
    
    std::cout << "NECESSITY : " << std::endl;
    // bool is_free = this->player->get_is_free();
    // if(is_free == true){
    //     delete player;
    //     player = nullptr;
    // }
    
    player->box_collide_checker(this->to_render_static, this->to_render_dynamic);
    player->Movement();

    BeginDrawing();
    ClearBackground(BLUE);
    BeginMode2D(this->camera);

    player->Run(nullptr, this->to_render_static, this->to_render_dynamic);
    this->Habit(nullptr);

    EndMode2D();
    EndDrawing();
}

void Render_Type_World::Habit(std::string* action){
    int32_t sz = this->to_render_static.size();
    int32_t dz = this->to_render_dynamic.size();

    for(int i = 0;i < sz + dz;i++){
        Body* obj;

        if(i < sz){
            obj = this->to_render_static[i];
        }else{
            obj = this->to_render_dynamic[i - sz];
        }

        bool is_free = obj->get_is_free();
        if(is_free == true){
            delete obj;
            if(i < sz){
                this->to_render_static.erase(this->to_render_static.begin() + i);
            }else{
              this->to_render_dynamic.erase(this->to_render_dynamic.begin() + (i - sz));
            }

            // i < sz ? this->to_render_static.erase(this->to_render_static.begin() + i) : this->to_render_dynamic.erase(this->to_render_dynamic.begin() + (i - sz));

            i--;
        }else{
            obj->Run(action, to_render_static, to_render_dynamic);
        }

    }
}

// camera alligned i need this
void Render_Type_World::camera_alligner(){
    this->camera.target = {(float)this->player->get_x(), (float)this->player->get_y()};
}