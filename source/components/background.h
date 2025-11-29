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

    void LoadBackground(int bitmap_base, const unsigned int* bitmap_source, uint32_t bitmap_size, const unsigned short*  pal_source, uint32_t pal_size);
    void LoadBackground(int bitmap_base, const unsigned int* bitmap_source, uint32_t bitmap_size);
};