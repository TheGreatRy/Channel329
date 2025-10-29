#include "game.h"

void Game::InitializeGame()
{
    // Set up exception handler
    defaultExceptionHandler();

    // Initialize GL in 2D and 3D mode
    glScreen2D();

    // Set video mode to 3D
    videoSetMode(MODE_0_3D);

    // // Setup some VRAM as memory for main engine background, main engine
    // // sprites, and 3D textures.
    // vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
    //      VRAM_C_TEXTURE, VRAM_D_TEXTURE);

    // Setup some memory to be used for textures and for texture palettes
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);

    //console setup in sub engine
    videoSetModeSub(MODE_0_3D);
    vramSetBankC(VRAM_C_SUB_BG);
}

void Game::RunCurrentScene(Scene *scene)
{
    // tileset variables
    int scroll_x = 0;
    int scroll_y = 0;

    scene->DrawLayers(scene->m_drawing_layers, scroll_x, scroll_y);
    
    // delete textures post game
    for (Tileset *layer : scene->m_drawing_layers)
    {
        glDeleteTextures(1, &layer->m_texture_id);
    }
}

void Game::RunCurrentScene(Scene *scene, Options *options)
{
    // tileset variables
    int scroll_x = 0;
    int scroll_y = 0;

    scene->DrawLayers(scene->m_drawing_layers, options, scroll_x, scroll_y);
    
    // delete textures post game
    for (Tileset *layer : scene->m_drawing_layers)
    {
        glDeleteTextures(1, &layer->m_texture_id);
    }
}
