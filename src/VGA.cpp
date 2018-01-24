

#include "VGA.hpp"
#include "array.hpp"

namespace v = PaulOS::Vga;
namespace
{
    const v::Color default_fg = v::Color::LightGrey;
    const v::Color default_bg = v::Color::Black;
    size_t current_row = 0;
    size_t current_col = 0;
    uint8_t default_color = v::make_color(default_fg, default_bg);
    uint16_t volatile * volatile const vga_buffer = (uint16_t*)0xB8000;

    constexpr size_t buffer_offset(size_t x, size_t y)
    {
        return y * v::VGA_WIDTH + x;
    }

    size_t strlen(char const* s)
    {
        size_t count = 0;
        while(*s)
        {
            s++;
            count++;
        }
        return count;
    }
}

void PaulOS::Vga::initialize()
{
    current_row = 0;
    current_col = 0;
    default_color = v::make_color(default_fg, default_bg);
    //blank the screen.
    for(size_t y = 0; y < v::VGA_HEIGHT; y++)
        for(size_t x = 0; x < v::VGA_WIDTH; x++)
            vga_buffer[buffer_offset(x, y)] = vga_entry(' ', default_color);
}

void PaulOS::Vga::set_default_color(uint8_t color_code)
{
    default_color = color_code;
}

void PaulOS::Vga::put_at(char c, uint8_t color, size_t x, size_t y)
{
    const auto index = buffer_offset(x, y);
    vga_buffer[index] = vga_entry(c, color);
}

void PaulOS::Vga::put(char c)
{
    put_at(c, default_color, current_col, current_row);
    if(++current_col == VGA_WIDTH)
    {
        current_col = 0;
        if(++current_row == VGA_HEIGHT)
        {
            current_row = 0;
        }
    }
}

void PaulOS::Vga::put(char const *s, size_t length)
{
    for(size_t i = 0; i < length; i++)
    {
        put(s[i]);
    }
}

void PaulOS::Vga::put(char const *s)
{
    put(s, strlen(s));
}
