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

void Scene::AddSprite(Sprite *sprite)
{
    m_sprites.push_back(sprite);
}

void Scene::AddTextLayer(Text *text)
{
    m_text_layers.push_back(text);
}

void Scene::AddTextConsole(TextConsole *text_con)
{
    if (text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_MAIN_TALK)
        m_main_cons.push_back(text_con);

    else if (text_con->m_text_console_type == TEXT_CON_TYPE_SUB_OPT || text_con->m_text_console_type == TEXT_CON_TYPE_SUB_TALK)
        m_sub_cons.push_back(text_con);
}

void Scene::AddBattle(Battle *battle)
{
    m_battles.push_back(battle);
}

void Scene::CheckCollision(Background* col_bg, int &scroll_x, int &scroll_y, bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right)
{
    for (int x = 0; x < 31; x ++)
    {
        can_move_up = (NF_GetPoint(col_bg->m_slot, scroll_x + 113 + x, scroll_y + 80) == 3) ? false : true;
        if (can_move_up == false) break;
    }

    //Check bottom 
    for (int x = 0; x < 31; x ++)
    {
        can_move_down = (NF_GetPoint(col_bg->m_slot, scroll_x + 113 + x, scroll_y + 112) == 3) ? false : true;
        if (can_move_down == false) break;
    }

    //Check left side of sprite
    for (int y = 0; y < 31; y++)
    {
        can_move_left = (NF_GetPoint(col_bg->m_slot, scroll_x + 112, scroll_y + 81 + y) == 3) ? false : true;
        if (can_move_left == false) break;
    }

    //Check right of sprite
    for (int y = 0; y < 31; y++)
    {
        can_move_right = (NF_GetPoint(col_bg->m_slot, scroll_x + 144, scroll_y + 81 + y) == 3) ? false : true;
        if (can_move_right == false) break;
    }
    
}

void Scene::CheckInteractions(Background *col_bg, int &scroll_x, int &scroll_y, bool& can_battle)
{
    for (int x = 0; x < 32; x ++)
    {
        can_battle = (NF_GetPoint(col_bg->m_slot, scroll_x + 112 + x, scroll_y + 80) == 2) ? true : false;
        if (can_battle == true) return;
    }

    //Check bottom 
    for (int x = 0; x < 31; x ++)
    {
        can_battle = (NF_GetPoint(col_bg->m_slot, scroll_x + 112 + x, scroll_y + 112) == 2) ? true : false;
        if (can_battle == true) return;
    }

    //Check left side of sprite
    for (int y = 0; y < 31; y++)
    {
        can_battle = (NF_GetPoint(col_bg->m_slot, scroll_x + 112, scroll_y + 80 + y) == 2) ? true : false;
        if (can_battle == true) return;
    }

    //Check right of sprite
    for (int y = 0; y < 31; y++)
    {
        can_battle = (NF_GetPoint(col_bg->m_slot, scroll_x + 144, scroll_y + 80 + y) == 2) ? true : false;
        if (can_battle == true) return;
    }
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
    // play animation on input
    // else if so multiple won't play at once on the same character

    // UP
    if (keysUp() & KEY_UP)
    {
        anim_id = 1;
        flip = false;
    }
    else if (keysHeld() & KEY_UP)
    {
        anim_id = 4;
        flip = false;
    }

    // DOWN
    else if (keysUp() & KEY_DOWN)
    {
        anim_id = 0;
        flip = false;
    }
    else if (keysHeld() & KEY_DOWN)
    {
        anim_id = 3;
        flip = false;
    }

    // LEFT
    else if (keysUp() & KEY_LEFT)
    {
        anim_id = 2;
        flip = true;
    }
    else if (keysHeld() & KEY_LEFT)
    {
        anim_id = 5;
        flip = true;
    }

    // RIGHT
    else if (keysUp() & KEY_RIGHT)
    {
        anim_id = 2;
        flip = false;
    }
    else if (keysHeld() & KEY_RIGHT)
    {
        anim_id = 5;
        flip = false;
    }
}

void Scene::DeleteAllSceneComponents()
{
    // Actors
    for (Character *actor : m_actors)
    {
        for (Animation *anim : actor->m_sprite_animations)
        {
            anim->m_spritesheet->RemoveSprite();
            delete anim;
        }
        delete actor;
    }
    // Other Sprites
    for (Sprite* sprite : m_sprites)
    {
        sprite->RemoveSprite();
        delete sprite;
    }
    // Battles
    for (Battle *battle : m_battles)
    {
        delete battle->m_battle_response;
        delete battle->m_tone_text;
        delete battle->m_topic_text;

        delete battle;
    }

    // Backgrounds
    for (Background *background : m_backgrounds)
    {
        background->RemoveBackground();
        delete background;
    }

    // Text
    for (TextConsole* main_con : m_main_cons)
    {
        delete main_con;
    }

    for (TextConsole* sub_con : m_sub_cons)
    {
        delete sub_con;
    }

    // for (Text* text : m_text_layers)
    // {
    //     text->ClearText();
    //     text->RemoveText();
    //     delete text;
    // }

    NF_ResetSpriteBuffers();
    NF_ResetTiledBgBuffers();
    NF_Reset8bitsBgBuffers();
    NF_ResetCmapBuffers();
    NF_ResetRawSoundBuffers();
}

void Scene::ClearAllTextConsoles()
{
    for (Battle* battle : m_battles)
    {
        battle->m_battle_response->ClearTextConsole(&battle->m_battle_response->m_print_console);
        battle->m_tone_text->ClearTextConsole(&battle->m_tone_text->m_print_console);
        battle->m_topic_text->ClearTextConsole(&battle->m_topic_text->m_print_console);
    }

    // Text
    for (TextConsole* main_con : m_main_cons)
    {
        main_con->ClearTextConsole(&main_con->m_print_console);
    }

    for (TextConsole* sub_con : m_sub_cons)
    {
        sub_con->ClearTextConsole(&sub_con->m_print_console);
    }
}

void Scene::ValidateColBg(bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right, bool &can_battle)
{
    if (keysUp() & KEY_B)
    {
        std::string col_out = "MOVE UP? " + std::to_string(can_move_up) + "\nMOVE DOWN? " + std::to_string(can_move_down) + "\nMOVE LEFT? " + std::to_string(can_move_left) + "\nMOVE RIGHT? " + std::to_string(can_move_right) + "\nCAN BATTLE? " + std::to_string(can_battle);
        m_sub_cons[0]->SetText(col_out, false);
        m_sub_cons[0]->DisplayTextConsole(&m_sub_cons[0]->m_print_console);
    }
}

void Scene::DrawScene(int &scroll_x, int &scroll_y, bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right)
{
    touchPosition current_pos;
    int current_anim_id = 0;
    bool current_flip = false;
    
    NF_Sort3dSprites();

    bool shifting_tones = false;
    bool shifting_topics = false;

    bool confirm = false;
    bool can_battle = true;

    while (1)
    {

        // Update OAM array
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        // Wait for the screen refresh
        swiWaitForVBlank();

        // Update OAM
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);

        scanKeys();

        //- - - - - user input - - - - -//
        DetectInput(scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);

        // quit game
        if (keysDown() & KEY_START)
        {
            m_player_quit = true;
            break;
        }

        // switch scenes
        if (keysUp() & KEY_A)
        {
            //accept user input
            if (shifting_tones || shifting_topics)
            {
                confirm = true;

                shifting_tones = false;
                shifting_topics = false;

                m_battles[0]->CheckAttackPhrase();
            }
            else if (can_battle)
            {
                // switch to game
                if (m_scene_gm_state != GM_STATE_BATTLE)
                {

                    if (keysUp() & KEY_A)
                    {
                        m_switch_gm_state = GM_STATE_BATTLE;
                        break;
                    }
                    else if (keysUp() & KEY_B)
                        break;
                }
                m_player_quit = false;
                break;
            }

            // switch to main
            if (m_scene_gm_state != GM_STATE_MAIN)
            {
                m_switch_gm_state = GM_STATE_MAIN;
                m_player_quit = false;
                break;
            }
        }

        // switch animations on input
        SwitchAnimations(current_anim_id, current_flip);

        //- - - - - - - - - - - - - - - - - - - - - -//

        //- - - - - scene components - - - - -//
        // Actors
        for (Character *actor : m_actors)
        {
            for (Animation *anim : actor->m_sprite_animations)
            {
                //if(anim->m_spritesheet->m_spr_type == SPR_TYPE_256) 
                NF_ShowSprite(anim->m_spritesheet->m_screen, anim->m_spritesheet->m_sprite_id, false);
                //else if(anim->m_spritesheet->m_spr_type == SPR_TYPE_3D)NF_Show3dSprite(anim->m_spritesheet->m_sprite_id, false);
            }

            if (actor->m_character_type == CHARACTER_TYPE_MAIN)
            {
                actor->PlayAnimation(current_anim_id, 8, current_flip);
            }
            else
            {
                actor->PlayAnimation(0, 8, false, scroll_x, scroll_y);
            }
        }

        //Backgrounds
        for (Background *background : m_backgrounds)
        {
            if (m_scene_gm_state != GM_STATE_BATTLE && background->m_screen == 0) 
            {
                NF_ScrollBg(background->m_screen, background->m_layer, scroll_x, scroll_y);
            }
            if (background->m_bg_type == BG_TYPE_COL) 
            {
                CheckCollision(background, scroll_x, scroll_y, can_move_up, can_move_down, can_move_left, can_move_right);
                CheckInteractions(background, scroll_x, scroll_y, can_battle);
            }
        }

        for (Battle *battle : m_battles)
        {
            if (!confirm)
            {
                if (keysUp() & KEY_X)
                {
                    shifting_tones = true;
                    shifting_topics = false;
                }
                else if (keysUp() & KEY_Y)
                {
                    shifting_tones = false;
                    shifting_topics = true;
                }

                if (shifting_tones)
                    battle->CycleTones();
                else if (shifting_topics)
                    battle->CycleTopics();
            }
        }

         // Main Screen Text Consoles
        for (TextConsole *main_con : m_main_cons)
        {
            if (m_scene_gm_state != GM_STATE_BATTLE) main_con->DisplayTextConsole(&main_con->m_print_console);
        }

        //int index = 0;
        // Sub Screen Text Consoles
        for (TextConsole *sub_con : m_sub_cons)
        {
            if (m_scene_gm_state != GM_STATE_BATTLE) sub_con->DisplayTextConsole(&sub_con->m_print_console, current_pos);
            if (m_scene_gm_state != GM_STATE_BATTLE && can_battle)
            {
                sub_con->SetText("WOULD YOU LIKE TO INTERROGATE THIS NPC?\nA: YES\nB: NO", false);
                sub_con->DisplayTextConsole(&sub_con->m_print_console);
            }
            else if (m_scene_gm_state != GM_STATE_BATTLE && !can_battle)
            {
                ValidateColBg(can_move_up, can_move_down, can_move_left, can_move_right, can_battle);
            }
        }

        NF_Draw3dSprites();

        glFlush(0);
    }
}
