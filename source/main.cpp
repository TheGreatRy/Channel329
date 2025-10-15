// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025 

#include "dsinput_print.h"
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <fat.h>

// This file contains pointers to the data: `forest_townTiles`, `forest_townMap`
// and `forest_townPal`. It also contains the size of everything:
// `forest_townTilesLen`, etc.
#include "forest_town.h"

void wait_forever(void)
{
    while (1)
        swiWaitForVBlank();
}

typedef void (fnptrvoid)(void);
typedef int (fnptr1int)(int);
typedef int (fnptr2int)(int, int);


int main(int argc, char **argv)
{
    //Set up exception handler
    defaultExceptionHandler();

    #pragma region Input Initialization
    // PrintConsole topScreen;
    // PrintConsole bottomScreen;

    // videoSetMode(MODE_0_2D);
    // videoSetModeSub(MODE_0_2D);

    // vramSetBankA(VRAM_A_MAIN_BG);
    // vramSetBankC(VRAM_C_SUB_BG);

    // consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    // consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    #pragma endregion

    #pragma region Input Tests
    // consoleSelect(&topScreen);

    
    // bool init_ok = fatInitDefault();
    // if (!init_ok)
    // {
    //     perror("fatInitDefault()");
    //     wait_forever();
    // }

    // printf("Testing input. Please press any key");
    // printf("\n");
    // printf("START will exit the program");
    // printf("\n");


    // consoleSelect(&bottomScreen);

    // while (1)
    // {
    //     PrintDSInput* getInput = new PrintDSInput();
        
    //     swiWaitForVBlank();
        
    //     scanKeys();
        
    //     if (keysHeld() & KEY_START) break;

    //     else if (keysHeld() & static_cast<KEYPAD_BITS>(keysHeld()))
    //     {
    //         getInput->printInput(static_cast<KEYPAD_BITS>(keysHeld()));
    //         printf(" was held!\n");
    //     }
        
    // }
    #pragma endregion

   // Use a video mode that sets layer 0 as a regular tiled background. Mode 0
    // sets all 4 layers as regular tiled backgrounds.
    videoSetMode(MODE_0_2D);

    // Designate VRAM A as memory for main engine backgrounds. This gives us 128
    // KB in total.
    vramSetBankA(VRAM_A_MAIN_BG);

    // Initialize layer 0 as a regular (text) background with 256 colors (8 bpp)
    // and size 256x256. The last 0 is the map base and the 1 is the tile base.
    // We'll talk about that in a minute.
    int bg = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

    // Copy tiles and tile map to VRAM
    dmaCopy(forest_townTiles, bgGetGfxPtr(bg), forest_townTilesLen);
    dmaCopy(forest_townMap, bgGetMapPtr(bg), forest_townMapLen);

    // Copy palete to palette RAM
    dmaCopy(forest_townPal, BG_PALETTE, forest_townPalLen);

    consoleDemoInit();

    printf("PAD:   Scroll background\n");
    printf("START: Exit to loader\n");

    int x = 0, y = 0;

    while (1)
    {
        swiWaitForVBlank();

        bgSetScroll(bg, x, y);

        bgUpdate();

        scanKeys();

        u16 keys_held = keysHeld();

        if (keys_held & KEY_UP)
            y--;
        else if (keys_held & KEY_DOWN)
            y++;

        if (keys_held & KEY_LEFT)
            x--;
        else if (keys_held & KEY_RIGHT)
            x++;

        if (keys_held & KEY_START)
            break;
    }

    
    return 0;
}
