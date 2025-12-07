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

void Scene::AddTextConsole(TextConsole *text_con)
{
    // Add the console to the respective vector
    if (text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_TALK)
        m_main_consoles.push_back(text_con);
    else if (text_con->m_text_console_type == TEXT_CON_TYPE_SUB_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_SUB_TALK)
        m_sub_consoles.push_back(text_con);
}

void Scene::AddBattle(Battle *battle)
{
    m_battles.push_back(battle);
}

void Scene::AddBackground(Background *background)
{
    m_backgrounds.push_back(background);
}

void Scene::DetectInput(int &scroll_x, int &scroll_y, bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right)
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

void Scene::SwitchAnimations(int &anim_id, bool &flip)
{
//     // play animation on input
//     // else if so multiple won't play at once on the same character

//     // UP
//     if (keysUp() & KEY_UP)
//     {
//         anim_id = 1;
//         flip = false;
//     }
//     else if (keysHeld() & KEY_UP)
//     {
//         anim_id = 4;
//         flip = false;
//     }

//     // DOWN
//     else if (keysUp() & KEY_DOWN)
//     {
//         anim_id = 0;
//         flip = false;
//     }
//     else if (keysHeld() & KEY_DOWN)
//     {
//         anim_id = 3;
//         flip = false;
//     }

//     // LEFT
//     else if (keysUp() & KEY_LEFT)
//     {
//         anim_id = 2;
//         flip = true;
//     }
//     else if (keysHeld() & KEY_LEFT)
//     {
//         anim_id = 5;
//         flip = true;
//     }

//     // RIGHT
//     else if (keysUp() & KEY_RIGHT)
//     {
//         anim_id = 2;
//         flip = false;
//     }
//     else if (keysHeld() & KEY_RIGHT)
//     {
//         anim_id = 5;
//         flip = false;
//     }
}

void Scene::DeleteAllTextures()
{
    
}

void Scene::DeleteAllSceneComponents()
{
    // Actors
    for (Character *actor : m_actors)
    {
        // actor->~Character();
        delete actor;
    }

    // TextConsoles
    for (TextConsole *console : m_main_consoles)
    {
        delete console;
    }

    for (TextConsole *console : m_sub_consoles)
    {
        delete console;
    }

    // Battles
    for (Battle *battle : m_battles)
    {
        delete battle;
    }

    //Backgrounds
    for (Background* background : m_backgrounds)
    {
        background->RemoveBackground();
        delete background;
    }
}

void Scene::ClearAllTextConsoles()
{
    for (TextConsole *console : m_main_consoles)
    {
        console->ClearTextConsole(&console->m_print_console);
    }

    for (TextConsole *console : m_sub_consoles)
    {
        console->ClearTextConsole(&console->m_print_console);
    }
}

void Scene::DrawScene(int scroll_x, int scroll_y, bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right)
{
    touchPosition current_pos;
    int current_anim_id = 0;
    bool current_flip = false;

    while (1)
    {

        // Update OAM array
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        // Wait for the screen refresh
        swiWaitForVBlank();

        scanKeys();

        //- - - - - user input - - - - -//
        DetectInput(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

        // quit game
        if (keysDown() & KEY_START)
        {
            m_player_quit = true;
            break;
        }

        // switch animations on input
        SwitchAnimations(current_anim_id, current_flip);

        //- - - - - - - - - - - - - - - - - - - - - -//


        //- - - - - scene components - - - - -//
        // Actors
        for (Character *actor : m_actors)
        {
            if (actor->m_character_type == CHARACTER_TYPE_MAIN)
            {
                actor->PlayAnimation(current_anim_id, 8, current_flip);
            }
            else
            {
                // play all other animations
            }
        }

         // Update OAM
        oamUpdate(&oamMain);
        oamUpdate(&oamSub); 
    }
}
