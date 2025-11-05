#include "map.h"

// this method is a crime i am sorry for my sins
Map::Map(Tileset *layer, int width, int height, const int16_t tile_id_arr[])
{
    m_layer_info = *layer;
    m_width = width;
    m_height = height;

    // this should be more efficent than a nested for loop, but could be more efficent
    // again, leaving it for now

    // the algorithm is inputing (x,y)[value] down the column then across the row
    int current_y = 0;
    for (int current_x = 0; current_x < (width * height); current_x++) //current x == 0 - 30*20
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

void Map::DrawMap(int scroll_x, int scroll_y, bool &can_move_u, bool &can_move_d, bool &can_move_l, bool &can_move_r)
{
    // // so we only need to draw the necessary tiles

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

    //draws the entire map, can be optimized but above attempt did not work
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

        draw_x_pos = scroll_x + m_coordinates.at(current_x)->m_x * m_layer_info.m_sprite_h;
        draw_y_pos = scroll_y + m_coordinates.at(current_x)->m_y * m_layer_info.m_sprite_h;

        tile_id = m_coordinates.at(current_x)->m_value;
        
        glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_layer_info.m_tileset_img[tile_id]);
    }

    //check collison square IF COLLISION MAP

    if (m_layer_info.m_tag == TS_TAG_COL)
    {
    #pragma region Left Collision

    #pragma endregion
    //---------------------------------//

    #pragma region Right Collision
            
    #pragma endregion
    //---------------------------------//

    #pragma region Up Collision
            
    #pragma endregion
    //---------------------------------//

    #pragma region Down Collision
           
    #pragma endregion

    }
}

bool Map::CheckCollision(int scroll_x, int scroll_y, int adjustment_tile_x, bool &can_move)
{
    // int top_right_x = scroll_x + (width_tile_amt / 2) + 1;
            // //int top_right_y = scroll_y + (height_tile_amt / 2) - 1;

            // int tile_id_TR = m_coordinates.at(top_right_x)->m_value;

            // int bot_right_x = scroll_x + (width_tile_amt / 2) + 1;
            // //int bot_right_y = scroll_y + (height_tile_amt / 2);

            // int tile_id_BR = m_coordinates.at(bot_right_x)->m_value;

            // if (tile_id_TR == 1 || tile_id_BR == 1)
            //     can_move_r = false;
            // else if (tile_id_TR == 0 && tile_id_BR == 0)
            //     can_move_r = true;
    return false;
}
