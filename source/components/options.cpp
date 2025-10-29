#include "options.h"

void Options::InitializeConsole(PrintConsole *console, const unsigned int layer, BgType bg_type, BgSize bg_size, const unsigned int map_base, const unsigned int tile_base, const unsigned int pal_index, const unsigned int start_char, bool is_main, bool load_gr)
{
    consoleInitEx(console,
                  layer,      // Background layer
                  bg_type,    // 4 BPP mode
                  bg_size,    // Size of the background layer
                  map_base,   // Use map base 0 (they can't be shared)
                  tile_base,  // Use tile base 3
                  pal_index,  // Use palette index 4 (16 color palettes)
                  start_char, // Start from character 0 of the tile base
                  is_main,    // Sub screen
                  load_gr);
}

void Options::SetMainConsole(PrintConsole main_con)
{
    consoleInitEx(&main_con,
                  1,                // Background layer
                  BgType_Text8bpp,  // 8 BPP mode
                  BgSize_T_256x256, // Size of the background layer
                  0,                // Use map base 0 (they can't be shared)
                  3,                // Use tile base 3
                  0,                // Use palette index 0 (256 color palette)
                  0,                // Start from character 0 of the tile base
                  true,             // Main screen
                  false);           // Don't load graphics

    m_main_console = main_con;
}

void Options::AddSubConsole(PrintConsole sub_con)
{
    // consoleInitEx(sub_con,
    //               0,                // Background layer
    //               BgType_Text4bpp,  // 4 BPP mode
    //               BgSize_T_256x256, // Size of the background layer
    //               0,                // Use map base 0 (they can't be shared)
    //               3,                // Use tile base 3
    //               4,                // Use palette index 4 (16 color palettes)
    //               0,                // Start from character 0 of the tile base
    //               false,            // Sub screen
    //               false);           // Don't load graphics

    m_sub_consoles.push_back(sub_con);
}

void Options::DisplayOptions(PrintConsole main_con, std::vector<PrintConsole> sub_con)
{
    setBackdropColorSub(RGB15(5, 5, 5));

    InitializeConsole(&sub_con_01, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 3, 4, 0, false, false);

    consoleSetFont(&sub_con_01, &font_cellphone);


    int x = 1;
    int y = 1;
    int width = 10;
    int height = 5;

    consoleSetWindow(&sub_con_01, x, y, x + width, y + height);

    consoleSelect(&sub_con_01);

    printf("Printing on the bottom screen in a small window\n");

    touchPosition current_pos;

    u16 L_x = 8 * x;
    u16 R_x = 8 * (x + width);
    u16 L_y = 8 * y;
    u16 R_y = 8 * (y + height);

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

void Options::DisplayOptions(std::vector<Tileset *> layers, Options *options, int scroll_x, int scroll_y, std::vector<PrintConsole> sub_con)
{
    setBackdropColorSub(RGB15(5, 5, 5));

    InitializeConsole(&sub_con_01, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 3, 4, 0, false, false);

    consoleSetFont(&sub_con_01, &font_cellphone);

    int x = 1;
    int y = 1;
    int width = 10;
    int height = 5;

    consoleSetWindow(&sub_con_01, x, y, x + width, y + height);

    consoleSelect(&sub_con_01);

    printf("Printing on the bottom screen in a small window\n");

    touchPosition current_pos;

    u16 L_x = 8 * x;
    u16 R_x = 8 * (x + width);
    u16 L_y = 8 * y;
    u16 R_y = 8 * (y + height);

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        uint16_t keys = keysHeld();
        
        ScrollInput(keys, scroll_x, scroll_y);
        
        glBegin2D();
        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));

        if (keys & KEY_START)
            break;

        if (keys & KEY_TOUCH)
        {
            touchRead(&current_pos);
        }

        if (keys & KEY_TOUCH)
        {
            glBoxFilled(
                current_pos.px - TOUCH_BOX_RADIUS,
                current_pos.py - TOUCH_BOX_RADIUS,
                current_pos.px + TOUCH_BOX_RADIUS,
                current_pos.py + TOUCH_BOX_RADIUS,
                RGB15(31, 31, 31)
            );
        }
        
        // insert battle graphics
        for (Tileset *layer : m_drawing_layers)
        {
            switch (layer->m_tag)
            {
            case TS_TAG_BG:
                for (int j = 0; j < MAP_HEIGHT; j++)
                {
                    for (int i = 0; i < MAP_WIDTH; i++)
                    {
                        int x = scroll_x + i * 16;
                        int y = scroll_y + j * 16;
                        int tile_id = map[j * MAP_WIDTH + i];

                        glSprite(x, y, GL_FLIP_NONE, &layer->m_tileset_img[tile_id]);
                    }
                }
                break;
            case TS_TAG_CHAR:
                glSprite((screen_width / 2) - (layer->m_sprite_w / 2), (screen_height / 2) - (layer->m_sprite_h / 2), GL_FLIP_NONE, &layer->m_tileset_img[0]);
                break;
            }
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

void Options::ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y)
{
    if (keys & KEY_UP)
        scroll_y++;
    if (keys & KEY_DOWN)
        scroll_y--;

    if (keys & KEY_LEFT)
        scroll_x++;
    if (keys & KEY_RIGHT)   
        scroll_x--;
}