// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025

#include "engine/game.h"
//#include "test_files/blockds_examples.h"

#include "../graphics/characters/cam.h"
#include "../graphics/test_graphics/tiny_16.h"

#include <nds/arm9/dldi.h>

int main(int argc, char **argv)
{
    // Set the DLDI mode
    //dldiSetMode(DLDI_MODE_ARM9); // or DLDI_MODE_AUTODETECT or DLDI_MODE_ARM7

    Game* game = new Game();

    game->InitializeGame();

    Scene* demo = new Scene();

    Tileset* cam = new Tileset(1, 1, 32, 32, TS_CHARACTER);
    Tileset* town = new Tileset(10, 10, 16, 16, TS_BACKGROUND);

    cam->LoadTileset({new glImage[cam->m_img_dimensions]},camPal, camBitmap, GL_RGB256, 256);
    town->LoadTileset({new glImage[town->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);

    //FIFO
    demo->AddLayer(town);
    demo->AddLayer(cam);

    Options* options = new Options();

    //options->SetMainConsole(main_console);
    //options->DisplayOptions(main_console, sub_consoles);

    game->RunCurrentScene(demo, options);

    
    // Test methods to run
    // BlockDSExamples *DSeX = new BlockDSExamples();

    // DSeX->CustomFonts();

    return 0;
}
