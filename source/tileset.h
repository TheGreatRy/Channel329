#include <memory>
#include <vector>

#include <nds.h>
#include <stdio.h>

#include <gl2d.h>

class Tileset
{
    public:
    Tileset(const int frames, const int spr_w, const int spr_h);
    ~Tileset() = default;

    int m_frames_num = 1;
    int m_texture_id = 0;
    int m_sprite_h = 8;
    int m_sprite_w = 8;

    std::vector<glImage> m_frames_img;

    void DrawTileset(glImage Tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[]);
};