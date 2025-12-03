#pragma once

//Components Folder
#include "../components/tileset.h"

#include "../game_data/background_data.h"

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class Background
{
public:


    Background(int layer, BgType bg_type, BgSize bg_size, int map_base, int tile_base, bool is_main, BackgroundData* data);
    ~Background() = default;

    int m_background_id;
    bool m_is_main;
    BackgroundData* m_data;

    void LoadBackground(int bpp);
};