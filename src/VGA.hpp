/*
 * Low-level VGA commands
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace PaulOS { namespace Vga {

    const size_t VGA_HEIGHT = 25;
    const size_t VGA_WIDTH = 80;

    enum class Color: uint8_t
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGrey = 7,
        DarkGrey = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        LightBrown = 14,
        White = 15
    };

    constexpr inline uint8_t make_color(Color fg, Color bg)
    {
        return static_cast<uint8_t>(fg) | (static_cast<uint8_t>(bg) << 4);
    }

    constexpr inline Color fg_color(uint8_t color_code)
    {
        return static_cast<Color>(color_code & 0x0F);
    }

    constexpr
    inline Color bg_color(uint8_t color_code)
    {
        return static_cast<Color>((color_code >> 4) & 0x0F);
    }

    constexpr inline uint16_t vga_entry(unsigned char uc, uint8_t color_code)
    {
        return static_cast<uint16_t>(uc) | (static_cast<uint16_t>(color_code) << 8);
    }


    void initialize();
    void set_default_color(uint8_t color_code);
    inline void set_default_color(Color fg, Color bg){set_default_color(make_color(fg, bg));}

    void put_at(char c, uint8_t color, size_t x, size_t y);

    // put single character.
    void put(char c);

    // length-delimited string to console.
    void put(char const* s, size_t length);

    // null-terminated string to console.
    void put(char const* s);

    void putline(char const* s, size_t length);
    void putline(char const* s);

}}





