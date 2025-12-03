#pragma once

#include <nds.h>

class BackgroundData
{
    public:
    int m_bitmap_base;
    const unsigned int* m_bitmap_source;
    uint32_t m_bitmap_size; 
    const unsigned short*  m_pal_source;
    uint32_t m_pal_size;

    int m_bpp;

    BackgroundData(int bpp, int bitmap_base, const unsigned int* bitmap_source, uint32_t bitmap_size, const unsigned short* pal_source, uint32_t pal_size) :
        m_bpp{bpp},
        m_bitmap_base{bitmap_base},
        m_bitmap_source{bitmap_source},
        m_bitmap_size{bitmap_size},
        m_pal_source{pal_source},
        m_pal_size{pal_size}
    {};
    
    BackgroundData(int bpp, int bitmap_base, const unsigned int* bitmap_source, uint32_t bitmap_size) :
        m_bpp{bpp},    
        m_bitmap_base{bitmap_base},
        m_bitmap_source{bitmap_source},
        m_bitmap_size{bitmap_size}
    {};
};