
#pragma once
#include <stddef.h>

extern "C"{
    extern void* __stack_top;
    extern void* __stack_bottom;
}

namespace PaulOS{ namespace Stack{


    // return stack pointer.
    inline void* esp()
    {
        void* ret = nullptr;
        asm(
        "mov %%esp, %0"
        : "=r" (ret)
        );
        return ret;
    }

    inline void* ebp()
    {
        void* ret = nullptr;
        asm(
        "mov %%ebp, %0"
        : "=r" (ret)
        );
        return ret;
    }

    inline void* stack_top()
    {
        return &__stack_top;
    }

    inline void* stack_bottom()
    {
        return &__stack_bottom;
    }

    void dump_stack();

    /**
     * Print a stack trace to the VGA output.
     */
    void stacktrace(size_t max_levels);

}}

