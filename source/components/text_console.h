#pragma once

#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

#include <memory>
#include <vector>
#include <string>

// Graphics Folder
#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

#define TOUCH_BOX_RADIUS 4

enum TEXT_CON_TYPE
{
    TEXT_CON_TYPE_MAIN_OPT,
    TEXT_CON_TYPE_SUB_OPT,
    TEXT_CON_TYPE_MAIN_TALK,
    TEXT_CON_TYPE_SUB_TALK
};

class TextConsole
{
public:

    TextConsole() = default;

    PrintConsole m_print_console;
    TEXT_CON_TYPE m_text_console_type;
    u16 left_x;
    u16 right_x;
    u16 top_y;
    u16 bottom_y;

    //base text console
    void InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size, PrintConsole* console, 
        const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, 
        bool is_main, bool load_gr);

    //text console with custom fonts and window sizes
    void InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size, PrintConsole* console, 
        const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, 
        bool is_main, bool load_gr, ConsoleFont* font, const unsigned int x_pos, const unsigned int y_pos, const unsigned int width, const unsigned int height);
    
    //display text console to screen
    void DisplayTextConsole(PrintConsole* text_con, touchPosition current_pos);
    void ClearTextConsole(PrintConsole* text_con);

    // void GetWordsFromString(std::vector<std::string> sentence);
    // void UpdateOptionText();

    
};