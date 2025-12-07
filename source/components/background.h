#pragma once

//NDS Library Includes
#include <nf_lib.h>

enum BG_TYPE
{
    BG_TYPE_8BIT,
    BG_TYPE_16BIT,
    BG_TYPE_AFFINE,
    BG_TYPE_COL,
    BG_TYPE_TILED_FULL,
    BG_TYPE_TILED_RANGE
};

class Background
{
public:
    Background() = default;
    ~Background() = default;
    
    Background(BG_TYPE bg_type, const char *file, const char *name = "default", u32 slot = 0, u32 width = 0, u32 height = 0, u32 tile_start = 0, u32 tile_end = 0);
    
    BG_TYPE m_background_type;
    const char* m_name;
    u32 m_slot = 0;
    u32 m_width = 0;
    u32 m_height = 0;
    u32 m_start_tile = 0;
    u32 m_end_tile = 0;

    int m_screen;
    int m_layer;

    void LoadBackground(int screen, int layer = 0, int copy_dest = 0, bool can_wrap = false);
    void RemoveBackground();
    
    private:
    void UnloadBackgroundRAM();
};