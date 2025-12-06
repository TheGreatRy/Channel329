#pragma once

//NDS Library Includes
#include <nf_lib.h>

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

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
    
    Background(BG_TYPE bg_type, const char *file, const char *name, u32 slot, u32 width, u32 height, u32 tile_start, u32 tile_end);
    
    BG_TYPE m_background_type;
    const char* m_name;
    u32 m_slot = -1;
    u32 m_width = -1;
    u32 m_height = -1;
    u32 m_start_tile = -1;
    u32 m_end_tile = -1;
};