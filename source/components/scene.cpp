#include "scene.h"

Scene::Scene(GM_STATE scene_gm_st, int switch_id)
{
    m_scene_gm_state = scene_gm_st;
    m_switch_id = switch_id;
}

void Scene::AddActor(Character *character)
{
    m_actors.push_back(character);

    if (character->m_character_type == CHARACTER_TYPE_MAIN)
    m_player_object = character;
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

void Scene::DetectInput(int &scroll_x, int &scroll_y, bool& can_move_up, bool& can_move_down, bool& can_move_left, bool& can_move_right)
{
    if (can_move_up && keysHeld() & KEY_UP)
        scroll_y--;

    if (can_move_down && keysHeld() & KEY_DOWN)
        scroll_y++;

    if (can_move_left && keysHeld() & KEY_LEFT)
        scroll_x--;

    if (can_move_right && keysHeld() & KEY_RIGHT)   
        scroll_x++;
}

void Scene::SwitchAnimations(int& anim_id, GL_FLIP_MODE& flip)
{
    //play animation on input
    //else if so multiple won't play at once on the same character
    
    //UP
    if (keysUp() & KEY_UP) 
    {
        anim_id = 1; 
        flip = GL_FLIP_NONE;
    }
    else if (keysHeld() & KEY_UP)
    {
        anim_id = 4;
        flip = GL_FLIP_NONE;
    }

    //DOWN
    else if (keysUp() & KEY_DOWN) 
    { 
        anim_id = 0; 
        flip = GL_FLIP_NONE;
    }
    else if (keysHeld() & KEY_DOWN)
    {
        anim_id = 3;
        flip = GL_FLIP_NONE;
    }

    //LEFT
    else if (keysUp() & KEY_LEFT) 
    {
        anim_id = 2;
        flip = GL_FLIP_H;
    }
    else if (keysHeld() & KEY_LEFT) 
    {
        anim_id = 5;
        flip = GL_FLIP_H;
    }

    //RIGHT
    else if (keysUp() & KEY_RIGHT) 
    {
        anim_id = 2;
        flip = GL_FLIP_NONE;
    }
    else if (keysHeld() & KEY_RIGHT) 
    {
        anim_id = 5;
        flip = GL_FLIP_NONE;
    }
    
    

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
        for (Animation* animation : actor->m_sprite_animations) glDeleteTextures(1, &animation->m_spritesheet.m_texture_id);  
    }
}

void Scene::DeleteAllSceneComponents()
{
    // Maps
    for (Map *map : m_maps)
    {
        //map->~Map();
        delete map;
    }

    // Actors
    for (Character *actor : m_actors)
    {
        //actor->~Character();
        delete actor;
    }

    //TextConsoles
    for (TextConsole *console : m_main_consoles)
    {
        //console->~TextConsole();
        delete console;
    }

    for (TextConsole *console : m_sub_consoles)
    {
        //console->~TextConsole();
        delete console;
    }
    
    //Battles
    for (Battle *battle : m_battles)
    {
        //battle->~Battle();
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

    int current_anim_id = 0;
    GL_FLIP_MODE current_flip = GL_FLIP_NONE;

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        DetectInput(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

        glBegin2D();
        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        //quit game
        if (keysDown() & KEY_START)
        {  
            m_player_quit = true;
            break;
        }

        //switch animations on input
        SwitchAnimations(current_anim_id, current_flip);
        
        //switch to game
        if ((m_scene_gm_state != GM_STATE_BATTLE) && keysUp() & KEY_A)
        {    
            m_switch_gm_state = GM_STATE_BATTLE;
            m_player_quit = false;
            break;
        }
        
        //switch to main
        if ((m_scene_gm_state != GM_STATE_MAIN) && keysUp() & KEY_B)
        {    
            m_switch_gm_state = GM_STATE_MAIN;
            m_player_quit = false;
            break;
        }

        //Main Screen Text Consoles
        for (TextConsole* main_con : m_main_consoles)
        {
            main_con->DisplayTextConsole(&main_con->m_print_console, current_pos);
        }
        
        int index = 0;
        //Sub Screen Text Consoles
        for (TextConsole* sub_con : m_sub_consoles)
        {
            if (sub_con->m_text_console_type == TEXT_CON_TYPE_SUB_TALK) sub_con->DisplayTextConsole(&sub_con->m_print_console, current_pos);
            else if (sub_con->m_text_console_type == TEXT_CON_TYPE_SUB_OPT) sub_con->DisplayTextConsole(&sub_con->m_print_console, 
                current_pos, m_battles[0], index);

            index++;
        }

        //Maps
        for (Map* map : m_maps)
        {
            map->DrawMap(m_player_object, scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);
        }

        //Actors
        for (Character *actor : m_actors)
        {
            if (actor->m_character_type == CHARACTER_TYPE_MAIN)
            {
                actor->PlayAnimation(current_anim_id, 
                    (screen_width / 2) - (actor->m_sprite_animations[current_anim_id]->m_spritesheet.m_sprite_w / 2),
                    (screen_height / 2) - (actor->m_sprite_animations[current_anim_id]->m_spritesheet.m_sprite_h / 2), 
                    8, current_flip);
            }
            else
            {
                //play all other animations
            }
        }

        // end drawing 2D graphics
        glEnd2D();
        glFlush(0);
    }
}

