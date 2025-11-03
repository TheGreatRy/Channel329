#include "map.h"

Map::Map(int width, int height, int16_t tile_id_arr[])
{
    // this was 1D array, switching to 2D
    // // theoretically i can make a more effecient algorithm
    // // for now, it'll be slow
    // for (int i = 0; i < (width * height); i++)
    // {
    //     m_tile_id_array.push_back(tile_id_arr[i]);
    // }

    // // this should be more efficent than a nested for loop, but could be more efficent
    // // again, leaving it for now

    // //the algorithm is inputing (x,y) across the row then down the column
    // //the map is key = x, the vector is all y values
    // int current_y = 0;
    // for (int current_x = 0; current_x < (width * height); current_x++)
    // {
    //     //no need to mod the first row
    //     //also the first column is 0 and this prevents it from being incremented 1 past
    //     if (current_x < width) m_coordinates[current_x].push_back(current_y);
        
    //     //if we are past the first row
    //     else if (current_x >= width)
    //     {
    //         int row_reset = current_x % width;
    //         if (row_reset == 0) current_y++;

    //         m_coordinates[row_reset].push_back(current_y);
    //     }
    // }
}

void Map::DrawMap(int scroll_x, int scroll_y, Tileset *layer)
{
    // for (int j = 0; j < MAP_HEIGHT; j++)
    // {
    //     for (int i = 0; i < MAP_WIDTH; i++)
    //     {
    //         int x = scroll_x + i * 16;
    //         int y = scroll_y + j * 16;
    //         int tile_id = collisions_interaction[j * MAP_WIDTH + i];

    //         glSprite(x, y, GL_FLIP_NONE, &layer->m_tileset_img[tile_id]);
    //     }
    // }
}