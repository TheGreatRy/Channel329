#include <vector>
#include <nds.h>
#include <stdio.h>

//Components Folder
#include "text_console.h"

//Graphics Folder
#include "../graphics/test_graphics/tiny_16.h"

//Engine Folder
#include "../engine/game_states.h"


class Scene
{
public:
    std::vector<Tileset *> m_drawing_layers;
    std::vector<TextConsole* > m_main_consoles;
    std::vector<TextConsole* > m_sub_consoles;

    void AddLayer(Tileset *layer);
    void AddTextConsole(TextConsole* text_con);
    void DrawLayers(std::vector<Tileset *> layers, int scroll_x, int scroll_y);
    void DrawLayers(std::vector<Tileset *> layers, std::vector<TextConsole*> text_cons, int scroll_x, int scroll_y);

    void ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y);
};