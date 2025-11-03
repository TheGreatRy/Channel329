// C++ Classes
#include <vector>
#include <map>

// NDS Libraries
#include <nds.h>
#include <stdio.h>

// Components Folder
#include "text_console.h"
#include "map.h"

// Graphics Folder
#include "../graphics/test_graphics/tiny_16.h"

// Engine Folder
#include "../engine/game_states.h"

class Scene
{
public:
    std::vector<Tileset *> m_drawing_layers;
    std::vector<TextConsole *> m_main_consoles;
    std::vector<TextConsole *> m_sub_consoles;
    std::map<int, int> m_row_col;

    bool can_move_left = true;
    bool can_move_right = true;
    bool can_move_up = true;
    bool can_move_down = true;

    void AddLayer(Tileset *layer);
    void AddTextConsole(TextConsole *text_con);
    void DrawLayers(std::vector<Tileset *> layers, int scroll_x, int scroll_y);

    void ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y);

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;
};