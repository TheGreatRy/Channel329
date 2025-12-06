#pragma once

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class Background
{
public:


    Background();
    ~Background() = default;

    int m_background_id;
    bool m_is_main;

    
};