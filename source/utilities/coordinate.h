#pragma once

template <typename T>

struct Coordinate
{
public:
    int m_x;
    int m_y;
    T m_value;

    Coordinate() = default;
    Coordinate(int x, int y, T value) : 
        m_x{x}, 
        m_y{y}, 
        m_value{value}
    {}
    ~Coordinate() = default;
};