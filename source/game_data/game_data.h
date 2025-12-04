#pragma once

//NDS includes
#include <nds.h>

//Components Folder
#include "../components/scene.h"

//Shared Graphics
#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

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
        .gfx = anuvverbubbla_8x8Tiles,
        .pal = anuvverbubbla_8x8Pal,
        .numColors = anuvverbubbla_8x8PalLen / size_color,
        .bpp = 8,
        .asciiOffset = 32,
        .numChars = anuvverbubbla_8x8TilesLen / size_char_8bpp,
    };

    ConsoleFont font_cellphone =
    {
        .gfx = charmap_cellphoneTiles,
        .pal = charmap_cellphonePal,
        .numColors = charmap_cellphonePalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_cellphoneTilesLen / size_char_4bpp,
    };

    ConsoleFont font_futuristic =
    {
        .gfx = charmap_futuristicTiles,
        .pal = charmap_futuristicPal,
        .numColors = charmap_futuristicPalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_futuristicTilesLen / size_char_4bpp,
    };

};