#include "map.h"

// Crime method, but inputs correct coords
Map::Map(Tileset *layer, int width, int height, const int16_t tile_id_arr[])
{
    m_layer_info = *layer;
    m_width = width;
    m_height = height;

    // the algorithm is inputing (x,y)[value] down the column then across the row
    int current_y = 0;
    for (int current_x = 0; current_x < (width * height); current_x++) //current x == 0 - tile_id_arr size
    {
        // no need to mod the first row
        // also the first column is 0 and this prevents it from being incremented 1 past
        if (current_x < width) //x < 20
            m_coordinates.push_back(new Coordinate<int16_t>(current_x, current_y, tile_id_arr[current_x]));
            //x = 0 -19, y = 0;

        // if we are past the first row
        else if (current_x >= width) //x >= 20
        {
            int row_reset = current_x % width; // x % 20 (should cycle every 20 values)
            if (row_reset == 0)
                current_y++; //y++ on x % 20 == 0 

            m_coordinates.push_back(new Coordinate<int16_t>(row_reset, current_y, tile_id_arr[current_x]));
        }
    }
}

void Map::DrawMap(int scroll_x, int scroll_y, bool& can_move_u, bool& can_move_d, bool& can_move_l, bool& can_move_r)
{
    // so we only need to draw the necessary tiles

    int width_tile_amt = (SCREEN_WIDTH / m_layer_info.m_sprite_w);

    int height_tile_amt = (SCREEN_HEIGHT / m_layer_info.m_sprite_h);

    // go across the screen until the screen width worth of tiles (0 based)
    int width = width_tile_amt + 1;
    // go down the screen until the screen height worth of tiles (0 based)
    int height = height_tile_amt + 1;

    // // similar loop to constructor
    // // but drawing instead of adding
    
    // int skip_tiles = width + 1 + (m_width - width - 1);
    // int counter = 0;

    int draw_x_pos = 0;
    int draw_y_pos = 0;
    int tile_id = 0;
    int scale = 0;

    for (int current_x = 0; current_x < m_coordinates.size(); current_x++) // until 17*13
    {
        // //m_coords.size() = 30 * 20, so we need to adjust
        // draw_x_pos = scroll_x + m_coordinates.at(current_x + (scale * (width_tile_amt - width)))->m_x * m_layer_info.m_sprite_h; // 0, 1, 2 * (30 - 17)
        // draw_y_pos = scroll_y + m_coordinates.at(current_x + (scale * (width_tile_amt - width)))->m_y * m_layer_info.m_sprite_h;

        // tile_id = m_coordinates.at(current_x + (scale * (m_width - width)))->m_value;
        
        // glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_layer_info.m_tileset_img[tile_id]);
    
        // int row_reset = current_x % width + scroll_x; //17 % 17, 34, 51....
        // if (current_x > width && row_reset == 0)
        // {
        //     scale++; 
        // }

        //draws entire map
        draw_x_pos = scroll_x + m_coordinates.at(current_x)->m_x * m_layer_info.m_sprite_h;
        draw_y_pos = scroll_y + m_coordinates.at(current_x)->m_y * m_layer_info.m_sprite_h;

        tile_id = m_coordinates.at(current_x)->m_value;
        
        glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_layer_info.m_tileset_img[tile_id]);
    }
}

bool Map::CheckCollision(int tile_x_01, int tile_x_02, int adj_x_01, int adj_x_02)
{
    int tile_01 = tile_x_01 + adj_x_01;
    int tile_id_01 = m_coordinates.at(tile_01)->m_value;
    
    int tile_02 = tile_x_02 + adj_x_02;
    int tile_id_02 = m_coordinates.at(tile_02)->m_value;

    if (tile_id_01 == 1 || tile_id_02 == 1)
        return false;

    return true;
}

void Map::CheckOverlap(Tileset *overlap)
{
    
}
