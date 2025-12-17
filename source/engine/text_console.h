#pragma once

#include <nds.h>
#include <stdio.h>

#include <memory>
#include <vector>
#include <string>
#include <sstream>

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
    ~TextConsole() = default;

    PrintConsole m_print_console;
    TEXT_CON_TYPE m_text_console_type;
    std::vector<std::string> m_words_per_line;

    int m_console_width = 16;
    int m_console_height = 12;

    bool m_is_main_console = false;

    std::string m_text;
    std::string m_touch_text;

    u16 left_x;
    u16 right_x;
    u16 top_y;
    u16 bottom_y;

    //base text console
    void InitializeTextConsole(TEXT_CON_TYPE con_type, PrintConsole* console, const unsigned int layer, BgType bg_type, BgSize bg_size, 
        const unsigned int map_base, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr);

    //text console with custom fonts and window sizes
    void InitializeTextConsole(TEXT_CON_TYPE con_type, PrintConsole* console, const unsigned int layer, BgType bg_type, BgSize bg_size, 
        const unsigned int map_base, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr, 
        ConsoleFont* font, const unsigned int x_pos, const unsigned int y_pos, const unsigned int width, const unsigned int height);
    
    void SetText(std::string text, bool detect_touch);

    //display text console to screen
    void DisplayTextConsole(PrintConsole* text_con);
    void DisplayTextConsole(PrintConsole* text_con, touchPosition current_pos);
    void ClearTextConsole(PrintConsole* text_con);

    void WriteWordsPerLine(std::string sentence, int bpp);
};