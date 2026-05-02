#include <engine/render_type/gui.h>

Render_Type_Gui* G_RENDER_TYPE_gui = nullptr;

void Render_Type_Gui::Set(const std::vector<Gui*>& set){
    this->guis = set;
}

void Render_Type_Gui::Run(){
    // to run
}