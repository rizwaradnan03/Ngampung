#include <engine/render_type/world.h>
#include <singleton/mouse.h>
#include <body/body.h>

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
    this->camera_alligner();

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

    player->Run(nullptr, this->to_render_static, this->to_render_dynamic);

    this->Habit(nullptr);
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