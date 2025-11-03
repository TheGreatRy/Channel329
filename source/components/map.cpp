#include "map.h"

// this method is a crime i am sorry for my sins
Map::Map(Tileset* layer, int width, int height, const int16_t tile_id_arr[])
{
    m_layer_info = *layer;

    // this should be more efficent than a nested for loop, but could be more efficent
    // again, leaving it for now

    //the algorithm is inputing (x,y)[value] down the column then across the row
    //essentially a 2D array but they're not allowed as parameters without a size, which needs to by dynamic
    int current_y = 0;
    for (int current_x = 0; current_x < (width * height); current_x++)
    {
        //no need to mod the first row
        //also the first column is 0 and this prevents it from being incremented 1 past
        if (current_x < width) m_coordinates[current_x][current_y] = tile_id_arr[current_x];
        
        //if we are past the first row
        else if (current_x >= width)
        {
            int row_reset = current_x % width;
            if (row_reset == 0) current_y++;

            m_coordinates[row_reset][current_y] = tile_id_arr[current_x];
        }
    }
}

//boy i sure hope my crimes will be convienent!
void Map::DrawMap(int scroll_x, int scroll_y)
{
    //so we only need to draw the necessary tiles

    //go across the screen until the screen width worth of tiles + 1 tile
    int width = (SCREEN_WIDTH/m_layer_info.m_sprite_w) + 1;

    //go down the screen until the screen height worth of tiles + 1 tile
    int height = (SCREEN_HEIGHT/m_layer_info.m_sprite_h) + 1;

    // similar loop to constructor
    // but drawing instead of adding
    int current_y = 0;
    for (int current_x = 0; current_x < (width * height); current_x++)
    {
        //no need to mod the first row
        //also the first column is 0 and this prevents it from being incremented 1 past
        if (current_x < width)
        {
            int draw_x_pos = scroll_x + (current_x * m_layer_info.m_sprite_w);
            int draw_y_pos = scroll_y + (current_y * m_layer_info.m_sprite_h);

            int tile_id = m_coordinates[current_x][current_y];

            glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_layer_info.m_tileset_img[tile_id]);
        }
        //if we are past the first row
        else if (current_x >= width)
        {
            int row_reset = current_x % width;
            if (row_reset == 0) current_y++;

            int draw_x_pos = scroll_x + (row_reset * m_layer_info.m_sprite_w);
            int draw_y_pos = scroll_y + (current_y * m_layer_info.m_sprite_h);


            int tile_id = m_coordinates[row_reset][current_y];

            glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_layer_info.m_tileset_img[tile_id]);
        }
    }  
}