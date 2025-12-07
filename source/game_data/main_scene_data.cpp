#include "main_scene_data.h"

void MainSceneData::InitializeData()
{
    cam_front_idle = new Sprite("sprite/cam_front_idle_spritesheet", 0, 0, 32, 32, 0);
    options_bg = new Background(BG_TYPE_8BIT, "bmp/overworld_options");
    overworld_bg = new Background(BG_TYPE_TILED_FULL, "bg/overworld", "overworld", 0, 512, 512);
    
    // cam_back_idle = new Sprite(4, 1, 32, 32);
    // cam_side_idle = new Sprite(4, 3, 32, 32);
    
    // cam_front_walk = new Sprite(4, 3, 32, 32);
    // cam_back_walk = new Sprite(4, 1, 32, 32);
    // cam_side_walk = new Sprite(4, 3, 32, 32);

    // Now that the objects exist, we can load the graphics
    cam_front_idle->LoadSprite(cam_front_idle->m_sprite_id, cam_front_idle->m_gfx_slot, cam_front_idle->m_pal_slot, 
        ((SCREEN_WIDTH/cam_front_idle->m_sprite_w) / 2 - 0.5f) * cam_front_idle->m_sprite_w, ((SCREEN_HEIGHT/cam_front_idle->m_sprite_h) / 2 - 0.5f) * cam_front_idle->m_sprite_h, 
        false, 0);
    
        
    options_bg->LoadBackground(1, 1, 1);
    overworld_bg->LoadBackground(0, 3);

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
    m_scene->AddBackground(options_bg);
    m_scene->AddActor(cam);
    m_scene->m_player_object = cam;
}