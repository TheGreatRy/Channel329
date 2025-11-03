//C++ Classes
#include <map>

//Components Folder
#include "tileset.h"

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class Map
{
public:

    Map(Tileset* layer, int width, int height, const int16_t tile_id_arr[]);
    void DrawMap(int scroll_x, int scroll_y);

    //2D Array with stored values
    std::map<int, std::map<int, int16_t>> m_coordinates;
    Tileset m_layer_info;
};