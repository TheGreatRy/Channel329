// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025 

#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <fat.h>
#include <gl2d.h>

int main(int argc, char **argv)
{
    //Set up exception handler
    defaultExceptionHandler();

    glInit();
    videoSetMode(MODE_0_3D);

    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
                        VRAM_C_TEXTURE, VRAM_D_TEXTURE);


    return 0;
}
