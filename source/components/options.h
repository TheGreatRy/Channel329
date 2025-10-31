#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

#include <memory>
#include <vector>
#include <string>

// Components Folder
#include "tileset.h"

// Graphics Folder
#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

#define TOUCH_BOX_RADIUS 4
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

class Options
{
public:
    Options() = default;
    PrintConsole m_main_console;
    PrintConsole sub_con_01;
    PrintConsole sub_con_02;

    std::vector<PrintConsole> m_sub_consoles;

    std::vector<Tileset *> m_drawing_layers;

    void InitializeConsole(PrintConsole *console, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int map_base, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr);
    
    void SetMainConsole(PrintConsole main_con);
    void AddSubConsole(PrintConsole sub_con);
    void DisplayOptions(PrintConsole main_con, std::vector<PrintConsole> sub_con);
    void DisplayOptions(std::vector<Tileset *> layers, Options *options, int scroll_x, int scroll_y, std::vector<PrintConsole> sub_con);
    // void GetWordsFromString(std::vector<std::string> sentence);
    // void UpdateOptionText();

    void ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y);

    const int16_t map[MAP_WIDTH * MAP_HEIGHT] = {
        94, 95, 84, 85, 94, 95, 84, 85, 94, 95, 1, 1, 1, 1, 1, 1, 1, 1, 94, 95, 84, 85, 84, 85, 94, 95, 84, 85, 84, 85,
        84, 85, 94, 95, 84, 85, 94, 95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 94, 95, 94, 95, 84, 85, 94, 95, 94, 95,
        94, 95, 84, 85, 94, 95, 1, 0, 1, 1, 1, 1, 1, 1, 7, 7, 7, 1, 0, 1, 1, 1, 1, 1, 94, 95, 84, 85, 84, 85,
        1, 1, 94, 95, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 7, 7, 94, 95, 94, 95,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 84, 85,
        1, 1, 7, 0, 1, 1, 1, 1, 1, 1, 7, 2, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 94, 95,
        1, 7, 7, 7, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 47, 48, 48, 48, 49, 1, 1, 1, 1, 1, 1, 1, 1, 1, 84,
        0, 17, 18, 18, 18, 18, 18, 18, 19, 1, 1, 1, 1, 1, 1, 57, 58, 58, 58, 59, 1, 1, 1, 1, 0, 1, 1, 1, 1, 94,
        0, 27, 1, 1, 1, 1, 1, 1, 29, 1, 1, 1, 1, 1, 7, 67, 68, 68, 68, 69, 1, 1, 7, 7, 2, 1, 7, 1, 84, 85,
        7, 27, 1, 1, 1, 1, 1, 1, 29, 1, 1, 1, 1, 1, 1, 87, 97, 98, 99, 89, 1, 1, 0, 7, 7, 0, 0, 1, 94, 95,
        7, 27, 1, 1, 1, 1, 1, 1, 29, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 84, 85, 84,
        0, 27, 1, 1, 1, 1, 1, 1, 29, 7, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 94, 95, 94,
        7, 27, 1, 1, 1, 1, 1, 1, 29, 2, 7, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 84, 85,
        1, 37, 38, 38, 38, 38, 28, 38, 39, 7, 7, 1, 1, 1, 1, 20, 21, 21, 21, 21, 21, 21, 21, 22, 1, 1, 1, 1, 94, 95,
        7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 1, 1, 1, 30, 31, 31, 31, 31, 31, 31, 31, 32, 1, 1, 1, 1, 84, 85,
        0, 7, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 43, 22, 1, 2, 1, 94, 95,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 1, 7, 1, 1, 84,
        1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 1, 1, 1, 1, 94,
        1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 43, 22, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 1, 1, 1, 1};

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;

    // Size of a color in bytes
    const size_t size_color = 2;

    // Size of a font character in 4 and 8 BPP modes in bytes
    const size_t size_char_4bpp = (8 * 8) / 2;
    const size_t size_char_8bpp = 8 * 8;

    ConsoleFont font_anuvverbubbla = {
        .gfx = anuvverbubbla_8x8Tiles,
        .pal = anuvverbubbla_8x8Pal,
        .numColors = anuvverbubbla_8x8PalLen / size_color,
        .bpp = 8,
        .asciiOffset = 32,
        .numChars = anuvverbubbla_8x8TilesLen / size_char_8bpp,
    };

    ConsoleFont font_cellphone = {
        .gfx = charmap_cellphoneTiles,
        .pal = charmap_cellphonePal,
        .numColors = charmap_cellphonePalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_cellphoneTilesLen / size_char_4bpp,
    };

    ConsoleFont font_futuristic = {
        .gfx = charmap_futuristicTiles,
        .pal = charmap_futuristicPal,
        .numColors = charmap_futuristicPalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_futuristicTilesLen / size_char_4bpp,
    };
};