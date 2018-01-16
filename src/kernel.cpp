/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "kernel.hpp"
#include "Foo.hpp"
#include "VGA.hpp"
 
const char* status = "Bar was not triggered. ";

struct Bar
{
    Bar()
    {
        status = "Bar was triggered.";

    }
};
Bar bar;

static void call_global_constructors()
{
    extern void(*__ctors_start)();
    __ctors_start();
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(void) 
{
    using namespace PaulOS;
    call_global_constructors();
	/* Initialize terminal interface */
    Vga::initialize();
    char buf[] = "What is this";
    static_assert(sizeof(buf) == 13, "buf should be 13");
    Vga::put(buf, sizeof(buf));
    Vga::put("Hello from the kernel! ");
    Vga::put(status);

    for(size_t i = 0; i < 80; i++)
    {
        Vga::put_at('@', Vga::make_color(Vga::Color::Cyan, Vga::Color::Black), i, 10);
    }


    //terminal_writestring(foo.str);
}




