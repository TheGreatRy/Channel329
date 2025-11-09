#pragma once

// C++ Classes
#include <vector>
#include <map>

// NDS Libraries
#include <nds.h>
#include <stdio.h>

// Actors Folder
#include "../actors/character.h"

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
    Scene() = default;
    Scene(GM_STATE scene_gm_st);
    ~Scene() = default;

    std::vector<TextConsole *> m_main_consoles;
    std::vector<TextConsole *> m_sub_consoles;
    std::vector<Character *> m_actors;
    std::vector<Map *> m_maps;

    GM_STATE m_scene_gm_state;

    void AddActor(Character* character);
    void AddMap(Map* map);
    void AddTextConsole(TextConsole *text_con);

    void DrawScene(int scroll_x, int scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    void ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    void DeleteAllTextures();
    void DeleteAllSceneComponents();
    void ClearAllTextConsoles();

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;
};