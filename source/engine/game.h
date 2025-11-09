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

    std::vector<Scene*> m_scenes;

    //GM_STATE* m_current_game_state;

    void InitializeGame();

    void RunCurrentScene(Scene* scene);
    void RunCurrentScene(Scene* scene, TextConsole* TextConsole);

    void RunGame(std::vector<Scene*> scenes);
};