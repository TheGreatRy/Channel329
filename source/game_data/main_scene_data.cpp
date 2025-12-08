#include "main_scene_data.h"

void MainSceneData::InitializeData()
{
    cam_front_idle = new Sprite("sprite/cam_front_idle_spritesheet", 0, 0, 32, 32, 0);
    options_bg = new Background(BG_TYPE_8BIT, "bmp/overworld_options");
    overworld_bg = new Background(BG_TYPE_TILED_FULL, "bg/overworld", "overworld", 0, 512, 512);
    
    cam_back_idle = new Sprite("sprite/cam_back_idle_spritesheet", 1, 1, 32, 32, 0);
    cam_side_idle = new Sprite("sprite/cam_side_idle_spritesheet", 2, 2, 32, 32, 0);
    
    cam_front_walk = new Sprite("sprite/cam_front_walk_spritesheet", 3, 3, 32, 32, 0);
    cam_back_walk = new Sprite("sprite/cam_back_walk_spritesheet", 4, 4, 32, 32, 0);
    cam_side_walk = new Sprite("sprite/cam_side_walk_spritesheet", 5, 5, 32, 32, 0);

    // Now that the objects exist, we can load the graphics
    cam_front_idle->LoadSprite(0, 0, 0, ((SCREEN_WIDTH/cam_front_idle->m_sprite_w) / 2 - 0.5f) * cam_front_idle->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_front_idle->m_sprite_h) / 2 - 0.5f) * cam_front_idle->m_sprite_h, false, 0);
    
    cam_back_idle->LoadSprite(1, 1, 1, ((SCREEN_WIDTH/cam_back_idle->m_sprite_w) / 2 - 0.5f) * cam_back_idle->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_back_idle->m_sprite_h) / 2 - 0.5f) * cam_back_idle->m_sprite_h, false, 0);
    
    cam_side_idle->LoadSprite(2, 2, 2, ((SCREEN_WIDTH/cam_side_idle->m_sprite_w) / 2 - 0.5f) * cam_side_idle->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_side_idle->m_sprite_h) / 2 - 0.5f) * cam_side_idle->m_sprite_h, false, 0);
    
    cam_front_walk->LoadSprite(3, 3, 3, ((SCREEN_WIDTH/cam_front_walk->m_sprite_w) / 2 - 0.5f) * cam_front_walk->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_front_walk->m_sprite_h) / 2 - 0.5f) * cam_front_walk->m_sprite_h, false, 0);
    
    cam_back_walk->LoadSprite(4, 4, 4, ((SCREEN_WIDTH/cam_back_walk->m_sprite_w) / 2 - 0.5f) * cam_back_walk->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_back_walk->m_sprite_h) / 2 - 0.5f) * cam_back_walk->m_sprite_h, false, 0);
    
    cam_side_walk->LoadSprite(5, 5, 5, ((SCREEN_WIDTH/cam_side_walk->m_sprite_w) / 2 - 0.5f) * cam_side_walk->m_sprite_w, 
        ((SCREEN_HEIGHT/cam_side_walk->m_sprite_h) / 2 - 0.5f) * cam_side_walk->m_sprite_h, false, 0);
     
    options_bg->LoadBackground(1, 1, 1);
    overworld_bg->LoadBackground(0, 3);

    //Animation Objects
    cam_idle_f = new Animation(cam_front_idle, 12);
    cam_idle_b = new Animation(cam_back_idle, 4);
    cam_idle_s = new Animation(cam_side_idle, 12);
    
    cam_walk_f = new Animation(cam_front_walk, 12);
    cam_walk_b = new Animation(cam_back_walk, 4);
    cam_walk_s = new Animation(cam_side_walk, 12);

    //Scene Objects
    cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);

    //add animations to character object
    cam->AddAnimation(cam_idle_b);
    cam->AddAnimation(cam_idle_s);
    cam->AddAnimation(cam_walk_f);
    cam->AddAnimation(cam_walk_b);
    cam->AddAnimation(cam_walk_s);

    //add m_scene objects now that everything is loaded and added
    //FIFO
    m_scene->AddBackground(options_bg);
    m_scene->AddActor(cam);
    m_scene->m_player_object = cam;
}