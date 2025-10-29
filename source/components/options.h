#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

#include <memory>
#include <vector>
#include <string>

#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

#define TOUCH_BOX_RADIUS 4

class Options
{
public:
    Options() = default;
    PrintConsole m_main_console;
    PrintConsole sub_con_01;
    PrintConsole sub_con_02;

    std::vector<PrintConsole> m_sub_consoles;

    void InitializeConsole(PrintConsole *console, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int map_base, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr);
    void SetMainConsole(PrintConsole main_con);
    void AddSubConsole(PrintConsole sub_con);
    void DisplayOptions(PrintConsole main_con, std::vector<PrintConsole> sub_con);

    // void GetWordsFromString(std::vector<std::string> sentence);

    // void UpdateOptionText();


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