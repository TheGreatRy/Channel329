#include "text_console.h"

void TextConsole::InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size,
                                        PrintConsole *text_con, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int map_base, 
                                        const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr)
{
    
    // set console type
    m_text_console_type = con_type;
    m_is_main_console = is_main;

    // initialize console with given parameters
    consoleInitEx(text_con,
                  layer,      // Background layer
                  bg_type,    // Background type (preferrably text)
                  bg_size,    // Size of the background layer (preferrably text)
                  map_base,   // Use map_base
                  tile_base,  // Use tile_base
                  pal_index,  // Use palette size at pal_index
                  start_char, // Starting character from the tile base
                  is_main,    // True or false for if the console is on the main screen
                  load_gr);   // True or false to load graphics (true for base, false for custom)

    m_print_console = *text_con;
}

void TextConsole::InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size,
                                        PrintConsole* text_con, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int tile_base, 
                                        const unsigned int map_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr, 
                                        ConsoleFont* font, const unsigned int x_pos, const unsigned int y_pos, const unsigned int width, const unsigned int height)
{
    // Use the base initializer
    InitializeTextConsole(con_type, main_cons_size, sub_cons_size, text_con, layer, bg_type, bg_size, map_base, tile_base, pal_index, start_char, is_main, load_gr);

    // Set custom graphics
    consoleSetFont(&m_print_console, font);

    // Set custom window size
    // The screen size for the DS is 256:192
    // However, the consoleSetWindow functions sets window sizes in increments of 8
    // So largest values are 32 and 24 respectfully. Past this, the console will be off screen

    // In other words, x_pos + width > 32 or y_pos + height > 24 is consodered off screen
    // This is also true of just x_pos and y_pos
    // I am restricting this for my own sanity

    int x_corner = 0;
    int y_corner = 0;
    m_console_width = x_pos + width;
    m_console_height = y_pos + height;

    // setting the console position to x = 0 and/or y = 0 if they go past the limit
    x_corner = (x_pos > 32) ? 0 : x_pos;
    y_corner = (y_pos > 24) ? 0 : y_pos;

    // setting the window size to width = 1 (if 0) or 32 (if past limit) and/or height = 1 (if 0) or 24 (if past limit)
    m_console_width = (m_console_width < 1) ? 1 : (m_console_width > 32) ? 32 : m_console_width;
    
    m_console_height = (m_console_height < 1) ? 1 : (m_console_height > 24) ? 24 : m_console_height;

    consoleSetWindow(&m_print_console, x_corner, y_corner, m_console_width, m_console_height);

    // Detecting touch to the console will use the processed pixel value (0-256 x && 0-192 y)
    // Due to the consoleSetWindow, we need to scale up the values by 8

    // these are all processed pixel values of the console positions
    // the leftmost x position of the console
    left_x = 8 * x_corner;
    // the rightmost x position of the console
    right_x = 8 * m_console_width;
    // the topmost y position of the console
    top_y = 8 * y_corner;
    // the furthest down y position of the console
    bottom_y = 8 * m_console_height;
}

void TextConsole::SetText(std::string text, bool detect_touch)
{
    if (detect_touch)
        m_touch_text = text;
    else
        m_text = text;
}

//Display text without detecting user input
void TextConsole::DisplayTextConsole(PrintConsole *text_con)
{
    consoleSelect(text_con);
    printf("\x1b[2J");
    printf(m_text.c_str());
}

//Display text based on user input
void TextConsole::DisplayTextConsole(PrintConsole* text_con, touchPosition current_pos)
{
    consoleSelect(text_con);

    if (keysHeld() & KEY_TOUCH)
    {
        touchRead(&current_pos);
    }

    if (current_pos.px >= left_x && current_pos.px <= right_x && current_pos.py >= top_y && current_pos.py <= bottom_y)
    {
        printf("\x1b[2J");
        printf(m_touch_text.c_str());
    }
    else
    {
        printf("\x1b[2J");
        printf(m_text.c_str());
    }
}


//Display text based on the current battle
void TextConsole::DisplayTextConsole(PrintConsole *text_con, touchPosition current_pos, Battle *battle, int index)
{
    consoleSelect(text_con);

    if (keysHeld() & KEY_TOUCH)
    {
        touchRead(&current_pos);
    }

    if (current_pos.px >= left_x && current_pos.px <= right_x && current_pos.py >= top_y && current_pos.py <= bottom_y)
    {
        printf("\x1b[2J");
        //WriteWordsPerLine(win_text, 4);

        // for (std::string line : m_words_per_line)
        // {
        //     printf(line.c_str());
        // }
        //printf(result->m_text.c_str());
    }
    else
    {
        printf("\x1b[2J"); 
        // WriteWordsPerLine(battle->m_attack_phrases[index]->m_text, 4);
        // for (std::string line : m_words_per_line)
        // {
        //     printf(line.c_str());
        // }
        printf(battle->m_attack_phrases[index]->m_text.c_str());
    }
}

void TextConsole::ClearTextConsole(PrintConsole *text_con)
{
    consoleSelect(text_con);
    consoleClear();
}

void TextConsole::WriteWordsPerLine(std::string sentence, int bpp)
{
    //separate the words in a sentence by space
    std::stringstream str_stm(sentence);
    std::vector<std::string> words;
    std::string line;

    while (getline(str_stm, line, ' '))
    {
        words.push_back(line);
    }

    std::string current_line;

    for (int i = 0; i < words.size(); i++)
    {
        std::string compare = current_line + words[i] + ' ';

        if (compare.length() <= m_console_width * bpp) current_line = compare;
           
        m_words_per_line.push_back(current_line + "\n");
    }
}

