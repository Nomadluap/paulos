

#include "VGA.hpp"
#include "array.hpp"
#include <cstring.hpp>
#include <algorithm.hpp>

namespace PaulOS{ namespace Vga{
    namespace
    {
        const Color default_fg = Color::LightGrey;
        const Color default_bg = Color::Black;
        size_t current_row = 0;
        size_t current_col = 0;
        uint8_t default_color = make_color(default_fg, default_bg);
        uint16_t volatile * volatile const vga_buffer = (uint16_t*)0xB8000;


        constexpr size_t row_offset(size_t row)
        {
            return row * VGA_WIDTH;
        }

        constexpr size_t buffer_offset(size_t x, size_t y)
        {
            return row_offset(y) + x;
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

        void scroll_screen(size_t nlines)
        {
            /*
            for(size_t row = 0; row < nlines; row++)
            {
                std::copy_n(vga_buffer+row_offset(row+1), VGA_WIDTH, vga_buffer + row_offset(row));
            }
            */
            const auto dest = vga_buffer + row_offset(0);
            const auto first = vga_buffer + row_offset(nlines);
            const auto count = sizeof(uint16_t) * VGA_WIDTH * (VGA_HEIGHT-nlines);
            std::memmove(const_cast<uint16_t*>(dest), const_cast<uint16_t const*>(first), count);

            for(size_t row = VGA_HEIGHT-nlines; row < VGA_HEIGHT; row++)
            {
                for(size_t col = 0; col < VGA_WIDTH; col++)
                {
                    put_at(' ', default_color, col, row);
                }
            }
        };

        void advance_row()
        {
            if(++current_row == VGA_HEIGHT)
            {
                //current_row = 0;
                scroll_screen(1);
                current_row = VGA_HEIGHT-1;
            }
        }

    } // anon namespace

    void initialize()
    {
        current_row = 0;
        current_col = 0;
        default_color = make_color(default_fg, default_bg);
        //blank the screen.
        for(size_t y = 0; y < VGA_HEIGHT; y++)
            for(size_t x = 0; x < VGA_WIDTH; x++)
                vga_buffer[buffer_offset(x, y)] = vga_entry(' ', default_color);
    }

    void set_default_color(uint8_t color_code)
    {
        default_color = color_code;
    }

    void put_at(char c, uint8_t color, size_t x, size_t y)
    {
        const auto index = buffer_offset(x, y);
        vga_buffer[index] = vga_entry(c, color);
    }



    void put(char c)
    {
        switch(c)
        {
        case '\0': // null is not printed
            break;
        case '\n':
            current_col = 0;
            advance_row();
            break;

        default:
            put_at(c, default_color, current_col, current_row);
            if(++current_col == VGA_WIDTH)
            {
                current_col = 0;
                advance_row();
            }
            break;
        }
    }

    void put(char const *s, size_t length)
    {
        for(size_t i = 0; i < length; i++)
        {
            put(s[i]);
        }
    }

    void put(char const *s)
    {
        put(s, strlen(s));
    }

    void putline(char const* s, size_t length)
    {
        put(s, length);
        put('\n');
    }

    void putline(char const* s)
    {
        put(s);
        put('\n');

    }
}}
