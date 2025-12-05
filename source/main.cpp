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
    // //create game object and initialize
    // Game* game = new Game();

    // game->InitializeGame();

    //Initialize NitroFS
    // Prepare a NitroFS initialization screen
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    consoleDemoInit();
    printf("\n NitroFS init. Please wait.\n\n");
    printf(" Iniciando NitroFS,\n por favor, espere.\n\n");
    swiWaitForVBlank();

    // Initialize NitroFS and set it as the root folder of the filesystem
    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");

    // Initialize 2D engine in both screens and use mode 5. Layers 0 to 2 are
    // tiled backgrounds, layer 3 is an 8-bit bitmap background.
    NF_Set2D(0, 0);
    NF_Set2D(1, 5);

    // Initialize mixed background system
    NF_InitMixedBgSys(0);
    NF_InitMixedBgSys(1);

    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers();

    // Initialize storage buffers
    NF_Init8bitsBgBuffers();

    // Initialize sprite system
    NF_InitSpriteBuffers();     // Initialize storage buffers
    NF_InitSpriteSys(0);        // Top screen

    // Load background files from NitroFS
    NF_LoadTiledBg("bg/tiny_16", "tiny_16", 256, 256);

    NF_CreateTiledBg(0, 2, "tiny_16");
    
    // Load bitmap files from NitroFS
    NF_Load8bitsBg("bmp/overworld_options", 0);

    NF_Copy8bitsBuffer(1, 1, 0);
    
    // Load sprite files from NitroFS
    NF_LoadSpriteGfx("sprite/cam_front_idle_spritesheet", 0, 32, 32);
    NF_LoadSpritePal("sprite/cam_front_idle_spritesheet", 0);

    // Transfer the required sprites to VRAM
    NF_VramSpriteGfx(0, 0, 0, false);
    NF_VramSpritePal(0, 0, 0);

    NF_CreateSprite(0, 0, 0, 0, 100, 50);
    NF_SpriteLayer(0, 0, 0);

    //Game Loop
    while (1)
    {
        if (keysHeld() & KEY_START) break;

        // Update OAM array
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        // Wait for the screen refresh
        swiWaitForVBlank();

        // Update OAM
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    // //Main Scene
    // Scene* main_scene = new Scene(GM_STATE_MAIN, 0);
    // GameData* main_data = new MainSceneData(main_scene);
    // main_data->SetScene(main_scene);

    // //Battle Scene
    // Scene* battle_scene = new Scene(GM_STATE_BATTLE, 0);
    // GameData* battle_data = new BattleSceneData(battle_scene);
    // battle_data->SetScene(battle_scene);
    
    // //Add data to the game
    // game->AddData(main_data);
    // game->AddData(battle_data);
    
    // //run game
    // game->RunGame();
    
    // delete game;
    
    return 0;
    
}
