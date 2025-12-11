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
        delete battle;
    }

    // Backgrounds
    for (Background *background : m_backgrounds)
    {
        background->RemoveBackground();
        delete background;
    }

    for (Text* text : m_text_layers)
    {
        text->ClearText();
        text->RemoveText();
        delete text;
    }

    NF_ResetSpriteBuffers();
    NF_ResetTiledBgBuffers();
    NF_Reset8bitsBgBuffers();
}


void Scene::DrawScene(int &scroll_x, int &scroll_y, bool &can_move_up, bool &can_move_down, bool &can_move_left, bool &can_move_right)
{
    touchPosition current_pos;
    int current_anim_id = 0;
    bool current_flip = false;
    
    NF_Sort3dSprites();

    bool shifting_tones = false;
    bool shifting_topics = false;

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
            if (shifting_tones || shifting_topics)
            {
                shifting_tones = false;
                shifting_topics = false;

                m_battles[0]->CheckAttackPhrase();
            }
            else
            {
                // switch to game
                if (m_scene_gm_state != GM_STATE_BATTLE)
                {
                    m_switch_gm_state = GM_STATE_BATTLE;
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
            if (background->m_bg_type == BG_TYPE_TILED_FULL && m_scene_gm_state != GM_STATE_BATTLE) NF_ScrollBg(background->m_screen, background->m_layer, scroll_x, scroll_y);
        }

        //Text Layers
        for (Text* text : m_text_layers)
        {
            text->WriteText();
        }

        for (Battle* battle : m_battles)
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

            if (shifting_tones) battle->CycleTones();
            else if (shifting_topics) battle->CycleTopics();

        }

        NF_Draw3dSprites();
        NF_UpdateTextLayers();

        glFlush(0);
    }
}
