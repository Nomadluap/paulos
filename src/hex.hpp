

#pragma once
#include <array.hpp>


namespace PaulOS{ namespace Hex{

    extern const std::array<char, 16> hex_lookup;

    inline char hex_digit(uint8_t nibble)
    {
        return hex_lookup[nibble];
    }

}}
