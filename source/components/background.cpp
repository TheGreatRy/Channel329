#include "background.h"

/// @brief Able to initalize all background types. Only use the parameters needed for the background type
/// @param bg_type Background type as defined in BG_TYPE (`ALL`)
/// @param file File path without extension (`ALL`)
/// @param name File name without extension (`BG_TYPE_AFFINE` and `BG_TYPE_TILED_FULL`)
/// @param slot Slot number (`BG_TYPE_COL`)
/// @param width Background image width in pixels (`BG_TYPE_AFFINE`, `BG_TYPE_COL`, `BG_TYPE_TILED_FULL`, and `BG_TYPE_TILED_RANGE`)
/// @param height Background image height in pixels (`BG_TYPE_AFFINE`, `BG_TYPE_COL`, `BG_TYPE_TILED_FULL`, and `BG_TYPE_TILED_RANGE`)
/// @param tile_start First tile to load (`BG_TYPE_TILED_RANGE`)
/// @param tile_end Last tile to load (`BG_TYPE_TILED_RANGE`)
Background::Background(BG_TYPE bg_type, const char *file, const char *name = "default", u32 slot = -1, u32 width = -1, u32 height = -1, u32 tile_start = -1, u32 tile_end = -1)
{
    m_background_type = bg_type;
    m_name = name;
    m_slot = slot;
    m_width = width;
    m_height = height;
    m_start_tile = tile_start;
    m_end_tile = tile_end;

    switch (m_background_type)
    {
        case BG_TYPE_8BIT:
            NF_Load8bitsBg(file, m_slot);
            break;
        case BG_TYPE_16BIT:
            NF_Load16bitsBg(file, m_slot);
            break;
        case BG_TYPE_AFFINE:
            NF_LoadAffineBg(file, m_name, m_width, m_height);
            break;
        case BG_TYPE_COL:
            NF_LoadCollisionBg(file, m_slot, m_width, m_height);
            break;
        case BG_TYPE_TILED_FULL:
            NF_LoadTiledBg(file, m_name, m_width, m_height);
            break;
        case BG_TYPE_TILED_RANGE:
            NF_LoadTilesForBg(file, m_name, m_width, m_height, m_start_tile, m_end_tile);
            break;
    }
}
