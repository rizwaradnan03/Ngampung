#include <body/dynamic.h>
#include <initial.h>
#include <engine/log.h>
#include <iostream>
#include <engine/audio.h>

void Dynamic::Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;
    this->is_can_collide = is_can_collide;
    this->health = health;

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr){
        Log(false, "Gagal Load Texture!");
        return;
    }

    this->m_body = *tex;
}

void Dynamic::Run(const std::vector<std::pair<int, std::vector<Static*>>>& static_objects, const std::vector<Dynamic*> dynamic_objects){
    this->Display();
    this->physics(static_objects, dynamic_objects);
}

void Dynamic::physics(const std::vector<std::pair<int, std::vector<Static*>>>& static_objects, const std::vector<Dynamic*> dynamic_objects){
    
}

// check the collide
void Dynamic::physic_collide(const std::vector<std::pair<int, std::vector<Static*>>>& static_objects, const std::vector<Dynamic*> dynamic_objects){
    for(int i = 0;i < this->collide_masks->size();i++){
        for(int j = 0;j < static_objects.size();j++){

            for(int k = 0;k < static_objects[j].second.size();k++){
                for(int p = 0;p < static_objects[j].second[k]->get_collide_masks()->size();p++){
                    if(this->collide_masks[i] == static_objects[j].second[k]->get_collide_masks()[p]){
                        // to check every colliding
                    }
                }
            }
        }
    }
}

void Dynamic::Display(){
    Rectangle source = {(float)this->x, (float)this->y, (float)this->m_body.width, (float)this->m_body.height};
    Rectangle dest = {(float)this->x, (float)this->y, 30.0f, 30.0f};
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
    if(IsKeyDown(KEY_RIGHT)){
        this->x += 1.0f;
    }else if(IsKeyDown(KEY_LEFT)){
        this->x -= 1.0f;
    }

    if(IsKeyPressed(KEY_SPACE)){
        Play("die");
        this->y -= 1.0f;
    }
}