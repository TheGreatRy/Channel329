#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <gl2d.h>
#include <vector>

//includes characters and backgrounds
#include "../components/scene.h"


class Game
{
    public:
    Game() = default;
    ~Game() = default;

    //GM_STATE* m_current_game_state;

    void InitializeGame();

    void RunCurrentScene(Scene* scene);
    void RunCurrentScene(Scene* scene, Options* options);
};