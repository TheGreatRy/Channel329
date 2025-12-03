#pragma once

//Game Data Folder
#include "game_data.h"

//Components Folder
#include "../components/tileset.h"

//Engine Folder
#include "../engine/text_console.h"

// Graphics Folder
//Battle Stills / Animations
#include "../graphics/characters/cameron/cam_battle.h"

//Test / Other Graphics
#include "../graphics/characters/talkingnpc.h"
#include "../graphics/backgrounds/battle_bottom.h"
#include "../graphics/backgrounds/battle_top.h"

class BattleSceneData : public GameData
{
    public:
    BattleSceneData(Scene* scene)
    {
        m_scene = scene;
    }

    void InitializeData();

};