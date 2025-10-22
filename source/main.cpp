// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025
#include <memory>
#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <fat.h>
#include <gl2d.h>

#include "../graphics/characters/cam.h"

#include "test_files/blockds_examples.h"

int main(int argc, char **argv)
{
    consoleDemoInit();

    // Set up exception handler
    defaultExceptionHandler();
    
    // Initialize GL in 2D and 3D mode
    glScreen2D();
    
    // Set video mode to 3D
    videoSetMode(MODE_0_3D);
    
    // // Setup some VRAM as memory for main engine background, main engine
    // // sprites, and 3D textures.
    // vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
    //     VRAM_C_TEXTURE, VRAM_D_TEXTURE);
    // Setup some memory to be used for textures and for texture palettes
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);
        
    Tileset* cam = new Tileset(1, 1, 32, 32);
    
    cam->LoadTileset({new glImage[cam->m_sprites_num_x]},camPal, camBitmap);

    BlockDSExamples* DSeX = new BlockDSExamples();

    DSeX->TilesetBG(*cam);
        
    return 0;
}
