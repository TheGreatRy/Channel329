#include "main_scene_data.h"

void MainSceneData::InitializeData()
{
    options_bg = new Background(BG_TYPE_8BIT, "bmp/overworld_options");
    overworld_bg = new Background(BG_TYPE_TILED_FULL, "bg/overworld", "overworld", 0, 512, 512);
    overworld_col_bg = new Background(BG_TYPE_COL, "colbg/overworld_col", 0, 0, 512, 512);

    cam_front_idle = new Sprite(SPR_TYPE_256,"sprite/cam_front_idle_spritesheet", 0, 0, 32, 32, 0);
    cam_back_idle = new Sprite(SPR_TYPE_256,"sprite/cam_back_idle_spritesheet", 1, 1, 32, 32, 0);
    cam_side_idle = new Sprite(SPR_TYPE_256,"sprite/cam_side_idle_spritesheet", 2, 2, 32, 32, 0);
    
    cam_front_walk = new Sprite(SPR_TYPE_256,"sprite/cam_front_walk_spritesheet", 3, 3, 32, 32, 0);
    cam_back_walk = new Sprite(SPR_TYPE_256,"sprite/cam_back_walk_spritesheet", 4, 4, 32, 32, 0);
    cam_side_walk = new Sprite(SPR_TYPE_256,"sprite/cam_side_walk_spritesheet", 5, 5, 32, 32, 0);
    
    john_tutorial_ovwld = new Sprite(SPR_TYPE_256,"sprite/john_tutorial_overworld", 6, 6, 32, 32, 0);

    //test_text = new Text(TEXT_TYPE_CUST, "fnt/charmap_cellphone", "cam_text", 256, 256, 0, 2.5f, 2.5f);

    text_console = new TextConsole();

    text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, m_scene->m_main_cons.size(), m_scene->m_sub_cons.size(), new PrintConsole, 
    0, BgType_Text8bpp, BgSize_T_256x256, 0, 3, 4, 0, false, false, &font_anuvverbubbla, 3, 3, 23, 20);


    Position* cam_draw_pos = new Position(((SCREEN_WIDTH/cam_front_idle->m_sprite_w) / 2 - 0.5f) * cam_front_idle->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_front_idle->m_sprite_h) / 2 - 0.5f) * cam_front_idle->m_sprite_h);

    Position* john_draw_pos = new Position(-(32.0f * 10.5f) - 16.0f, -(32.0f * 9.0f) - 16.0f);

    // Now that the objects exist, we can load the graphics
    cam_front_idle->LoadSprite(0, 0, 0, cam_draw_pos, false, 0);
    cam_back_idle->LoadSprite(1, 1, 1, cam_draw_pos, false, 0);
    cam_side_idle->LoadSprite(2, 2, 2, cam_draw_pos, false, 0);
    
    cam_front_walk->LoadSprite(3, 3, 3, cam_draw_pos, false, 0);
    cam_back_walk->LoadSprite(4, 4, 4, cam_draw_pos, false, 0);
    cam_side_walk->LoadSprite(5, 5, 5, cam_draw_pos, false, 0);
    
    john_tutorial_ovwld->LoadSprite(6, 6, 6, john_draw_pos, false, 0);
     
    options_bg->LoadBackground(1, 1, 1);
    overworld_bg->LoadBackground(0, 3);

    // test_text->LoadText(1, 0);
    // test_text->AddText("Hello! Welcome to the demo of Channel329: Crimes of the Magically Inclined!\n\nThis is meant to be a proof of concept as well as my first game for the DS console.\n\nCONTROLS\n\nOverworld:\nDPAD: Move\nA:Interact\n\nBattle:\nX: Change Tone\nY: Change Topic\nA: Proceed");

    text_console->SetText("HELLO! WELLCOME TO THE DEMO OF CHANNEL329: CRIMES OF THE MAGICALLY INCLINED!\n\nTHIS IS MEANT TO BE A PROOF OF CONCEPT AS WELL AS MY FIRST GAME FOR THE DS CONSOLE.\n\nCONTROLS\n\nOVERWORLD:\nDPAD: MOVE\nA:INTERACT\n\nBATTLE:\nX: CHANGE TONE\nY: CHANGE TOPIC\nA: PROCEED", false);

    //Animation Objects
    cam_idle_f = new Animation(cam_front_idle, 12);
    cam_idle_b = new Animation(cam_back_idle, 4);
    cam_idle_s = new Animation(cam_side_idle, 12);
    
    cam_walk_f = new Animation(cam_front_walk, 12);
    cam_walk_b = new Animation(cam_back_walk, 4);
    cam_walk_s = new Animation(cam_side_walk, 12);

    john_tutorial_anim = new Animation(john_tutorial_ovwld, 1);

    //Scene Objects
    cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);

    //add animations to character object
    cam->AddAnimation(cam_idle_b);
    cam->AddAnimation(cam_idle_s);
    cam->AddAnimation(cam_walk_f);
    cam->AddAnimation(cam_walk_b);
    cam->AddAnimation(cam_walk_s);

    john_tutorial = new Character(john_tutorial_anim, "JOHN TUTORIAL", CHARACTER_TYPE_NPC);

    //add m_scene objects now that everything is loaded and added
    //FIFO
    m_scene->AddBackground(options_bg);
    m_scene->AddBackground(overworld_bg);
    m_scene->AddBackground(overworld_col_bg);
    m_scene->AddTextConsole(text_console);
    //m_scene->AddTextLayer(test_text);
    m_scene->AddActor(cam);
    m_scene->AddActor(john_tutorial);
    m_scene->m_player_object = cam;
}