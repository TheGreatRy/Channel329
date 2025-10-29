// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025

#include "engine/game.h"
//#include "test_files/blockds_examples.h"

#include "../graphics/characters/cam.h"
#include "../graphics/test_graphics/tiny_16.h"
#include "../graphics/characters/talkingnpc.h"

#include <nds/arm9/dldi.h>

int main(int argc, char **argv)
{
    // Set the DLDI mode
    //dldiSetMode(DLDI_MODE_ARM9); // or DLDI_MODE_AUTODETECT or DLDI_MODE_ARM7

    Game* game = new Game();

    game->InitializeGame();

    Scene* demo = new Scene();

    Tileset* cam = new Tileset(1, 1, 32, 32, TS_TAG_CHAR);
    Tileset* town = new Tileset(10, 10, 16, 16, TS_TAG_BG);

    cam->LoadTileset({new glImage[cam->m_img_dimensions]},camPal, camBitmap, GL_RGB256, 256);
    town->LoadTileset({new glImage[town->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);

    //FIFO
    demo->AddLayer(town);
    demo->AddLayer(cam);


    Scene* battle = new Scene();
    Options* options = new Options();

    Tileset* enemy = new Tileset(1,1,64,64,TS_TAG_CHAR);

    enemy->LoadTileset({new glImage[enemy->m_img_dimensions]}, talkingnpcPal, talkingnpcBitmap, GL_RGB256, 256);

    battle->AddLayer(enemy);

    // while (1)
    // {
    //     swiWaitForVBlank();

    //     scanKeys();

    //     if (keysHeld() & KEY_START) break;

    // }
    
    game->RunCurrentScene(demo, options);
    //game->RunCurrentScene(demo);
    
    // Test methods to run
    // BlockDSExamples *DSeX = new BlockDSExamples();

    // DSeX->CustomFonts();

    return 0;
}
