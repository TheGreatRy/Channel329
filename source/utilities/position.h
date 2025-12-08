#pragma once

class Position
{
    public:
    int m_x;
    int m_y;

    Position(int x, int y) :
        m_x{x},
        m_y{y}
    {}

    ~Position() = default;
};