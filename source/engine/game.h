#pragma once

//NDS Libraries
#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <gl2d.h>

//C++ includes
#include <vector>

// Components Folder
#include "../components/scene.h"

class Game
{
    public:
    Game() = default;
    ~Game() = default;

    bool is_running = true;

    GM_STATE m_current_game_state = GM_STATE_MAIN;

    Scene* m_title_scene;
    Scene* m_menu_scene;
    std::vector<Scene*> m_main_scenes;
    std::vector<Scene*> m_battle_scenes;

    int m_current_scene_index = 0;

    void InitializeGame();

    void AddScene(Scene* scene);
    void RunGame();
    
    private:
    void RunCurrentScene(Scene* scene);
};