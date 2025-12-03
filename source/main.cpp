// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025

// NDS includes
#include <nds/arm9/dldi.h>

// Engine Folder
#include "engine/game.h"

//Game Data Folder 
#include "game_data/main_scene_data.h"
#include "game_data/battle_scene_data.h"

int main(int argc, char **argv)
{
    //create game object and initialize
    Game* game = new Game();

    game->InitializeGame();

    //Main Scene
    Scene* main_scene = new Scene(GM_STATE_MAIN, 0);
    GameData* main_data = new MainSceneData(main_scene);

    //Battle Scene
    Scene* battle_scene = new Scene(GM_STATE_BATTLE, 0);
    GameData* battle_data = new BattleSceneData(battle_scene);
    
    //Add scenes and data to the game

    game->AddData(main_data);
    game->AddScene(main_scene);

    game->AddData(battle_data);
    game->AddScene(battle_scene);
    
    //run game
    game->RunGame();
    
    delete game;
    
    return 0;
    
}
