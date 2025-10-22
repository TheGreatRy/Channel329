#include <memory>
#include <vector>

#include <nds.h>
#include <stdio.h>

#include <gl2d.h>

class Tileset
{
    public:
    Tileset(const int spr_num_x, const int spr_num_y, const int spr_w, const int spr_h);
    ~Tileset() = default;
    
    int m_texture_id = 0;
    int m_sprites_num_x= 1;
    int m_sprites_num_y = 1;
    int m_sprite_h = 8;
    int m_sprite_w = 8;

    std::vector<glImage> m_tileset_img;

    void LoadTileset(glImage tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[]);
};