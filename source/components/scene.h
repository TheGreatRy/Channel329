#include <vector>
#include <nds.h>
#include <stdio.h>

//Components Folder
#include "options.h"

//Graphics Folder
#include "../graphics/test_graphics/tiny_16.h"

//Engine Folder
#include "../engine/game_states.h"


class Scene
{
public:
    std::vector<Tileset *> m_drawing_layers;

    void AddLayer(Tileset *layer);
    void DrawLayers(std::vector<Tileset *> layers, int scroll_x, int scroll_y);
    void DrawLayers(std::vector<Tileset *> layers, Options *options, int scroll_x, int scroll_y);

    void ScrollInput(uint16_t keys, int &scroll_x, int &scroll_y);
};