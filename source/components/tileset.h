#pragma once

//C++ Libraries
#include <memory>
#include <vector>

//NDS Libraries
#include <nds.h>
#include <stdio.h>
#include <dlfcn.h>
#include <gl2d.h>

enum TS_SIZE
{
    TS_SIZE_FULL_TEX,
    TS_SIZE_PAL_LEN
};

class Tileset
{
public:

    Tileset();
    Tileset(const int spr_num_x, const int spr_num_y, const int spr_w, const int spr_h);
    ~Tileset() = default;

    int m_texture_id = 0;
    int m_sprites_num_x = 1;
    int m_sprites_num_y = 1;
    int m_img_dimensions = 1;
    int m_sprite_h = 8;
    int m_sprite_w = 8;
    int m_offset_x = 0;
    int m_offset_y = 0;

    std::vector<glImage> m_tileset_img;

    void LoadTileset(glImage tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[], GL_TEXTURE_TYPE_ENUM tex_type, const unsigned int pal_len);
    
private:
    int PaddingForPowerOfTwo(int x, int y, TS_SIZE ts_size);
};