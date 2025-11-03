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
    // if (can_move_up && keys & KEY_UP)
    //     scroll_y++;

    // if (can_move_down && keys & KEY_DOWN)
    //     scroll_y--;

    // if (can_move_left && keys & KEY_LEFT)
    //     scroll_x++;

    // if (can_move_right && keys & KEY_RIGHT)   
    //     scroll_x--;
    
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

    touchPosition current_pos;

    Map* bg_map = new Map(layers[0], 30, 20, map);
    Map* col_map = new Map(layers[1], 30, 20, collisions_interaction);

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

        
        m_sub_consoles[0]->DisplayTextConsole(&m_sub_consoles[0]->m_print_console, current_pos);

        for (Tileset *layer : m_drawing_layers)
        {
            switch (layer->m_tag)
            {
            case TS_TAG_BG:
                

                bg_map->DrawMap(scroll_x, scroll_y);

                break;
            case TS_TAG_COL:
                

                col_map->DrawMap(scroll_x, scroll_y);
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