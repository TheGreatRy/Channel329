#pragma once

//Game Data Folder
#include "game_data.h"



class MainSceneData : public GameData
{
    public:
    MainSceneData(Scene* scene)
    {
        m_scene = scene;
    }

    void InitializeData();

    //Scene Objects
    Character* cam;
    Background* options_bg;
    Background* overworld_bg;
    Background* overworld_col_bg;
    Text* test_text;
    
    //Sprite Objects
    Sprite* cam_front_idle;
    Sprite* cam_back_idle;
    Sprite* cam_side_idle;
    
    Sprite* cam_front_walk;
    Sprite* cam_back_walk;
    Sprite* cam_side_walk;

    //Animation Objects
    Animation* cam_idle_f;
    Animation* cam_idle_b;
    Animation* cam_idle_s;
    
    Animation* cam_walk_f;
    Animation* cam_walk_b;
    Animation* cam_walk_s;

};