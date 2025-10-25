#include <memory>
#include <vector>

#include <nds.h>
#include <stdio.h>
#include <dlfcn.h>
#include <gl2d.h>

enum TS_TAG
{
    TS_CHARACTER,
    TS_BACKGROUND
};

enum TS_SIZE
{
    TS_FULL_TEXTURE,
    TS_PALETTE_LENGTH
};

class Tileset
{
    public:
    int m_texture_id = 0;
    int m_sprites_num_x= 1;
    int m_sprites_num_y = 1;
    int m_img_dimensions = 1;
    int m_sprite_h = 8;
    int m_sprite_w = 8;
    int m_offset_x = 0;
    int m_offset_y = 0;

    std::vector<glImage> m_tileset_img;
    TS_TAG m_tag = TS_BACKGROUND;

    Tileset(const int spr_num_x, const int spr_num_y, const int spr_w, const int spr_h, TS_TAG ts_tag);
    ~Tileset() = default;
    
    void LoadTileset(glImage tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[], GL_TEXTURE_TYPE_ENUM tex_type, const unsigned int pal_len);

    private:
    int PaddingForPowerOfTwo(int x, int y, TS_SIZE ts_size);
};