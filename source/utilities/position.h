#pragma once

class Position
{
    public:
    float m_x;
    float m_y;

    Position(float x, float y) :
        m_x{x},
        m_y{y}
    {}

    ~Position() = default;
};