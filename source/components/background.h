#pragma once

//Components Folder
#include "../components/tileset.h"

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class Background
{
public:


    Background(int layer, BgType bg_type, BgSize bg_size, int map_base, int tile_base, bool is_main);
    ~Background() = default;

    int m_background_id;
    bool m_is_main;

    void LoadBackground(void* tile_source, uint32_t tile_size, void* map_source, uint32_t map_size, void* pal_source, uint32_t pal_size);
};