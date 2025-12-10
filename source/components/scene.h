#pragma once

// C++ Classes
#include <vector>

// NDS Libraries
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>

// Actors Folder
#include "../actors/character.h"

// Components Folder
#include "background.h"

// Engine Folder
#include "../engine/game_states.h"
#include "../engine/text_console.h"
#include "../engine/text.h"
#include "../engine/battle.h"

class Scene
{
public:
    Scene() = default;
    Scene(GM_STATE scene_gm_st, int switch_id);
    ~Scene() = default;

    std::vector<TextConsole *> m_main_consoles;
    std::vector<TextConsole *> m_sub_consoles;
    std::vector<Text *> m_text_layers;
    std::vector<Sprite *> m_sprites;
    std::vector<Background*> m_backgrounds;
    std::vector<Character *> m_actors;
    std::vector<Battle*> m_battles;

    GM_STATE m_scene_gm_state;
    GM_STATE m_switch_gm_state;
    
    int m_switch_id = 0;
    int m_data_index = 0;
    bool m_player_quit = false;
    Character* m_player_object;

    void AddActor(Character* character);
    void AddSprite(Sprite* sprite);
    void AddTextConsole(TextConsole *text_con);
    void AddTextLayer(Text *text);
    void AddBackground(Background* background);
    void AddBattle(Battle* battle);

    void DrawScene(int& scroll_x, int& scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    
    void DetectInput(int &scroll_x, int &scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right);
    void SwitchAnimations(int& anim_id, bool& flip);
    
    void DeleteAllSceneComponents();
    void ClearAllTextConsoles();

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;
};