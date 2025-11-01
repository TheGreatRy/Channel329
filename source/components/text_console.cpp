#include "text_console.h"

void TextConsole::InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size,
    PrintConsole *text_con, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int tile_base, const unsigned int pal_index, 
    const unsigned int start_char, bool is_main, bool load_gr)
{
    //internally set map base to prevent bases from being shared
    //they are per screen (main and sub), so check for both
    int map_base = 0;

    //only initialize one console at a time using the is_main bool
    if (is_main) map_base = main_cons_size - 1;
    else if (!is_main) map_base = sub_cons_size - 1;
    m_text_console_type = con_type;

    //initialize console with given parameters
    consoleInitEx(text_con,
                  layer,      // Background layer
                  bg_type,    // Background type (preferrably text) 
                  bg_size,    // Size of the background layer (preferrably text)
                  map_base,   // Use map_base, set above to not be shared
                  tile_base,  // Use tile_base
                  pal_index,  // Use palette size at pal_index
                  start_char, // Starting character from the tile base
                  is_main,    // True or false for if the console is on the main screen
                  load_gr);   // True or false to load graphics (true for base, false for custom)
}

void TextConsole::InitializeTextConsole(TEXT_CON_TYPE con_type, const unsigned int main_cons_size, const unsigned int sub_cons_size,
    PrintConsole *text_con, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int tile_base, const unsigned int pal_index, 
    const unsigned int start_char, bool is_main, bool load_gr, ConsoleFont font, const unsigned int x_pos, const unsigned int y_pos, 
    const unsigned int width, const unsigned int height)
{
    //Use the base initializer
    InitializeTextConsole(con_type, main_cons_size, sub_cons_size, text_con, layer, bg_type, bg_size, tile_base, pal_index, start_char, is_main, load_gr);

    //Set custom graphics
    consoleSetFont(text_con, &font_cellphone);

    //Set custom window size
    //The screen size for the DS is 256:192
    //However, the consoleSetWindow functions sets window sizes in increments of 8
    //So largest values are 32 and 24 respectfully. Past this, the console will be off screen

    //In other words, x_pos + width > 32 or y_pos + height > 24 is consodered off screen
    //This is also true of just x_pos and y_pos
    //I am restricting this for my own sanity

    int x_corner;
    int y_corner;
    int screen_width = x_pos + width;
    int screen_height = y_pos + height;

    //setting the console position to x = 0 and/or y = 0 if they go past the limit
    x_corner = (x_corner > 32) ? 0 : x_pos; 
    y_corner = (y_corner > 24) ? 0 : y_pos;

    //setting the window size to width = 1 (if 0) or 32 (if past limit) and/or height = 1 (if 0) or 24 (if past limit)
    screen_width = (screen_width < 1) ? 1 : (screen_width > 32) ? 32 : screen_width;   
    screen_height = (screen_height < 1) ? 1 : (screen_height > 24) ? 24 : screen_height;

    consoleSetWindow(text_con, x_corner, y_corner, screen_width, screen_height);

    //Detecting touch to the console will use the processed pixel value (0-256 x && 0-192 y)
    //Due to the consoleSetWindow, we need to scale up the values by 8

    //these are all processed pixel values of the console positions
    //the leftmost x position of the console
    left_x = 8 * x_corner;
    //the rightmost x position of the console
    right_x = 8 * screen_width;
    //the topmost y position of the console
    top_y = 8 * y_corner;
    //the furthest down y position of the console
    bottom_y = 8 * screen_height;
}

void TextConsole::DisplayTextConsole(PrintConsole text_con)
{
    setBackdropColorSub(RGB15(5, 5, 5));

    consoleSelect(&text_con);

    printf("Printing on the bottom screen in a small window\n");

    touchPosition current_pos;

    

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        glBegin2D();
        glColor(RGB15(31, 31, 31));

        if (keysHeld() & KEY_START)
            break;

        if (keysHeld() & KEY_TOUCH)
        {
            touchRead(&current_pos);
        }

        if (keysHeld() & KEY_TOUCH)
        {
            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));

            glBoxFilled(
                current_pos.px - TOUCH_BOX_RADIUS,
                current_pos.py - TOUCH_BOX_RADIUS,
                current_pos.px + TOUCH_BOX_RADIUS,
                current_pos.py + TOUCH_BOX_RADIUS,
                RGB15(31, 31, 31)
            );
        }

        if (current_pos.px >= L_x && current_pos.px <= R_x && current_pos.py >= L_y && current_pos.py <= R_y)
        {
            printf("\x1b[2J");
            printf("Text box detected input!");
        }
        else
        {
            printf("\x1b[2J");
            printf("Not the box dummy!");
        }
        glEnd2D();
        glFlush(0);
    }
}
