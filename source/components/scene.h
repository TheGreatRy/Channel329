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
#include "map.h"

// Graphics Folder
#include "../graphics/test_graphics/tiny_16.h"

// Engine Folder
#include "../engine/game_states.h"
#include "../engine/text_console.h"
#include "../engine/battle.h"

class Scene
{
public:
    Scene() = default;
    Scene(GM_STATE scene_gm_st, int switch_id);
    ~Scene() = default;

    std::vector<TextConsole *> m_main_consoles;
    std::vector<TextConsole *> m_sub_consoles;
    std::vector<Character *> m_actors;
    std::vector<Map *> m_maps;
    std::vector<Battle*> m_battles;

    GM_STATE m_scene_gm_state;
    GM_STATE m_switch_gm_state;
    
    int m_switch_id = 0;
    bool m_player_quit = false;
    Character* m_player_object;

    void AddActor(Character* character);
    void AddMap(Map* map);
    void AddTextConsole(TextConsole *text_con);
    void AddBattle(Battle* battle);

    void DrawScene(int scroll_x, int scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    
    void DetectInput(int &scroll_x, int &scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    void SwitchAnimations(int& anim_id, GL_FLIP_MODE& flip);
    
    void DeleteAllTextures();
    void DeleteAllSceneComponents();
    void ClearAllTextConsoles();

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;
};