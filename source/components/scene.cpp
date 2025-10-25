#include "scene.h"

void Scene::AddLayer(Tileset *layer)
{
    m_drawing_layers.push_back(layer);
}

int Scene::ScanInput(int &scroll_x, int &scroll_y)
{
    scanKeys();

    uint16_t keys = keysHeld();

    if (keys & KEY_START)
        return 0;

    if (keys & KEY_UP)
        scroll_y++;
    if (keys & KEY_DOWN)
        scroll_y--;

    if (keys & KEY_LEFT)
        scroll_x++;
    if (keys & KEY_RIGHT)
        scroll_x--;

    return 1;
}

void Scene::DrawLayers(std::vector<Tileset *> layers, int scroll_x, int scroll_y)
{
    // Print some controls
    printf("PAD:    Scroll\n");
    printf("START:  Exit to loader\n");
    printf("\n");

    while (1)
    {
        swiWaitForVBlank();

        ScanInput(scroll_x, scroll_y);

        glBegin2D();
        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        for (Tileset *layer : m_drawing_layers)
        {
            switch (layer->m_tag)
            {
            case TS_BACKGROUND:
                for (int j = 0; j < MAP_HEIGHT; j++)
                {
                    for (int i = 0; i < MAP_WIDTH; i++)
                    {
                        int x = scroll_x + i * 16;
                        int y = scroll_y + j * 16;
                        int tile_id = map[j * MAP_WIDTH + i];

                        glSprite(x, y, GL_FLIP_NONE, &layer->m_tileset_img[tile_id]);
                    }
                }
                break;
            case TS_CHARACTER:
                glSprite((screen_width / 2) - (layer->m_sprite_w / 2), (screen_height / 2) - (layer->m_sprite_h / 2), GL_FLIP_NONE, &layer->m_tileset_img[0]);
                break;
            }
        }
        // end drawing 2D graphics
        glEnd2D();
        glFlush(0);
    }
}
