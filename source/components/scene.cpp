#include "scene.h"

void Scene::AddLayer(Tileset *layer)
{
    m_drawing_layers.push_back(layer);
}

void Scene::AddTextConsole(TextConsole *text_con)
{
    //Add the console to the respective vector
    if (text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_TALK) 
        m_main_consoles.push_back(text_con);
    else if (text_con->m_text_console_type == TEXT_CON_TYPE_SUB_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_SUB_TALK) 
        m_sub_consoles.push_back(text_con);
}

void Scene::ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y)
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

void Scene::DrawLayers(std::vector<Tileset *> layers, int scroll_x, int scroll_y)
{
    setBackdropColorSub(RGB15(5, 5, 5));

    consoleSelect(&m_sub_consoles[0]->m_print_console);

    printf("Printing on the bottom screen in a small window\n");

    touchPosition current_pos;

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        uint16_t keys = keysHeld();

        // if (keys & KEY_START) return GM_STATE_QUIT;

        ScrollInput(keys, scroll_x, scroll_y);

        // if (keys & KEY_A & KEY_B) return switch_gm_st;

        glBegin2D();
        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        if (keysHeld() & KEY_START)
            break;

        
        m_sub_consoles[0]->DisplayTextConsole(m_sub_consoles[0]->m_print_console, current_pos);

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
       
        // end drawing 2D graphics
        glEnd2D();
        glFlush(0);
    }
}

void Scene::DrawLayers(std::vector<Tileset *> layers, std::vector<TextConsole*> text_cons, int scroll_x, int scroll_y)
{
    
    // for (Tileset* layer : m_drawing_layers)
    // {
    //     TextConsole->m_drawing_layers.push_back(layer);
    // }
    
    // TextConsole->DisplayTextConsole(TextConsole->m_drawing_layers, TextConsole, scroll_x, scroll_x,TextConsole->m_sub_consoles);
}
