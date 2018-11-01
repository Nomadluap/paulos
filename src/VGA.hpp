/*
 * Low-level VGA commands
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include "hex.hpp"
#include <algorithm.hpp>

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

    namespace detail{
        template<typename T, bool is_signed>
        struct putdec_helper{};

        //partial spec for unsigned values.
        template<typename T>
        struct putdec_helper<T, false>
        {
            // write the number into the buffer, pointed to by buf.
            // returns one-past the end of buf.
            static char* eval(T val, char* buf)
            {
                std::array<char, 20> revbuf = {}; //place the number in reverse order.
                auto it = begin(revbuf);
                while(val > 0)
                {
                    int digit = (val % 10);
                    *it = '0' + digit;
                    ++it;
                    val = val / 10;
                }
                while(std::distance(begin(revbuf), --it) >= 0)
                {
                    *buf = *it;
                    ++buf;
                }
                return buf;
            }
        };

        //partial spec for signed values
        template<typename T>
        struct putdec_helper<T, true>
        {
            static char* eval(T val, char* buf)
            {
                if(val < 0)
                {
                    *buf = '-';
                    buf++;
                }
                using unsigned_T = typename std::make_unsigned<T>::type;

                return putdec_helper<unsigned_T, false>::eval(static_cast<unsigned_T>(-val), buf);
            }
        };
    }
    template<typename T>
    void putdec(T t)
    {
        static_assert(std::is_integral<T>::value, "T must be integral");
        //64 bit number has at most 19 characters, plus minus, plus null-terminator.
        std::array<char, 21> out_buf = {};

        if(t == 0)
        {
            put('0');
            return;
        }

        auto end = detail::putdec_helper<T, std::is_signed<T>::value>::eval(t, begin(out_buf));

        *end = '\0';
        put(out_buf.data(), std::distance(begin(out_buf), end));
    }

    template<typename T>
    void puthex(T t)
    {
        static_assert(std::is_integral<T>::value, "T must be an integral type");
        const auto NIBBLES = 2 * sizeof(T);

        put("0x", 2);

        for(size_t i = NIBBLES; i > 0; --i)
        {
            auto nibble = static_cast<uint8_t>(t >> (4 * (i-1)) & 0x0F);
            char c = Hex::hex_digit(nibble);
            put(c);
        }
    }

}}





