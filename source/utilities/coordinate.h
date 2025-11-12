#pragma once

#include <nds.h>
#include <stdio.h>

template < typename T = uint16_t >
class Coordinate
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