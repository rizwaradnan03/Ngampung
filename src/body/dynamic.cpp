#include <body/dynamic.h>
#include <initial.h>
#include <namespace/system.h>
#include <iostream>
#include <namespace/audio.h>
#include <namespace/physic.h>
#include <namespace/system.h>

void Dynamic::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_anchor(anchor);
    this->set_is_can_collide(is_can_collide);
    this->set_health(health);
    this->set_layer(layer);
    this->set_jump_amount(1);
    
    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr){
        System::Log(false, "Gagal Load Texture!");
        return;
    }

    this->m_body = *tex;
}

int32_t Dynamic::get_layer(){
    return this->layer;
}

void Dynamic::set_layer(int32_t layer){
    this->layer = layer;
}

int32_t Dynamic::get_x(){
    return this->x;
}

void Dynamic::set_x(int32_t x){
    this->x = x;
}

int32_t Dynamic::get_y(){
    return this->y;
}

void Dynamic::set_y(int32_t y){
    this->y = y;
}

int32_t Dynamic::get_w(){
    return this->w;
}

void Dynamic::set_w(int32_t w){
    this->w = w;
}

int32_t Dynamic::get_h(){
    return this->h;
}

void Dynamic::set_h(int32_t h){
    this->h = h;
}

bool Dynamic::get_is_can_collide(){
    return this->is_can_collide;
}

void Dynamic::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}

bool Dynamic::get_anchor(){
    return this->anchor;
}

void Dynamic::set_anchor(bool anchor){
    this->anchor = anchor;
}

std::pair<bool, bool> Dynamic::get_available_direction(){
    return this->available_direction;
}

void Dynamic::set_available_direction(std::pair<bool, bool> available_direction){
    this->available_direction = available_direction;
}

std::vector<Render*> Dynamic::get_inventory(){
    return this->inventory;
}

void Dynamic::set_inventory(std::vector<Render*> inventory){
    this->inventory = inventory;
}

std::string Dynamic::get_movement_action(){
    return this->movement_action;
}

void Dynamic::set_movement_action(std::string movement_action){
    this->movement_action = movement_action;
}

std::string Dynamic::get_movement_direction(){
    return this->movement_direction;
}

void Dynamic::set_movement_direction(std::string movement_direction){
    this->movement_direction = movement_direction;
}

int32_t Dynamic::get_health(){
    return this->health;
}

void Dynamic::set_health(int32_t health){
    this->health = health;
}

int32_t Dynamic::get_jump_amount(){
    return this->jump_amount;
}

void Dynamic::set_jump_amount(int32_t jump_amount){
    this->jump_amount = jump_amount;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Dynamic::get_start_jump(){
    return this->start_jump;
}

void Dynamic::set_start_jump(std::chrono::time_point<std::chrono::high_resolution_clock> start_jump){
    this->start_jump = start_jump;
}

void Dynamic::Run(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->physics(static_objects, dynamic_objects);
    this->Display();
}

void Dynamic::physics(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    // this->box_collide_checker(static_objects, dynamic_objects);
}

void Dynamic::box_collide_checker(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_is_can_collide() == true && this->get_anchor() == false){
        S_Dynamic::Gravity d = {false, false, false, false};

        int32_t s_obj_z = static_objects.size();
        int32_t d_obj_z = dynamic_objects.size();
        for(int i = 0;i < s_obj_z + d_obj_z;i++){
            Render* obj;
            if(i < s_obj_z){
                obj = static_objects[i];
            }else{
                if(obj == this){
                    continue;
                }

                obj = dynamic_objects[i - s_obj_z];
            }

            if(obj->get_layer() == this->get_layer() && obj->get_is_can_collide() == true){
                std::pair<bool, std::string> cc = Physic::is_colliding(this, obj);
                if(cc.first == true){
                    if(cc.second == "BOTTOM"){
                        d.is_found_bottom = true;
                    }

                    if(cc.second == "TOP"){
                        d.is_found_top = true;
                    }

                    if(cc.second == "RIGHT"){
                        d.is_found_right = true;
                    }

                    if(cc.second == "LEFT"){
                        d.is_found_left = true;
                    }
                }
            }
        }

        if(d.is_found_bottom == false){
            this->set_y(this->get_y() + 3.0f);
        }else if(d.is_found_bottom == true){
            if(this->get_y() % 30 != 0){
                int calc = this->get_y();
                while(calc % 30 != 0){
                    calc--;
                }

                this->set_y(calc);
            }

            this->set_jump_amount(1);
        }

        this->set_available_direction(std::make_pair(d.is_found_left == true ? false : true, d.is_found_right == true ? false : true));
    }
}

void Dynamic::gravity(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_anchor() == false){
        this->y += 1.0f;
    }
}

void Dynamic::Display(){
    Rectangle source = {0.0f, 0.0f, (float)this->m_body.width, (float)this->m_body.height};
    Rectangle dest = {(float)this->get_x(), (float)this->get_y(), (float)this->get_w(), (float)this->get_h()};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->u_head, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_face, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_neck, source, dest, origin, 0.0f, WHITE);
    
    DrawTexturePro(this->m_body, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_l_hand, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_r_hand, source, dest, origin, 0.0f, WHITE);

    DrawTexturePro(this->l_foot, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->l_leg, source, dest, origin, 0.0f, WHITE);
}

void Dynamic::Movement(){
    std::pair<bool, bool> avail_x = this->get_available_direction();

    if(IsKeyDown(KEY_RIGHT) && avail_x.second == true){
        this->set_movement_direction("RIGHT");
        this->set_x(this->get_x() + 2.0f);
    }else if(IsKeyDown(KEY_LEFT) && avail_x.first == true){
        this->set_movement_direction("LEFT");
        this->set_x(this->get_x() - 2.0f);
    }

    if(IsKeyPressed(KEY_SPACE) && this->get_movement_action() != "JUMP" && this->get_jump_amount() > 0){
        this->set_start_jump(System::current_time());
        Audio::play("jump");
        this->set_movement_action("JUMP");
        this->set_y(this->get_y() - 7.0f);

        this->set_jump_amount(this->get_jump_amount() - 1);
    }

    if(this->get_movement_action() == "JUMP"){
        auto current_time = System::current_time();
        std::chrono::duration<float> differ = current_time - this->get_start_jump();
        
        if(differ.count() >= 0.3f){
            this->set_movement_action("STAY");
        }
    }
}