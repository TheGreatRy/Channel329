#include "main_scene_data.h"

void MainSceneData::InitializeData()
{
    text_console = new TextConsole();
    town_ts = new Tileset(10, 10, 16, 16);
    c_i_ts = new Tileset(4, 1, 16, 16);

    cam_front_idle = new Tileset(4, 3, 32, 32);
    cam_back_idle = new Tileset(4, 1, 32, 32);
    cam_side_idle = new Tileset(4, 3, 32, 32);
    
    cam_front_walk = new Tileset(4, 3, 32, 32);
    cam_back_walk = new Tileset(4, 1, 32, 32);
    cam_side_walk = new Tileset(4, 3, 32, 32);

    // //Now that the objects exist, we can load the graphics
    // town_ts->LoadTileset({new glImage[town_ts->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);
    // c_i_ts->LoadTileset({new glImage[c_i_ts->m_img_dimensions]}, collisionPal, collisionBitmap, GL_RGB256, 256);
    
    // cam_front_idle->LoadTileset({new glImage[cam_front_idle->m_img_dimensions]},cam_front_idle_spritesheetPal, cam_front_idle_spritesheetBitmap, GL_RGB256, 256);
    // cam_back_idle->LoadTileset({new glImage[cam_back_idle->m_img_dimensions]},cam_back_idle_spritesheetPal, cam_back_idle_spritesheetBitmap, GL_RGB256, 256);
    // cam_side_idle->LoadTileset({new glImage[cam_side_idle->m_img_dimensions]},cam_side_idle_spritesheetPal, cam_side_idle_spritesheetBitmap, GL_RGB256, 256);
    
    // cam_front_walk->LoadTileset({new glImage[cam_front_walk->m_img_dimensions]},cam_front_walk_spritesheetPal, cam_front_walk_spritesheetBitmap, GL_RGB256, 256);
    // cam_back_walk->LoadTileset({new glImage[cam_back_walk->m_img_dimensions]},cam_back_walk_spritesheetPal, cam_back_walk_spritesheetBitmap, GL_RGB256, 256);
    // cam_side_walk->LoadTileset({new glImage[cam_side_walk->m_img_dimensions]},cam_side_walk_spritesheetPal, cam_side_walk_spritesheetBitmap, GL_RGB256, 256);

    // //this is a crime im so sorry
    // text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, m_scene->m_main_consoles.size(), m_scene->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    // BgSize_T_256x256, 0, 3, 4, 0, false, false, &font_cellphone, 1, 1, 10, 5);

    // Background* test = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 4, 0, false);

    // test->LoadBackground(0, overworld_optionsBitmap, overworld_optionsBitmapLen, overworld_optionsPal, overworld_optionsPalLen);

    //Animation Objects
    cam_idle_f = new Animation(cam_front_idle);
    cam_idle_b = new Animation(cam_back_idle);
    cam_idle_s = new Animation(cam_side_idle);
    
    cam_walk_f = new Animation(cam_front_walk);
    cam_walk_b = new Animation(cam_back_walk);
    cam_walk_s = new Animation(cam_side_walk);

    //Scene Objects
    cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);
    coll_inter = new Map(c_i_ts, 30, 20, collisions_interaction, MAP_TYPE_COL_INTER);
    town = new Map(town_ts, 30, 20, map, MAP_TYPE_BG_MAIN);

    //add animations to character object
    cam->AddAnimation(cam_idle_b);
    cam->AddAnimation(cam_idle_s);
    cam->AddAnimation(cam_walk_f);
    cam->AddAnimation(cam_walk_b);
    cam->AddAnimation(cam_walk_s);

    //add m_scene objects now that everything is loaded and added
    //FIFO
    //m_scene->AddBackground(test);
    m_scene->AddMap(coll_inter);
    m_scene->AddMap(town);
    m_scene->AddActor(cam);
    m_scene->AddTextConsole(text_console);
    m_scene->m_player_object = cam;
}