#include <raylib.h>
#include <vector>
#include <body/static.h>
#include <body/dynamic.h>
#include <engine/gui.h>

#pragma once

class Render_Type_Gui {
    public:
        void Set(const std::vector<Gui*>& set);
        void Run();
    
    private:
        std::vector<Gui*> guis;
};

extern Render_Type_Gui* G_RENDER_TYPE_gui;