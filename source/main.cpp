// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025 

#include "dsinput_print.h"
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <fat.h>

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

    #pragma region Initialization
    PrintConsole topScreen;
    PrintConsole bottomScreen;

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    #pragma endregion

    consoleSelect(&topScreen);

    
    bool init_ok = fatInitDefault();
    if (!init_ok)
    {
        perror("fatInitDefault()");
        wait_forever();
    }

    printf("Testing input. Please press any key");
    printf("\n");
    printf("START will exit the program");
    printf("\n");


    consoleSelect(&bottomScreen);

    while (1)
    {
        PrintDSInput* getInput = new PrintDSInput();
        
        swiWaitForVBlank();
        
        scanKeys();
        
        if (keysHeld() & KEY_START) break;

        else if (keysHeld() & static_cast<KEYPAD_BITS>(keysHeld()))
        {
            getInput->printInput(static_cast<KEYPAD_BITS>(keysHeld()));
            printf(" was held!\n");
        }
        
    }

    return 0;
}
