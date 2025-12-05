#include "game.h"

void Game::InitializeGame()
{
    
}

void Game::InitializeScene(Scene *scene)
{
    int data_index = scene->m_data_index;

    if (!m_data[data_index]->has_initialized)
    {
        m_data[data_index]->InitializeData();
        m_data[data_index]->has_initialized = true;
    }
}

void Game::AddData(GameData *data)
{
    data->m_scene->m_data_index = m_data.size();
    
    switch (data->m_scene->m_scene_gm_state)
    {
        case GM_STATE_TITLE:
        m_title_scene = data->m_scene;
        break;
        case GM_STATE_MAIN:
        m_main_scenes.push_back(data->m_scene);
        break;
        case GM_STATE_BATTLE:
        m_battle_scenes.push_back(data->m_scene);
        break;
        case GM_STATE_MENU:
        m_menu_scene = data->m_scene;
        break;
    }
    m_data.push_back(data);
}


void Game::RunCurrentScene(Scene *scene)
{
    int data_index = scene->m_data_index;

    int scroll_x = 0;
    int scroll_y = 0;

    bool can_move_up = true;
    bool can_move_down = true;
    bool can_move_left = true;
    bool can_move_right = true;   

    scene->DrawScene(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

    Scene save_state = *scene;

    m_data[data_index]->LoadScene(save_state);

    switch (m_data[data_index]->m_scene->m_scene_gm_state)
    {
        case GM_STATE_TITLE:
        m_title_scene = m_data[data_index]->m_scene;
        break;
        case GM_STATE_MAIN:
        m_main_scenes.at(m_current_scene_index) = m_data[data_index]->m_scene;
        break;
        case GM_STATE_BATTLE:
        m_battle_scenes.at(m_current_scene_index) = m_data[data_index]->m_scene;
        break;
        case GM_STATE_MENU:
        m_menu_scene = m_data[data_index]->m_scene;
        break;
    }

    scene->ClearAllTextConsoles();
    // scene->DeleteAllTextures();
    // scene->DeleteAllSceneComponents();
    
}

void Game::RunGame()
{
    while (is_running)
    {
        switch (m_current_game_state)
        {
        case GM_STATE_TITLE:
            InitializeScene(m_title_scene);
            RunCurrentScene(m_title_scene);
            (m_title_scene->m_player_quit) ? is_running = false 
            : m_current_game_state = m_title_scene->m_switch_gm_state; 
            m_current_scene_index = m_title_scene->m_switch_id;
            break;
        case GM_STATE_MAIN:
            InitializeScene(m_main_scenes[m_current_scene_index]);
            RunCurrentScene(m_main_scenes[m_current_scene_index]);
            (m_main_scenes[m_current_scene_index]->m_player_quit) 
            ? is_running = false 
            : m_current_game_state = m_main_scenes[m_current_scene_index]->m_switch_gm_state; 
            m_current_scene_index = m_main_scenes[m_current_scene_index]->m_switch_id;

            break;
        case GM_STATE_BATTLE:
            InitializeScene(m_battle_scenes[m_current_scene_index]);
            RunCurrentScene(m_battle_scenes[m_current_scene_index]);
            (m_battle_scenes[m_current_scene_index]->m_player_quit) 
            ? is_running = false 
            : m_current_game_state = m_battle_scenes[m_current_scene_index]->m_switch_gm_state; 
            m_current_scene_index = m_battle_scenes[m_current_scene_index]->m_switch_id;

            break;
        case GM_STATE_MENU:
            InitializeScene(m_menu_scene);
            RunCurrentScene(m_menu_scene);
            break;
        default:
            is_running = false;
        }
    }
}
