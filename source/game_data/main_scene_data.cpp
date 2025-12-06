#include "main_scene_data.h"

void MainSceneData::InitializeData()
{
    cam_front_idle = new Sprite("sprite/cam_front_idle_spritesheet", 0, 0, 32, 32, 0);
    // cam_back_idle = new Sprite(4, 1, 32, 32);
    // cam_side_idle = new Sprite(4, 3, 32, 32);
    
    // cam_front_walk = new Sprite(4, 3, 32, 32);
    // cam_back_walk = new Sprite(4, 1, 32, 32);
    // cam_side_walk = new Sprite(4, 3, 32, 32);

    // //Now that the objects exist, we can load the graphics
    cam_front_idle->LoadSprite(cam_front_idle->m_sprite_id, cam_front_idle->m_gfx_slot, cam_front_idle->m_pal_slot, 
        ((SCREEN_WIDTH/cam_front_idle->m_sprite_w) / 2 - 0.5f) * cam_front_idle->m_sprite_w, ((SCREEN_HEIGHT/cam_front_idle->m_sprite_h) / 2 - 0.5f) * cam_front_idle->m_sprite_h, 
        false, 0);

    // town_ts->LoadSprite({new glImage[town_ts->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);
    // c_i_ts->LoadSprite({new glImage[c_i_ts->m_img_dimensions]}, collisionPal, collisionBitmap, GL_RGB256, 256);
    
    // cam_front_idle->LoadSprite({new glImage[cam_front_idle->m_img_dimensions]},cam_front_idle_spritesheetPal, cam_front_idle_spritesheetBitmap, GL_RGB256, 256);
    // cam_back_idle->LoadSprite({new glImage[cam_back_idle->m_img_dimensions]},cam_back_idle_spritesheetPal, cam_back_idle_spritesheetBitmap, GL_RGB256, 256);
    // cam_side_idle->LoadSprite({new glImage[cam_side_idle->m_img_dimensions]},cam_side_idle_spritesheetPal, cam_side_idle_spritesheetBitmap, GL_RGB256, 256);
    
    // cam_front_walk->LoadSprite({new glImage[cam_front_walk->m_img_dimensions]},cam_front_walk_spritesheetPal, cam_front_walk_spritesheetBitmap, GL_RGB256, 256);
    // cam_back_walk->LoadSprite({new glImage[cam_back_walk->m_img_dimensions]},cam_back_walk_spritesheetPal, cam_back_walk_spritesheetBitmap, GL_RGB256, 256);
    // cam_side_walk->LoadSprite({new glImage[cam_side_walk->m_img_dimensions]},cam_side_walk_spritesheetPal, cam_side_walk_spritesheetBitmap, GL_RGB256, 256);

    // //this is a crime im so sorry
    // text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, m_scene->m_main_consoles.size(), m_scene->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    // BgSize_T_256x256, 0, 3, 4, 0, false, false, &font_cellphone, 1, 1, 10, 5);

    // Background* test = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 4, 0, false);

    // test->LoadBackground(0, overworld_optionsBitmap, overworld_optionsBitmapLen, overworld_optionsPal, overworld_optionsPalLen);

    //Animation Objects
    cam_idle_f = new Animation(cam_front_idle, 12);
    // cam_idle_b = new Animation(cam_back_idle);
    // cam_idle_s = new Animation(cam_side_idle);
    
    // cam_walk_f = new Animation(cam_front_walk);
    // cam_walk_b = new Animation(cam_back_walk);
    // cam_walk_s = new Animation(cam_side_walk);

    //Scene Objects
    cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);

    // //add animations to character object
    // cam->AddAnimation(cam_idle_b);
    // cam->AddAnimation(cam_idle_s);
    // cam->AddAnimation(cam_walk_f);
    // cam->AddAnimation(cam_walk_b);
    // cam->AddAnimation(cam_walk_s);

    //add m_scene objects now that everything is loaded and added
    //FIFO
    //m_scene->AddBackground(test);
    m_scene->AddActor(cam);
    m_scene->m_player_object = cam;
}