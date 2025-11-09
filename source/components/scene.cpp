#include "scene.h"

Scene::Scene(GM_STATE scene_gm_st)
{
    m_scene_gm_state = scene_gm_st;
}

void Scene::AddActor(Character *character)
{
    m_actors.push_back(character);
}

void Scene::AddMap(Map *map)
{
    m_maps.push_back(map);
}

void Scene::AddTextConsole(TextConsole *text_con)
{
    //Add the console to the respective vector
    if (text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_TALK) 
        m_main_consoles.push_back(text_con);
    else if (text_con->m_text_console_type == TEXT_CON_TYPE_SUB_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_SUB_TALK) 
        m_sub_consoles.push_back(text_con);
}

void Scene::AddBattle(Battle *battle)
{
    m_battles.push_back(battle);
}

void Scene::ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right)
{
    if (can_move_up && keys & KEY_UP)
        scroll_y++;

    if (can_move_down && keys & KEY_DOWN)
        scroll_y--;

    if (can_move_left && keys & KEY_LEFT)
        scroll_x++;

    if (can_move_right && keys & KEY_RIGHT)   
        scroll_x--;
    
    // if (keys & KEY_UP)
    //     scroll_y++;

    // if (keys & KEY_DOWN)
    //     scroll_y--;

    // if (keys & KEY_LEFT)
    //     scroll_x++;

    // if (keys & KEY_RIGHT)   
    //     scroll_x--;
}

void Scene::DeleteAllTextures()
{
    //Maps
    for (Map* map : m_maps)
    {
        glDeleteTextures(1, &map->m_tileset_info.m_texture_id);
    }

    //Actors
    for (Character *actor : m_actors)
    {
        glDeleteTextures(1, &actor->m_tileset_info.m_texture_id);  
    }
}

void Scene::DeleteAllSceneComponents()
{
    // Maps
    for (Map *map : m_maps)
    {
        map->~Map();
        delete map;
    }

    // Actors
    for (Character *actor : m_actors)
    {
        actor->~Character();
        delete actor;
    }

    //TextConsoles
    for (TextConsole *console : m_main_consoles)
    {
        console->~TextConsole();
        delete console;
    }

    for (TextConsole *console : m_sub_consoles)
    {
        console->~TextConsole();
        delete console;
    }
    
    //Battles
    for (Battle *battle : m_battles)
    {
        battle->~Battle();
        delete battle;
    }
}

void Scene::ClearAllTextConsoles()
{
    for (TextConsole* console : m_main_consoles)
    {
        console->ClearTextConsole(&console->m_print_console);
    }
    
    for (TextConsole* console : m_sub_consoles)
    {
        console->ClearTextConsole(&console->m_print_console);
    }
}

void Scene::DrawScene(int scroll_x, int scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right)
{
    touchPosition current_pos;
    
    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        uint16_t keys = keysHeld();

        // if (keys & KEY_START) return GM_STATE_QUIT;

        ScrollInput(keys, scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

        // if (keys & KEY_A & KEY_B) return switch_gm_st;

        glBegin2D();
        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        if (keysDown() & KEY_START)
            break;

        //Main Screen Text Consoles
        for (TextConsole* main_con : m_main_consoles)
        {
            main_con->DisplayTextConsole(&main_con->m_print_console, current_pos);
        }
        
        //Sub Screen Text Consoles
        for (TextConsole* sub_con : m_sub_consoles)
        {
            sub_con->DisplayTextConsole(&sub_con->m_print_console, current_pos);
        }

        //Maps
        for (Map* map : m_maps)
        {
            map->DrawMap(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);
        }

        //Actors
        for (Character *actor : m_actors)
        {
            glSprite((screen_width / 2) - (actor->m_tileset_info.m_sprite_w / 2), (screen_height / 2) - (actor->m_tileset_info.m_sprite_h / 2), 
            GL_FLIP_NONE, &actor->m_tileset_info.m_tileset_img[0]);   
        }
       
        // end drawing 2D graphics
        glEnd2D();
        glFlush(0);
    }
}