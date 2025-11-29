#include "main_data.h"

void MainData::InitializeMain()
{
    main_scene = new Scene(GM_STATE_MAIN, 0);

    CustomFonts* cf = new CustomFonts();

    const int16_t map[30 * 20] = 
    {
        94, 95, 84, 85, 94, 95, 84, 85, 94, 95,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 84, 85, 84, 85, 94, 95, 84, 85, 84, 85,
        84, 85, 94, 95, 84, 85, 94, 95,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 94, 95, 84, 85, 94, 95, 94, 95,
        94, 95, 84, 85, 94, 95,  1,  0,  1,  1,  1,  1,  1,  1,  7,  7,  7,  1,  0,  1,  1,  1,  1,  1, 94, 95, 84, 85, 84, 85,
        1,  1, 94, 95,  1,  1,  1,  7,  1,  1,  1,  1,  1,  1,  1,  0,  2,  1,  1,  1,  1,  1,  1,  1,  7,  7, 94, 95, 94, 95,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  7,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84, 85,
        1,  1,  7,  0,  1,  1,  1,  1,  1,  1,  7,  2,  1,  1,  1,  7,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95,
        1,  7,  7,  7,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 47, 48, 48, 48, 49,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84,
        0, 17, 18, 18, 18, 18, 18, 18, 19,  1,  1,  1,  1,  1,  1, 57, 58, 58, 58, 59,  1,  1,  1,  1,  0,  1,  1,  1,  1, 94,
        0, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  7, 67, 68, 68, 68, 69,  1,  1,  7,  7,  2,  1,  7,  1, 84, 85,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  1, 87, 97, 98, 99, 89,  1,  1,  0,  7,  7,  0,  0,  1, 94, 95,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 84, 85, 84,
        0, 27,  1,  1,  1,  1,  1,  1, 29,  7,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 94,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  2,  7,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84, 85,
        1, 37, 38, 38, 38, 38, 28, 38, 39,  7,  7,  1,  1,  1,  1, 20, 21, 21, 21, 21, 21, 21, 21, 22,  1,  1,  1,  1, 94, 95,
        7,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  7,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1, 84, 85,
        0,  7,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 43, 22,  1,  2,  1, 94, 95,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  7,  1,  1, 84,
        1,  1,  1,  1,  1,  1,  1,  1,  7,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1, 94,
        1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 43, 22,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1 
    };

    const int16_t collisions_interaction[30 * 20] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
    }; 
    
    //We need to initialize all objects that use a tileset
    TextConsole* text_console = new TextConsole();
    TextConsole* main_con = new TextConsole();
    Tileset* options_bg_ts = new Tileset(1, 1, 256, 256);
    Tileset* town_ts = new Tileset(10, 10, 16, 16);
    Tileset* c_i_ts = new Tileset(4, 1, 16, 16);
    
    Tileset* cam_front_idle = new Tileset(4, 3, 32, 32);
    Tileset* cam_back_idle = new Tileset(4, 1, 32, 32);
    Tileset* cam_side_idle = new Tileset(4, 3, 32, 32);
    
    Tileset* cam_front_walk = new Tileset(4, 3, 32, 32);
    Tileset* cam_back_walk = new Tileset(4, 1, 32, 32);
    Tileset* cam_side_walk = new Tileset(4, 3, 32, 32);
    
    //Now that the objects exist, we can load the graphics
    town_ts->LoadTileset({new glImage[town_ts->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);
    c_i_ts->LoadTileset({new glImage[c_i_ts->m_img_dimensions]}, collisionPal, collisionBitmap, GL_RGB256, 256);
    options_bg_ts->LoadTileset({new glImage[options_bg_ts->m_img_dimensions]}, overworld_optionsPal, overworld_optionsBitmap, GL_RGB256, 256);
    
    cam_front_idle->LoadTileset({new glImage[cam_front_idle->m_img_dimensions]},cam_front_idle_spritesheetPal, cam_front_idle_spritesheetBitmap, GL_RGB256, 256);
    cam_back_idle->LoadTileset({new glImage[cam_back_idle->m_img_dimensions]},cam_back_idle_spritesheetPal, cam_back_idle_spritesheetBitmap, GL_RGB256, 256);
    cam_side_idle->LoadTileset({new glImage[cam_side_idle->m_img_dimensions]},cam_side_idle_spritesheetPal, cam_side_idle_spritesheetBitmap, GL_RGB256, 256);
    
    cam_front_walk->LoadTileset({new glImage[cam_front_walk->m_img_dimensions]},cam_front_walk_spritesheetPal, cam_front_walk_spritesheetBitmap, GL_RGB256, 256);
    cam_back_walk->LoadTileset({new glImage[cam_back_walk->m_img_dimensions]},cam_back_walk_spritesheetPal, cam_back_walk_spritesheetBitmap, GL_RGB256, 256);
    cam_side_walk->LoadTileset({new glImage[cam_side_walk->m_img_dimensions]},cam_side_walk_spritesheetPal, cam_side_walk_spritesheetBitmap, GL_RGB256, 256);
    
    //BG Layer
    Background* options_bg = new Background(0, BgType_Bmp8, BgSize_B8_256x256, 0, 1, false);
    options_bg->LoadBackground(0, overworld_optionsBitmap, overworld_optionsBitmapLen, overworld_optionsPal, overworld_optionsPalLen);

    //Text Consoles
    text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, main_scene->m_main_consoles.size(), main_scene->m_sub_consoles.size(), {new PrintConsole}, 1, BgType_Text4bpp,
    BgSize_T_256x256, 1, 2, 4, 0, false, false, &cf->font_cellphone, 1, 1, 10, 5);
    
    text_console->SetText("test sub", false);
    
    
    //create animations from loaded tilesets
    Animation* cam_idle_f = new Animation(cam_front_idle);
    Animation* cam_idle_b = new Animation(cam_back_idle);
    Animation* cam_idle_s = new Animation(cam_side_idle);
    
    Animation* cam_walk_f = new Animation(cam_front_walk);
    Animation* cam_walk_b = new Animation(cam_back_walk);
    Animation* cam_walk_s = new Animation(cam_side_walk);

    //create scene objects
    Character* cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);
    Map* coll_inter = new Map(c_i_ts, 30, 20, collisions_interaction, MAP_TYPE_COL_INTER);
    Map* town = new Map(town_ts, 30, 20, map, MAP_TYPE_BG_MAIN);

    //add animations to character object
    cam->AddAnimation(cam_idle_b);
    cam->AddAnimation(cam_idle_s);
    cam->AddAnimation(cam_walk_f);
    cam->AddAnimation(cam_walk_b);
    cam->AddAnimation(cam_walk_s);

    //add scene objects now that everything is loaded and added
    //FIFO
    main_scene->AddBackground(options_bg);
    main_scene->AddMap(coll_inter);
    main_scene->AddMap(town);
    main_scene->AddActor(cam);
    main_scene->AddTextConsole(text_console);
    main_scene->AddTextConsole(main_con);
    main_scene->m_player_object = cam;
}
