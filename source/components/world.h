#pragma once

//C++ includes
#include <string>
#include <vector>

//Componebts Folder
#include "scene.h"

class World
{
    public:

    World() = default;
    ~World() = default;

    std::string m_name;
    std::vector<Scene*> m_main_scenes;
    std::vector<Scene*> m_battle_scenes;

    int m_current_scene_index = 0;

    void InitializeWorld();
};