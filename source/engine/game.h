#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <gl2d.h>

//includes characters and backgrounds
#include "../components/scene.h"

class Game
{
    public:
    Game() = default;
    ~Game() = default;

    void InitializeGame();

    void RunCurrentScene(Scene* scene);
};