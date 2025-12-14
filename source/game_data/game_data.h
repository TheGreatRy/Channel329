#pragma once

//NDS includes
#include <nds.h>

//Components Folder
#include "../components/scene.h"
#include "../components/sprite.h"

//Engine Folder
#include "../engine/text_console.h"
#include "../engine/text.h"

#include "fonts/blk_anuvverbubbla_8x8_png.h"


//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class GameData
{
    public:

    bool has_initialized = false;
    Scene* m_scene;

    virtual void InitializeData() = 0;

    void SetScene(Scene* scene)
    {
        m_scene = scene;
    }

    void LoadScene(Scene scene)
    {
        m_scene = &scene;
    }
    
    //Shared Variables
    // Size of a color in bytes
    const size_t size_color = 2;

    // Size of a font character in 4 and 8 BPP modes in bytes
    const size_t size_char_4bpp = (8 * 8) / 2;
    const size_t size_char_8bpp = 8 * 8;
 
    //Fonts
    ConsoleFont font_anuvverbubbla =
    {
        .gfx = blk_anuvverbubbla_8x8_pngTiles,
        .pal = blk_anuvverbubbla_8x8_pngPal,
        .numColors = blk_anuvverbubbla_8x8_pngPalLen / size_color,
        .bpp = 8,
        .asciiOffset = 32,
        .numChars = blk_anuvverbubbla_8x8_pngTilesLen / size_char_8bpp,
    };

    // ConsoleFont font_cellphone =
    // {
    //     .gfx = charmap_cellphoneTiles,
    //     .pal = charmap_cellphonePal,
    //     .numColors = charmap_cellphonePalLen / size_color,
    //     .bpp = 4,
    //     .asciiOffset = 32,
    //     .numChars = charmap_cellphoneTilesLen / size_char_4bpp,
    // };

    // ConsoleFont font_futuristic =
    // {
    //     .gfx = charmap_futuristicTiles,
    //     .pal = charmap_futuristicPal,
    //     .numColors = charmap_futuristicPalLen / size_color,
    //     .bpp = 4,
    //     .asciiOffset = 32,
    //     .numChars = charmap_futuristicTilesLen / size_char_4bpp,
    // };

};