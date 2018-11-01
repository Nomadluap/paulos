#include "stack.hpp"
#include "VGA.hpp"

namespace PaulOS{ namespace Stack{
    void dump_stack()
    {
        using namespace Vga;
        auto p = reinterpret_cast<uint8_t const*>(Stack::ebp());
        auto end = reinterpret_cast<uint8_t const*>(Stack::stack_top());

        putline("Stack contents:");
        while(p < end)
        {
            //print address, then 16 bytes
            put(' ');
            puthex(reinterpret_cast<uintptr_t>(p));
            put(": (");
            puthex(*(reinterpret_cast<uintptr_t const*>(p)));
            //puthex(reinterpret_cast<uintptr_t>(p));
            put(")  ");

            for(int i = 0; i < 4; i++)
            {
                if(p >= end) break;

                auto val = *p;
                p++;

                std::array<char, 3>  buf = {' ', ' ', ' '};
                buf[0] = Hex::hex_digit((val >> 4) & 0x0F);
                buf[1] = Hex::hex_digit(val & 0x0F);

                put(buf.data(), buf.size());
            }
            put('\n');
        }
    }

    void stacktrace(size_t max_levels)
    {
        /* Stack contains:
         *  - second function arg
         *  - first function arg (maxframes)
         *  - return addr in calling function
         *  - ebp of calling function (pointed to by current ebp)
         */

        uintptr_t const* ebp = reinterpret_cast<uintptr_t const *>(Stack::ebp());
        Vga::putline("Stack trace:");
        for(size_t frame = 0; frame < max_levels; ++frame)
        {
            uintptr_t eip = ebp[2];
            if(eip == 0) //no caller on stack (done)
                break;

            ebp = reinterpret_cast<uintptr_t*>(ebp[1]);

            Vga::put(' ');
            Vga::putdec(frame);
            Vga::put(": ");
            Vga::puthex(eip);
            Vga::put('\n');
        }
    }
} }

