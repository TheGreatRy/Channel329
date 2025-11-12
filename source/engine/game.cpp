#include "game.h"

void Game::InitializeGame()
{
    // Set up exception handler
    defaultExceptionHandler();

    // Initialize GL in 2D and 3D mode
    glScreen2D();

    // Set video mode to 3D
    videoSetMode(MODE_0_3D);
    videoSetModeSub(MODE_0_3D);

    // // Setup some VRAM as memory for main engine background, main engine
    // // sprites, and 3D textures.
    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
         VRAM_C_TEXTURE, VRAM_D_TEXTURE);

    // Setup some memory to be used for textures and for texture palettes
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);
    vramSetBankC(VRAM_C_SUB_BG);
}

void Game::RunCurrentScene(Scene *scene)
{
    int scroll_x = 0;
    int scroll_y = 0;

    bool can_move_up = true;
    bool can_move_down = true;
    bool can_move_left = true;
    bool can_move_right = true;

    scene->DrawScene(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

    scene->ClearAllTextConsoles();
    scene->DeleteAllTextures();
    scene->DeleteAllSceneComponents();
}

void Game::AddScene(Scene *scene)
{
    m_scenes.push_back(scene);
}

void Game::RunGame()
{
    for (Scene* scene : m_scenes)
    {
        RunCurrentScene(scene);
    }

    //Clear all scenes from memory once done
    for (Scene* scene : m_scenes)
    {
        delete scene;
    }
}
