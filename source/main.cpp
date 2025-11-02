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
    PrintConsole* sub_con_01 = new PrintConsole();
    TextConsole* text_console = new TextConsole();

    Tileset* cam = new Tileset(1, 1, 32, 32, TS_TAG_CHAR);
    Tileset* town = new Tileset(10, 10, 16, 16, TS_TAG_BG);

    cam->LoadTileset({new glImage[cam->m_img_dimensions]},camPal, camBitmap, GL_RGB256, 256);
    town->LoadTileset({new glImage[town->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);

    //this is a crime im so sorry
    text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, demo->m_main_consoles.size(), demo->m_sub_consoles.size(), sub_con_01, 0, BgType_Text4bpp,
    BgSize_T_256x256, 3, 4, 0, false, false, text_console->font_cellphone, 1, 1, 5, 10);
    
    //FIFO
    demo->AddLayer(town);
    demo->AddLayer(cam);
    demo->AddTextConsole(text_console);
    
    //initialize after to get current vector sizes


    // Multiple scenes doesnt work yet
    // Scene* battle = new Scene();

    // Tileset* enemy = new Tileset(1,1,64,64,TS_TAG_CHAR);

    // enemy->LoadTileset({new glImage[enemy->m_img_dimensions]}, talkingnpcPal, talkingnpcBitmap, GL_RGB256, 256);

    // battle->AddLayer(enemy);
    
    //game->RunCurrentScene(demo, text_console);
    game->RunCurrentScene(demo);
    
    // Test methods to run
    // BlockDSExamples *DSeX = new BlockDSExamples();

    // DSeX->CustomFonts();

    return 0;
}
