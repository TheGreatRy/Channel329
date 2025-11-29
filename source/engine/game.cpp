#include "game.h"

void Game::InitializeGame()
{
    // Set up exception handler
    defaultExceptionHandler();

    // Initialize GL in 2D and 3D mode
    glScreen2D();

    // Set video mode to 3D
    videoSetMode(MODE_0_3D);
    videoSetModeSub(MODE_5_2D);

    // // Setup some VRAM as memory for main engine background, main engine
    // // sprites, and 3D textures.
    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
         VRAM_C_TEXTURE, VRAM_D_TEXTURE);

    // Setup some memory to be used for textures and for texture palettes
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);
    vramSetBankC(VRAM_C_SUB_BG);
}

void Game::RunCurrentScene(Scene *scene)
{
    int scroll_x = 0;
    int scroll_y = 0;

    bool can_move_up = true;
    bool can_move_down = true;
    bool can_move_left = true;
    bool can_move_right = true;

    scene->DrawScene(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

    Scene* save_state = scene;
    switch (scene->m_scene_gm_state)
    {
        case GM_STATE_TITLE:
        m_title_scene = save_state;
        break;
        case GM_STATE_MAIN:
        m_main_scenes.at(m_current_scene_index) = save_state;
        break;
        case GM_STATE_BATTLE:
        m_battle_scenes.at(m_current_scene_index) = save_state;
        break;
        case GM_STATE_MENU:
        m_menu_scene = save_state;
        break;
    }
    
    scene->ClearAllTextConsoles();
    scene->DeleteAllTextures();
    scene->DeleteAllSceneComponents();
}

void Game::AddScene(Scene *scene)
{
    switch (scene->m_scene_gm_state)
    {
        case GM_STATE_TITLE:
        m_title_scene = scene;
        break;
        case GM_STATE_MAIN:
        m_main_scenes.push_back(scene);
        break;
        case GM_STATE_BATTLE:
        m_battle_scenes.push_back(scene);
        break;
        case GM_STATE_MENU:
        m_menu_scene = scene;
        break;
    }
}

void Game::RunGame()
{
    while (is_running)
    {
        switch (m_current_game_state)
        {
        case GM_STATE_TITLE:
            RunCurrentScene(m_title_scene);
            (m_title_scene->m_player_quit) ? is_running = false 
            : m_current_game_state = m_title_scene->m_switch_gm_state; 
            m_current_scene_index = m_title_scene->m_switch_id;
            break;
        case GM_STATE_MAIN:
            RunCurrentScene(m_main_scenes[m_current_scene_index]);
            (m_main_scenes[m_current_scene_index]->m_player_quit) 
            ? is_running = false 
            : m_current_game_state = m_main_scenes[m_current_scene_index]->m_switch_gm_state; 
            m_current_scene_index = m_main_scenes[m_current_scene_index]->m_switch_id;

            break;
        case GM_STATE_BATTLE:
            RunCurrentScene(m_battle_scenes[m_current_scene_index]);
            (m_battle_scenes[m_current_scene_index]->m_player_quit) 
            ? is_running = false 
            : m_current_game_state = m_battle_scenes[m_current_scene_index]->m_switch_gm_state; 
            m_current_scene_index = m_battle_scenes[m_current_scene_index]->m_switch_id;

            break;
        case GM_STATE_MENU:
            RunCurrentScene(m_menu_scene);
            break;
        default:
            is_running = false;
        }
    }

    // //Clear all scenes from memory once done
    // for (Scene* scene : m_scenes)
    // {
    //     delete scene;
    // }
}
