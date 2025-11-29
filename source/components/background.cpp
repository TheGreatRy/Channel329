#include "background.h"

Background::Background(int layer, BgType bg_type, BgSize bg_size, int map_base, int tile_base, bool is_main)
{
    if (is_main)
        m_background_id = bgInit(layer, bg_type, bg_size, map_base, tile_base);
    else 
        m_background_id = bgInitSub(layer, bg_type, bg_size, map_base, tile_base);

    m_is_main = is_main;
}

void Background::LoadBackground(int bitmap_base, const unsigned int* bitmap_source, uint32_t bitmap_size, const unsigned short*  pal_source, uint32_t pal_size)
{
    
    if (m_is_main)
        dmaCopy(pal_source, BG_PALETTE, pal_size);
    else
        dmaCopy(pal_source, BG_PALETTE_SUB, pal_size);

    bgSetMapBase(m_background_id, bitmap_base);
    
    dmaCopy(bitmap_source, bgGetGfxPtr(m_background_id), bitmap_size);
}

void Background::LoadBackground(int bitmap_base, const unsigned int *bitmap_source, uint32_t bitmap_size)
{
    bgSetMapBase(m_background_id, bitmap_base);
    
    dmaCopy(bitmap_source, bgGetGfxPtr(m_background_id), bitmap_size);
}
