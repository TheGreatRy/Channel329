#include "background.h"

Background::Background(int layer, BgType bg_type, BgSize bg_size, int map_base, int tile_base, bool is_main)
{
    m_background_id = bgInit(layer, bg_type, bg_size, map_base, tile_base);
    m_is_main = is_main;
}

void Background::LoadBackground(void* tile_source, uint32_t tile_size, void* map_source, uint32_t map_size, void* pal_source, uint32_t pal_size)
{
    dmaCopy(tile_source, bgGetGfxPtr(m_background_id), tile_size);
    dmaCopy(map_source, bgGetMapPtr(m_background_id), map_size);

    if (m_is_main)
        dmaCopy(pal_source, BG_PALETTE, pal_size);
    else
        dmaCopy(pal_source, BG_PALETTE_SUB, pal_size);

}
